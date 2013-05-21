all:
		$(MAKE) -C build TYPE=nand
		$(MAKE) -C build TYPE=nor
clean:
		$(MAKE) -C build TYPE=nand clean
		$(MAKE) -C build TYPE=nor clean
%::
		$(MAKE) -C build TYPE=nand $@
		$(MAKE) -C build TYPE=nor $@
		
