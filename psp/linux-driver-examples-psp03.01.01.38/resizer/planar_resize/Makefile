# Makefile for planar_resize application
# Change the kernel patch to point to personal Linux Tree

CC = $(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include

all: planar_resize

planar_resize: planar_resize.o
	$(CC) -o planar_resize $^

%.o:%.c
	$(CC) $(CFLAGS) -c $^

install:
	mkdir -p $(INSTALL_DIR)
	cp planar_resize $(INSTALL_DIR)

clean:
	rm -f *.o *~ core planar_resize
