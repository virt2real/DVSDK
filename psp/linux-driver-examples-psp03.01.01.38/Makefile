CROSS_COMPILE=arm-none-linux-gnueabi-

ifeq ($(strip $(DEST)),)
DEST=$(shell pwd)/bin
endif

FINAL_DEST=$(DEST)/$(PLATFORM)

export KERNEL_DIR CROSS_COMPILE PLATFORM ALSA_LIB_PATH FINAL_DEST

all: sanity build_$(PLATFORM) build_common

.PHONY sanity:
ifeq ($(strip $(KERNEL_DIR)),)
	@echo "Please pass a KERNEL_DIR= variable pointing to your PSP kernel directory."
	@exit 1
endif

ifeq ($(strip $(PLATFORM)),)
	@echo "Please pass a PLATFORM= {dm355|dm365|dm6467|dm6467t}"
	@exit 1
endif

ifeq ($(strip $(PLATFORM)),)
	@echo "Please pass a PLATFORM= {dm355|dm365|dm6467|dm6467t}"
	@exit 1
endif

install: install_prepare install_$(PLATFORM) install_common

install_prepare:
	mkdir -p $(FINAL_DEST)

install_dm355:
	$(MAKE) -C h3a/dm355 install
	$(MAKE) -C imp-prev-rsz/dm355 install
	$(MAKE) -C fbdev install
	$(MAKE) -C v4l2 install_vpfe_vpbe
	$(MAKE) -C gpio install

build_dm355:
	$(MAKE) -C h3a/dm355
	$(MAKE) -C imp-prev-rsz/dm355
	$(MAKE) -C fbdev
	$(MAKE) -C v4l2 build_vpfe_vpbe
	$(MAKE) -C gpio

install_dm365:
	$(MAKE) -C imp-prev-rsz/dm365 install
	$(MAKE) -C fbdev install
	$(MAKE) -C v4l2 install_vpfe_vpbe_hd

build_dm365:
	$(MAKE) -C imp-prev-rsz/dm365
	$(MAKE) -C fbdev
	$(MAKE) -C v4l2 build_vpfe_vpbe_hd

install_dm6467t: install_dm6467

install_dm6467:
	$(MAKE) -C vdce install
	$(MAKE) -C cir install
	$(MAKE) -C v4l2 install_vpif

build_dm6467t: build_dm6467

build_dm6467:
	$(MAKE) -C vdce
	$(MAKE) -C cir
	$(MAKE) -C v4l2 build_vpif

install_dm644x:
	$(MAKE) -C v4l2 install_vpfe_vpbe
	$(MAKE) -C fbdev install
	$(MAKE) -C resizer/planar_resize install
	$(MAKE) -C resizer/yuv_multipass_resize install

build_dm644x:
	$(MAKE) -C v4l2 build_vpfe_vpbe
	$(MAKE) -C fbdev
	$(MAKE) -C resizer/planar_resize
	$(MAKE) -C resizer/yuv_multipass_resize

build_common:
	$(MAKE) -C edma

install_common:
	$(MAKE) -C edma install

clean:
	$(MAKE) -C fbdev clean
	$(MAKE) -C h3a/dm355 clean
	$(MAKE) -C h3a/dm365 clean
	$(MAKE) -C vdce clean
	$(MAKE) -C v4l2 clean
	$(MAKE) -C imp-prev-rsz/dm355 clean
	$(MAKE) -C imp-prev-rsz/dm365 clean
	$(MAKE) -C cir clean
	$(MAKE) -C vdce clean
	$(MAKE) -C edma clean
	$(MAKE) -C gpio clean
	$(MAKE) -C resizer/planar_resize clean
	$(MAKE) -C resizer/yuv_multipass_resize clean

