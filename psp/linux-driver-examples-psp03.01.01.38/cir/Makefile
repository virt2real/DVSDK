# Set KERNEL_DIR to your local kernel location include location
INSTALL_DIR=$(FINAL_DEST)/cir

CC = $(CROSS_COMPILE)gcc -I$(KERNEL_DIR)/include

all:
	$(CC) saCir.c -o saCir

install:
	mkdir -p $(INSTALL_DIR)
	cp saCir $(INSTALL_DIR)

clean:
	rm -rf *.o
