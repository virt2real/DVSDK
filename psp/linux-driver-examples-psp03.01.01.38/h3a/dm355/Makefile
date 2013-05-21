# Makefile for h3a applications
# Change the path for the include files appropriately

CC = $(CROSS_COMPILE)gcc -I $(KERNEL_DIR)/include

INSTALL_DIR=$(FINAL_DEST)/h3a

all: aew_example af_example

aew_example:aew_example.o
	$(CC) -o aew_example -lpthread $^

af_example:af_example.o
	$(CC) -o af_example -lpthread $^

%.o:%.c
	$(CC) $(CFLAGS) -c $^

install:
	mkdir -p $(INSTALL_DIR)
	cp aew_example $(INSTALL_DIR)
	cp af_example $(INSTALL_DIR)

clean:
	rm -f *.o *~ core aew_example af_example
