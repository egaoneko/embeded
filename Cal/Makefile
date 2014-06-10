Main : Main.o Dev.o Calculator.o HisOpen.o HisSave.o HisNum.o ListBaseStack.o InfixCalculator.o InfixToPostfix.o PostCalculator.o
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -o Main Main.o Dev.o Calculator.o HisOpen.o HisSave.o HisNum.o ListBaseStack.o  InfixCalculator.o InfixToPostfix.o PostCalculator.o -lpthread
Main.o : Main.c Dev.h Calculator.h InfixCalculator.h History.h
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c Main.c
Dev.o : Dev.c Dev.h
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c Dev.c
Calculator.o : Calculator.c Calculator.h 
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c Calculator.c
HisOpen.o : HisOpen.c History.h
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c HisOpen.c
HisSave.o : HisSave.c History.h 
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c HisSave.c
HisNum.o : HisNum.c History.h
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c HisNum.c
ListBaseStack.o : ListBaseStack.c ListBaseStack.h
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c ListBaseStack.c
InfixCalculator.o : InfixCalculator.c InfixCalculator.h Calculator.h PostCalculator.h
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c InfixCalculator.c
InfixToPostfix.o : InfixToPostfix.c InfixToPostfix.h ListBaseStack.h Calculator.h
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c InfixToPostfix.c
PostCalculator.o : PostCalculator.c PostCalculator.h ListBaseStack.h Calculator.h
	/opt/iwmmxt-1.0.0/bin/arm-linux-gcc -c PostCalculator.c

clean:
	rm -rf *.o *.ko *.mod.c
	rm -f $(TEST_TARGET)
