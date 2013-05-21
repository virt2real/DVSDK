#
#  Copyright 2010 by Texas Instruments Incorporated.
#  
#

include $(XDCROOT)/packages/xdc/bld/xdc_java.mak

CLASSES  = $(patsubst %.java,%,$(wildcard *.java))
JARFILE  = java/package.jar

JCPATH:=$(XDCROOT)/packages/xdc/rta/java/package.jar

.libraries: $(JARFILE)
$(JARFILE): $(patsubst %,$(CLASSDIR)/%.class,$(CLASSES))

clean::
	$(RM) $(JARFILE)

JTEST = java -classpath java/package.jar:$(XDCROOT)/packages/xdc/rta/java/package.jar ti.targets.omf.elf.Elf32
java.test: java/package.jar
	$(JTEST) tests/repo/client/client.x86U	0x804d9e8
	$(JTEST) tests/repo/client/client.xe64P	0x80002484
	$(JTEST) tests/repo/client/client.xem3 0x804d9e8
#
#  @(#) ti.targets.omf.elf; 1,0,0,38; 2-24-2010 16:41:22; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
#

