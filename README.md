embeded
=======
fnd	: xhyper255
dot	: xhyper255
clcd	: xhyper255 driver change
key	: xhyper270 driver change
led	: xhyper

edit kernel : /include/linux/fs.h => file_operations
+ clcd add write2
