CC 	:= /opt/iwmmxt-1.0.0/bin/arm-linux-gcc

KDIR	:= /XHYPER270-TKU/kernel/linux-2.6.11-h270-tku_v1.1

TEST_TARGET = clcd_test
TEST_OBJS   = clcd_test.o
TEST_SRCS   = clcd_test.c 

obj-m	:= clcd.o

build: $(TEST_TARGET) 
	make -C $(KDIR) SUBDIRS=`pwd` modules

$(TEST_TARGET) : $(TEST_OBJS)
	$(CC) -o $@ $(TEST_OBJS)
clean:
	rm -rf *.o *.ko *.mod.c
	rm -f $(TEST_TARGET)

