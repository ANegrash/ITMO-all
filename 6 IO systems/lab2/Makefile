kmod=main

obj-m += $(kmod).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insmod:
	sudo insmod $(kmod).ko

rmmod:
	sudo rmmod $(kmod).ko
