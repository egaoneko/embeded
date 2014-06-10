CC := /opt/iwmmxt-1.0.0/bin/arm-linux-gcc

KDIR := /XHyper270-TKU/kernel/linux-2.6.11-h270-tku_v1.1-app

obj-m := btn.o

all: btn.ko	btn_test

btn.ko:
	make -C $(KDIR) SUBDIRS=`pwd` modules

btn_test : btn_test.c
	$(CC) -o btn_test btn_test.c

clean:
	rm -rf *.o *.ko btn_test
