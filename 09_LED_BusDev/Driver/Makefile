KERN_DIR = /home/shuimu/more/linux-3.0.1
all:
	make -C $(KERN_DIR) M=`pwd` modules

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m += LED_BusDev.o
obj-m += LED_BusDrv.o
