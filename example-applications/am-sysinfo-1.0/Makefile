-include DIRS
-include ../../Rules.make

all: debug release

debug:
	for dir in $(DIRS); do \
                make -C $$dir/Debug; \
        done

release:
	for dir in $(DIRS); do \
                make -C $$dir/Release; \
	done

clean:
	for dir in $(DIRS); do \
                make -C $$dir/Release clean; \
                make -C $$dir/Debug clean; \
	done
	@rm -f `find . -name "*.map"`
	@rm -f `find . -name "*.lst"`

install:
	@install -d $(DESTDIR)/usr/bin
	@if [ -e mem_util/Release/mem_util.elf ] ; then \
		install mem_util/Release/mem_util.elf $(DESTDIR)/usr/bin/mem_util ; \
		echo "mem_util release version installed."; \
	else \
		echo "mem_util release version not built - nothing to install!"; \
	fi

install_debug:
	@install -d $(DESTDIR)/usr/bin
	@if [ -e mem_util/Debug/mem_util.elf ] ; then \
		install mem_util/Debug/mem_util.elf $(DESTDIR)/usr/bin/mem_util ; \
		echo "mem_util debug version installed."; \
	else \
		echo "mem_util debug version not built - nothing to install!"; \
	fi

