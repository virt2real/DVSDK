# --COPYRIGHT--,EPL
#  Copyright (c) 2008 Texas Instruments and others.
#  All rights reserved. This program and the accompanying materials
#  are made available under the terms of the Eclipse Public License v1.0
#  which accompanies this distribution, and is available at
#  http://www.eclipse.org/legal/epl-v10.html
# 
#  Contributors:
#      Texas Instruments - initial implementation
# 
# --/COPYRIGHT--*/

#
#  ======== xdc_java.mak ========
#  Generic rules for making Java jars from java sources contained in 
#  RTSC packages.
#

ifndef JDK
    $(error JDK must be defined to point to a Java Development Kit)
endif

#
# Compute the list of all jars supplied by prerequisite packages (including .)
#
JARS := $(wildcard $(patsubst %,%/java/*.jar,$(shell $(FINDPKGS) -d -a .)))

#
# CLASSTOP - directory containing class files (not including the package name)
# CLASSDIR - the full directory where class files are written
#
# Note: PKGDIR and XPKGPATH are defined by package.mak 
#    PKGDIR	the RTSC package name (with '/'s instead of '.'s)
#    XPKGPATH 	the full package path with all ^'s expanded as appropriate
#
CLASSTOP   = java/classes
CLASSDIR   = $(CLASSTOP)/$(PKGDIR)

ifeq (,$(wildcard java))
    $(shell $(MKDIR) java)
endif
ifeq (,$(wildcard $(CLASSTOP)))
    $(shell $(MKDIR) $(CLASSTOP))
endif

#
#  Define Java classpath to include all jars (JARS) followed by RTSC package
#  path
#
JARP := $(if $(JARS),$(subst $(space),$(PATHCHAR),$(JARS))$(PATHCHAR),)
JCPATH = $(subst ;,$(PATHCHAR),$(JARP)$(subst $(space),\$(space),$(XPKGPATH)))

#
#  Rules for building class files and jars ...
#
#  NOTE: This pattern rule should only match jars created in the 
#       current working directory (or below); otherwise, jar dependencies that
#	reference jars in other packages will trigger this jar rule in an
#	attempt to build the prequisite jar!
#
java/%.jar ./%.jar $(CURDIR)/%.jar:
	@$(MSG) making $@ "(from $(PKGDIR))" ...
	$(JDK)/bin/jar cf $@ -C $(CLASSTOP) ./$(PKGDIR)
	
$(CLASSDIR)/%.class:%.java 
	@$(MSG) javac $< ...
	$(JDK)/bin/javac $(JCOPTS) -classpath "$(JCPATH)" -d $(CLASSTOP) $<

clean::
	$(RMDIR) $(CLASSTOP)
#
#  @(#) xdc.bld; 1, 0, 2,238; 2-22-2010 10:33:33; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
#

