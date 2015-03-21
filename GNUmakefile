# -*- Makefile -*-

#
# step #1 - system specific compilers, setttings etc
#

OSTYPE := $(shell uname -s)

#
#
#

ifeq ($(CONFIG),) # not defined

include build/GNUmakefile.config # default is debug

endif


#
# external libraries
#

LOCAL_INCLUDE =

#
# utilities
#

ECHO := /bin/echo

#
# defines
#

DEFS  :=

#
# compiler flags, dependncy generation and implicit build rules
#

-include build/GNUmakefile.compiler
-include build/GNUmakefile.ABI
-include build/GNUmakefile.depends
-include build/GNUmakefile.rules

#
# sources, objects and targets
#
# object files - done by string substitution
#

SRCS_SIMPLEX := main.cpp
OBJS_SIMPLEX := $(addsuffix .o, $(basename $(SRCS_SIMPLEX)))	
DEPS_SIMPLEX := $(addsuffix .d, $(basename $(SRCS_SIMPLEX)))

OBJS := $(OBJS_SIMPLEX)
DEPS := $(DEPS_SIMPLEX)

# all targets

SIMPLEX := sim

.PHONY: all tags dox clean realclean

all: $(SIMPLEX)

$(SIMPLEX): $(OBJS_SIMPLEX)
	$(LD) $(LDFLAGS) -o $@ $(wordlist 1,10000000,$^) -L/usr/local/lib $(SYSLIB)	

#dependencies
-include $(DEPS)

tags:
	@(find . -name "*.h" -print | etags -)
	@(find . -name "*.cpp" -print | etags -a -)
	@(find . -name "*.cc" -print | etags -a -)
	@/bin/echo "TAGS updated"

dox:
	doxygen

clean:
	-rm -rf $(SIMPLEX)
	-rm -rf $(OBJS)

realclean:
	-rm -rf $(SIMPLEX)
	-rm -rf $(OBJS)
	-rm -rf $(DEPS)
	-rm -rf TAGS
