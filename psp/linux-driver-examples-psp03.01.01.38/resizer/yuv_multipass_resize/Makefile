# Makefile for yuv_multipass_resize application
# Change the kernel patch to point to personal Linux Tree

CC = $(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include

all: yuv_multipass_resize

yuv_multipass_resize: yuv_multipass_resize.o
	$(CC) -o yuv_multipass_resize $^

%.o:%.c
	$(CC) $(CFLAGS) -c $^

install:
	mkdir -p $(INSTALL_DIR)
	cp yuv_multipass_resize $(INSTALL_DIR)

clean:
	rm -f *.o *~ core yuv_multipass_resize
