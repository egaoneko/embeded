CC 	:= /opt/iwmmxt-1.0.0/bin/arm-linux-gcc

KDIR	:= /XHyper270-TKU/kernel/linux-2.6.11-h270-tku_v1.1-app

TEST_TARGET = fnd_test
TEST_OBJS   = fnd_test.o
TEST_SRCS   = fnd_test.c 

obj-m	:= fnd.o

build: $(TEST_TARGET) 
	make -C $(KDIR) SUBDIRS=`pwd` modules

$(TEST_TARGET) : $(TEST_OBJS)
	$(CC) -o $@ $(TEST_OBJS)
clean:
	rm -rf *.o *.ko *.mod.c
	rm -f $(TEST_TARGET)

