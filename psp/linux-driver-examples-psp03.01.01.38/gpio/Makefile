obj-m := gpio_test.o 
PWD := $(shell pwd)

INSTALL_DIR=$(FINAL_DEST)/gpio

# Set KERNEL_DIR to your local kernel location

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

install:
	mkdir -p $(INSTALL_DIR)
	cp gpio_test.ko $(INSTALL_DIR)
clean:
	rm -rf *.o *.ko *.mod.c .*.cmd .tmp_versions
