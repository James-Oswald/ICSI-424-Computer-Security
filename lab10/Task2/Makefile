obj-m += task2.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=/home/seed/lab10/Task2 modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=/home/seed/lab10/Task2 clean