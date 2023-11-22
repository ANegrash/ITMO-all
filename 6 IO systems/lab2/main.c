#include <linux/bio.h>
#include <linux/blk-mq.h>
#include <linux/blkdev.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/genhd.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/vmalloc.h>

#define DISK_NAME "vramdisk"

#define MEMSIZE 0x19000 // Size of Ram disk in sectors

int major = 0; // Variable for Major Number

#define MDISK_SECTOR_SIZE 512
#define MBR_SIZE MDISK_SECTOR_SIZE
#define MBR_DISK_SIGNATURE_OFFSET 440
#define MBR_DISK_SIGNATURE_SIZE 4
#define PARTITION_TABLE_OFFSET 446
#define PARTITION_ENTRY_SIZE 16
#define PARTITION_TABLE_SIZE 64
#define MBR_SIGNATURE_OFFSET 510
#define MBR_SIGNATURE_SIZE 2
#define MBR_SIGNATURE 0xAA55
#define BR_SIZE MDISK_SECTOR_SIZE
#define BR_SIGNATURE_OFFSET 510
#define BR_SIGNATURE_SIZE 2
#define BR_SIGNATURE 0xAA55

typedef struct {
	unsigned char boot_type; // 0x00 - Inactive; 0x80 - Active (Bootable)
	unsigned char start_head;
	unsigned char start_sec : 6;
	unsigned char start_cyl_hi : 2;
	unsigned char start_cyl;
	unsigned char part_type;
	unsigned char end_head;
	unsigned char end_sec : 6;
	unsigned char end_cyl_hi : 2;
	unsigned char end_cyl;
	unsigned int abs_start_sec;
	unsigned int sec_in_part;
} PartEntry;

typedef PartEntry PartTable[4];

static struct lock_class_key sr_bio_compl_lkclass;

#define SEC_PER_HEAD 63
#define HEAD_PER_CYL 255
#define HEAD_SIZE (SEC_PER_HEAD * MDISK_SECTOR_SIZE)
#define CYL_SIZE (SEC_PER_HEAD * HEAD_PER_CYL * MDISK_SECTOR_SIZE)

#define sec4size(s) ((((s) % CYL_SIZE) % HEAD_SIZE) / MDISK_SECTOR_SIZE)
#define head4size(s) (((s) % CYL_SIZE) / HEAD_SIZE)
#define cyl4size(s) ((s) / CYL_SIZE)

static PartTable def_part_table =
{
	{
		boot_type: 0x00,
		start_sec: 0x2,
		start_head: 0x0,
		start_cyl: 0x0,
		part_type: 0x83,
		end_head: 0x3,
		end_sec: 0x20,
		end_cyl: 0x9F,
		abs_start_sec: 0x1,
		sec_in_part: 0x4FFF // 10Mbyte
	},
	{
		boot_type: 0x00,
		start_sec: 0x1,
		start_head: 0x4,
		start_cyl: 0x0,
		part_type: 0x83,
		end_sec: 0x20,
		end_head: 0xD,
		end_cyl: 0x9F,
		abs_start_sec: 0x5000,
		sec_in_part: 0xC800 // 25Mbyte
	},
	{
		boot_type: 0x00,
		start_sec: 0x1,
		start_head: 0xE,
		start_cyl: 0x0,
		part_type: 0x83,
		end_head: 0x13,
		end_sec: 0x20,
		end_cyl: 0x9F,
		abs_start_sec: 0x11800,
		sec_in_part: 0x7800 // 15Mbyte
	}
};

static void copy_mbr(u8 *disk) {
	memset(disk, 0x0, MBR_SIZE);
	*(unsigned long *)(disk + MBR_DISK_SIGNATURE_OFFSET) = 0x36E5756D;
	memcpy(disk + PARTITION_TABLE_OFFSET, &def_part_table, PARTITION_TABLE_SIZE);
	*(unsigned short *)(disk + MBR_SIGNATURE_OFFSET) = MBR_SIGNATURE;
}

/* Structure associated with Block device*/
struct vram_disk_device {
	size_t size;
	u8 *data;
	atomic_t nr_users;
	// spinlock_t lock;
	struct blk_mq_tag_set tag_set;
	struct request_queue *queue;
	struct gendisk *gd;
} device;

// struct vram_disk_device *x;

static int vramdisk_open(struct block_device *x, fmode_t mode) {
	struct vram_disk_device *dev = x->bd_disk->private_data;
	if (dev == NULL) {
		printk(KERN_WARNING DISK_NAME "driver: invalid disk private_data\n");
		return -ENXIO;
	}

	atomic_inc(&dev->nr_users);
	printk(KERN_INFO DISK_NAME "driver: open \n");

	return 0;
}

static void vramdisk_release(struct gendisk *disk, fmode_t mode) {
	struct vram_disk_device *dev = disk->private_data;
	if (dev) {
		atomic_dec(&dev->nr_users);
		printk(KERN_INFO DISK_NAME "driver: closed \n");
	} else
		printk(KERN_WARNING DISK_NAME "driver: invalid disk private_data\n");
}

static struct block_device_operations fops = {
    .owner = THIS_MODULE,
    .open = vramdisk_open,
    .release = vramdisk_release,
};

int vramdisk_init(void) {
	device.size = MEMSIZE;
	device.data = vmalloc(MEMSIZE * MDISK_SECTOR_SIZE);
	if (device.data == NULL) {
		printk(KERN_WARNING DISK_NAME "driver: vmalloc failure.\n");
		return -ENOMEM;
	}

	/* Load partition table */
	copy_mbr(device.data);

	return 0;
}

static int rb_transfer(struct request *req, unsigned int *nr_bytes) {
	int dir = rq_data_dir(req);
	sector_t start_sector = blk_rq_pos(req);
	unsigned int sector_cnt = blk_rq_sectors(req); /* no of sector on which opn to be done*/

	struct bio_vec bv;
#define BV_PAGE(bv) ((bv).bv_page)
#define BV_OFFSET(bv) ((bv).bv_offset)
#define BV_LEN(bv) ((bv).bv_len)

	struct req_iterator iter;
	sector_t sector_offset = 0;
	unsigned int sectors;
	u8 *buffer;

	rq_for_each_segment(bv, req, iter) {
		buffer = page_address(BV_PAGE(bv)) + BV_OFFSET(bv);
		if (BV_LEN(bv) % (MDISK_SECTOR_SIZE) != 0) {
			printk(KERN_ERR DISK_NAME ": bio size is not a multiple of sector size\n");
			return -EIO;
		}

		sectors = BV_LEN(bv) / MDISK_SECTOR_SIZE;
		printk(KERN_DEBUG DISK_NAME ": Start Sector: %llu, Sector Offset: %llu; Buffer: %p; Length: %u sectors\n",
			   (unsigned long long)(start_sector),
			   (unsigned long long)(sector_offset), buffer, sectors);

		if (dir == WRITE) /* Write to the device */
			memcpy((device.data) +
					 ((start_sector + sector_offset) * MDISK_SECTOR_SIZE),
				 buffer, sectors * MDISK_SECTOR_SIZE);
		else /* Read from the device */
			memcpy(buffer,
				 (device.data) +
					 ((start_sector + sector_offset) * MDISK_SECTOR_SIZE),
				 sectors * MDISK_SECTOR_SIZE);

		sector_offset += sectors;
		*nr_bytes += sectors * MDISK_SECTOR_SIZE;
	}

	if (sector_offset != sector_cnt) {
		printk(KERN_ERR DISK_NAME ": bio info doesn't match with the request info");
		return -EIO;
	}

	return 0;
#undef BV_PAGE
#undef BV_OFFSET
#undef BV_LEN
}

/* request handling function */
/**
 * Changing according to blk multi-queue feature
 */
static blk_status_t handle_request(struct blk_mq_hw_ctx *hardware_context, const struct blk_mq_queue_data *bd) {
	blk_status_t status = BLK_STS_OK;
	unsigned int nr_bytes = 0;
	struct request *req = bd->rq;
	switch (rb_transfer(req, &nr_bytes)) {
		case -EIO: {
			status = BLK_STS_IOERR;
		} break;
		default: {
			status = BLK_STS_OK;
		} break;
	};

	if (blk_update_request(req, status, nr_bytes)) // GPL-only symbol
	BUG();
	__blk_mq_end_request(req, status);

	return status;
}

static struct blk_mq_ops vram_queue_ops = {
    .queue_rq = handle_request,
};

int device_setup(void) {
	/* Register block device */
	major = register_blkdev(major, DISK_NAME); // major no. allocation

	if (major <= 0) {
		printk(KERN_WARNING DISK_NAME ": unable to get major number\n");
		return -EBUSY;
	}

	printk(KERN_ALERT "Major Number is : %d", major);

	if (vramdisk_init()) {
		return -ENOMEM;
	}

	device.tag_set.ops = &vram_queue_ops;
	device.tag_set.nr_hw_queues = 1;
	device.tag_set.queue_depth = 128;
	device.tag_set.numa_node = NUMA_NO_NODE;
	device.tag_set.cmd_size = sizeof(struct vram_disk_device);
	device.tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	device.tag_set.driver_data = &device;
	if (blk_mq_alloc_tag_set(&(device.tag_set))) {
		return -ENOMEM;
	}

	device.queue = blk_mq_init_queue(&(device.tag_set));
	if (IS_ERR(device.queue)) {
		blk_mq_free_tag_set(&(device.tag_set));
		return -ENOMEM;
	}
	device.queue->queuedata = &device;

	/* Initialize gendisk */
	device.gd = __alloc_disk_node(device.queue, 7, &sr_bio_compl_lkclass);

	if (!device.gd) {
		printk(KERN_INFO DISK_NAME ": alloc_disk failure\n");
		return -EBUSY;
	}

	device.gd->minors = 7;
	(device.gd)->major = major; // major no to gendisk
	device.gd->first_minor = 0; // first minor of gendisk

	device.gd->fops = &fops;
	device.gd->private_data = &device;
	device.gd->queue = device.queue;
	printk(KERN_INFO "Device size: %zu", device.size);

	snprintf(((device.gd)->disk_name), DISK_NAME_LEN, DISK_NAME);

	set_capacity(device.gd, device.size);

	add_disk(device.gd);
	return 0;
}

static int __init vramdisk_drive_init(void) {
	int ret = 0;
	ret = device_setup();
	return ret;
}

void vramdisk_cleanup(void) { vfree(device.data); }

void __exit vramdisk_drive_exit(void) {
	del_gendisk(device.gd);
	put_disk(device.gd);

	blk_cleanup_queue(device.queue);
	blk_mq_free_tag_set(&(device.tag_set));

	// cleanup device buffer in ram
	vramdisk_cleanup();

	unregister_blkdev(major, DISK_NAME);
}

module_init(vramdisk_drive_init);
module_exit(vramdisk_drive_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ANegrash, IP-13");
MODULE_DESCRIPTION("BLOCK DRIVER");
