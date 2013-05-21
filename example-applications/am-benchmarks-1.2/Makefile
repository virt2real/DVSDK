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

install:
	@install -d $(DESTDIR)/usr/bin
	@if [ -e dhrystone/Release/dhrystone ] ; then \
		install dhrystone/Release/dhrystone $(DESTDIR)/usr/bin/ ; \
		echo "dhrystone release version installed."; \
	else \
		echo "dhrystone release version not built - nothing to install!"; \
	fi
	@if [ -e whetstone/Release/whetstone ] ; then \
		install whetstone/Release/whetstone $(DESTDIR)/usr/bin/ ; \
		echo "whetstone release version installed."; \
	else \
		echo "whetstone release version not built - nothing to install!" ; \
	fi
	@if [ -e linpack/Release/linpack ] ; then \
		install linpack/Release/linpack $(DESTDIR)/usr/bin/ ; \
		echo "linpack release version installed."; \
	else \
		echo "linpack release version not built - nothing to install!" ; \
	fi
	@install scripts/* $(DESTDIR)/usr/bin

install_debug:
	@install -d $(DESTDIR)/usr/bin
	@if [ -e dhrystone/Debug/dhrystone ] ; then \
		install dhrystone/Debug/dhrystone $(DESTDIR)/usr/bin/ ; \
		echo "dhrystone debug version installed."; \
		echo "NOTE: DEBUG VERSION WILL NOT YIELD MEANINGFUL BENCHMARK RESULTS."; \
	else \
		echo "drhystone debug version not built - nothing to install!"; \
	fi
	@if [ -e whetstone/Debug/whetstone ] ; then \
		install whetstone/Debug/whetstone $(DESTDIR)/usr/bin/ ; \
		echo "whetstone debug version installed."; \
		echo "NOTE: DEBUG VERSION WILL NOT YIELD MEANINGFUL BENCHMARK RESULTS."; \
	else \
		echo "whetstone debug version not built - nothing to install!" ; \
	fi
	@if [ -e linpack/Debug/linpack ] ; then \
		install linpack/Debug/linpack $(DESTDIR)/usr/bin/ ; \
		echo "linpack debug version installed."; \
		echo "NOTE: DEBUG VERSION WILL NOT YIELD MEANINGFUL BENCHMARK RESULTS."; \
	else \
		echo "linpack debug version not built - nothing to install!" ; \
	fi
	@install scripts/* $(DESTDIR)/usr/bin
