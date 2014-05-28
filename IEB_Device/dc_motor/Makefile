CC 	:= /opt/iwmmxt-1.0.0/bin/arm-linux-gcc

KDIR	:= /project/xhyper270-TKU-Rev/kernel/linux-2.6.11-h270-tku_v1.1

TEST_TARGET = dc_motor_test
TEST_OBJS   = dc_motor_test.o
TEST_SRCS   = dc_motor_test.c 

obj-m	:= dc_motor.o

build: $(TEST_TARGET) 
	make -C $(KDIR) SUBDIRS=`pwd` modules

$(TEST_TARGET) : $(TEST_OBJS)
	$(CC) -o $@ $(TEST_OBJS)
clean:
	rm -rf *.o *.ko *.mod.c
	rm -f $(TEST_TARGET)

