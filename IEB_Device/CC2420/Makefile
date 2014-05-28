CC 	:= /opt/iwmmxt-1.0.0/bin/arm-linux-gcc
KDIR	:= /project/xhyper270-TKU-Rev/kernel/linux-2.6.11-h270-tku_v1.1 

TEST_TARGET1 = receiver
TEST_OBJS1   = receiver.o
TEST_SRCS1   = receiver.c 

TEST_TARGET2 = sender
TEST_OBJS2   = sender.o
TEST_SRCS2   = sender.c

build: $(TEST_TARGET1) $(TEST_TARGET2)

$(TEST_TARGET1) : $(TEST_OBJS1)
	$(CC) -o $@ $(TEST_OBJS1)

$(TEST_TARGET2) : $(TEST_OBJS2)
	$(CC) -o $@ $(TEST_OBJS2)

clean:
	rm -rf *.o
	rm -rf $(TEST_TARGET1) $(TEST_TARGET2)

