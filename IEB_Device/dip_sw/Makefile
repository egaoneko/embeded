CC 	:= /opt/iwmmxt-1.0.0/bin/arm-linux-gcc

KDIR	:= /project/xhyper270-TKU-Rev/kernel/linux-2.6.11-h270-tku_v1.1

TEST_TARGET = dip_test
TEST_OBJS   = dip_test.o
TEST_SRCS   = dip_test.c 

obj-m	:= dip.o

build: $(TEST_TARGET) 
	make -C $(KDIR) SUBDIRS=`pwd` modules

$(TEST_TARGET) : $(TEST_OBJS)
	$(CC) -o $@ $(TEST_OBJS)
clean:
	rm -rf *.o *.ko *.mod.c
	rm -f $(TEST_TARGET)

