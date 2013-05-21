all:
		$(MAKE) -C build TYPE=nand
		$(MAKE) -C build TYPE=nor
DM6441:
		$(MAKE) -C build TYPE=nand DEVICE=DM6441
		$(MAKE) -C build TYPE=nor DEVICE=DM6441
		
DM6441_LV:
		$(MAKE) -C build TYPE=nand DEVICE=DM6441_LV
		$(MAKE) -C build TYPE=nor DEVICE=DM6441_LV
		
clean:
		$(MAKE) -C build TYPE=nand clean
		$(MAKE) -C build TYPE=nor clean
%::
		$(MAKE) -C build TYPE=nand $@
		$(MAKE) -C build TYPE=nor $@
		
