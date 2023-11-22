TARGET = lab3
obj-m += $(TARGET).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	
test:
	sudo dmesg -C
	sudo insmod ${TARGET}.ko
	sudo dmesg

exit:
	sudo rmmod $(TARGET)
