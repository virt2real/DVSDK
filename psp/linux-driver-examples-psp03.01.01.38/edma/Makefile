obj-m := edma_test.o 
PWD := $(shell pwd)
INSTALL_DIR=$(FINAL_DEST)/edma
# Set KERNEL_DIR to your local kernel location

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
install:
	mkdir -p $(INSTALL_DIR)
	cp edma_test.ko $(INSTALL_DIR)
clean:
	rm -rf *.o *.ko *.mod.c .*.cmd .tmp_versions
