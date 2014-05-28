CC 	:= /opt/iwmmxt-1.0.0/bin/arm-linux-gcc

KDIR	:= /XHYPER270-TKU/kernel/linux-2.6.11-h270-tku_v1.0 

TEST_TARGET = key_test
TEST_OBJS   = key_test.o
TEST_SRCS   = key_test.c 

obj-m	:= key.o

build: $(TEST_TARGET) 
	make -C $(KDIR) SUBDIRS=`pwd` modules

$(TEST_TARGET) : $(TEST_OBJS)
	$(CC) -o $@ $(TEST_OBJS)
clean:
	rm -rf *.o *.ko *.mod.c
	rm -f $(TEST_TARGET)

