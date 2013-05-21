# Makefile for fbdev applications
# Change the kernel patch to point to Linux source tree
INSTALL_DIR=$(FINAL_DEST)/v4l2
CMEMLIB=cmem.a470uC
CC = $(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include

all: vpif_mmap_loopback vpif_userptr_loopback vpif_userptr_loopback_vdce vpif_userptr_loopback_vdce_resize v4l2_mmap_loopback v4l2_userptr_loopback v4l2_userptr_loopback_hd

build_vpfe_vpbe: v4l2_mmap_loopback v4l2_userptr_loopback

build_vpfe_vpbe_hd: build_vpfe_vpbe v4l2_userptr_loopback_hd

build_vpif: vpif_userptr_loopback vpif_userptr_loopback_vdce

install_vpif:
	mkdir -p $(INSTALL_DIR)
	install vpif_userptr_loopback_vdce	$(INSTALL_DIR)
	install vpif_userptr_loopback 		$(INSTALL_DIR)

install_vpfe_vpbe:
	mkdir -p $(INSTALL_DIR)
	cp v4l2_mmap_loopback $(INSTALL_DIR)
	cp v4l2_userptr_loopback $(INSTALL_DIR)

install_vpfe_vpbe_hd: install_vpfe_vpbe
	cp v4l2_userptr_loopback_hd $(INSTALL_DIR)

vpif_userptr_loopback_vdce: vpif_userptr_loopback_vdce.o
	$(CC) -o  vpif_userptr_loopback_vdce $^

vpif_userptr_loopback_vdce_resize: vpif_userptr_loopback_vdce_resize.o
	$(CC) -o  vpif_userptr_loopback_vdce_resize $^

vpif_mmap_loopback: vpif_mmap_loopback.o
	$(CC) -o  vpif_mmap_loopback $^

vpif_userptr_loopback: vpif_userptr_loopback.o
	$(CC) -o  vpif_userptr_loopback $^

v4l2_mmap_loopback: v4l2_mmap_loopback.o
	$(CC) -o v4l2_mmap_loopback $^

v4l2_userptr_loopback: v4l2_userptr_loopback.o
	$(CC) -o v4l2_userptr_loopback $^ 

v4l2_userptr_loopback_hd: v4l2_userptr_loopback_hd.o
	$(CC) -o v4l2_userptr_loopback_hd $^ $(CMEMLIB)

%.o:%.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o *~ core vpif_mmap_loopback vpif_userptr_loopback vpif_userptr_loopback_vdce v4l2_mmap_loopback v4l2_userptr_loopback v4l2_userptr_loopback_hd vpif_userptr_loopback_vdce_resize
