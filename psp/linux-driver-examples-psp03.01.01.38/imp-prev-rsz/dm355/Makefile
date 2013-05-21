# Makefile for IPIPE applications
CROSS_COMPILE=arm-none-linux-gnueabi-
CMEMLIB=cmem.a470uC
INSTALL_DIR=$(FINAL_DEST)/imp-prev-rsz

CC = $(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include

all:	capture_prev_rsz_onthe_fly_bayer capture_prev_rsz_ss_raw_bayer

capture_prev_rsz_onthe_fly_bayer: capture_prev_rsz_onthe_fly_bayer.o
	$(CC) -o  capture_prev_rsz_onthe_fly_bayer $^ $(CMEMLIB)

capture_prev_rsz_ss_raw_bayer: capture_prev_rsz_ss_raw_bayer.o
	$(CC) -o  capture_prev_rsz_ss_raw_bayer $^ $(CMEMLIB)

install:
	mkdir -p $(INSTALL_DIR)
	cp capture_prev_rsz_onthe_fly_bayer $(INSTALL_DIR)
	cp capture_prev_rsz_ss_raw_bayer $(INSTALL_DIR)

clean:
	rm -f *.o *~
	rm -f capture_prev_rsz_onthe_fly_bayer \
	rm -f capture_prev_rsz_ss_raw_bayer
