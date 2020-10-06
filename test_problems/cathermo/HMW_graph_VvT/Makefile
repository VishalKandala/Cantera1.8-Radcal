#!/bin/sh

############################################################################
#
#  Makefile to compile and link a C++ application to 
#  Cantera.
#
#############################################################################

# addition to suffixes
.SUFFIXES : .d

# the name of the executable program to be created
PROG_NAME = HMW_graph_VvT

# the object files to be linked together. List those generated from Fortran
# and from C/C++ separately
OBJS = HMW_graph_VvT.o sortAlgorithms.o

# additional flags to be passed to the linker. If your program
# requires other external libraries, put them here
LINK_OPTIONS = 

#############################################################################

PURIFY=

# Check to see whether we are in the msvc++ environment
os_is_win = 0

# Fortran libraries
ifeq (1, 0)
FORT_LIBS = 
else
FORT_LIBS =
endif

# the C++ compiler
CXX = g++

# C++ compile flags
CXX_FLAGS = -O3 -Wall  

# Ending C++ linking libraries
LCXX_END_LIBS = -lctf2c -lm

# the directory where the Cantera libraries are located
CANTERA_LIBDIR=/home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu

# required Cantera libraries
CANTERA_LIBS =  -luser -loneD -lzeroD -lequil -lkinetics -ltransport -lthermo -lctnumerics -lctmath -ltpx -lctspectra -lconverters -lctbase -lcvode -lctlapack -lctblas -lctf2c -lctcxx

# Dependencies for CANTERA_LIBS
CANTERA_LIBS_DEP =  /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libuser.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/liboneD.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libzeroD.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libequil.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libkinetics.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libtransport.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libthermo.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libctnumerics.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libctmath.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libtpx.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libctspectra.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libconverters.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libctbase.a /home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu/libctf2c.a $(CANTERA_LIBDIR)/libctcxx.a

# the directory where Cantera include files may be found.
CANTERA_INCDIR=/home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/include/cantera
INCLUDES=-I$(CANTERA_INCDIR) -I$(CANTERA_INCDIR)/kernel

# flags passed to the C++ compiler/linker for the linking step
LCXX_FLAGS = -L$(CANTERA_LIBDIR)  -L/home/wenjiang/Downloads/cantera-1.8-Duffour-test/build/lib/x86_64-unknown-linux-gnu -O3 -Wall  

# How to compile C++ source files to object files
.cpp.o:
	$(PURIFY) $(CXX) -c $< $(INCLUDES) $(CXX_FLAGS)

# How to compile the dependency file
.cpp.d:
	g++ -MM $(INCLUDES) $(CXX_FLAGS) $*.cpp > $*.d

# List of dependency files to be created
DEPENDS=$(OBJS:.o=.d)

# Program Name
PROGRAM = $(PROG_NAME)$(EXE_EXT)

all: $(PROGRAM) .depends V_standalone

$(PROGRAM): $(OBJS) $(CANTERA_LIBS_DEP)
	$(PURIFY) $(CXX) -o $(PROGRAM) $(OBJS) $(LCXX_FLAGS) $(LINK_OPTIONS) \
                  $(CANTERA_LIBS)  $(FORT_LIBS) \
                  $(LCXX_END_LIBS)


# Add an additional target for stability:
$(OBJS):  $(CANTERA_LIBDIR)/libctbase.a $(CANTERA_LIBDIR)/libthermo.a


V_standalone: V_standalone.o
	 $(CXX) -o V_standalone V_standalone.o \
               $(LCXX_FLAGS) $(LINK_OPTIONS)  $(LCXX_END_LIBS)

# depends target -> forces recalculation of dependencies
depends:
	make .depends

.depends: $(DEPENDS)
	cat $(DEPENDS) > .depends

# Do the test -> For the windows vc++ environment, we have to skip checking on
#                whether the program is uptodate, because we don't utilize make
#                in that environment to build programs.
test:
ifeq ($(os_is_win), 1)
else
	@ make -s $(PROGRAM)
endif
	@ ./runtest

clean:
	$(RM) $(OBJS) $(PROGRAM) $(DEPENDS) .depends *.o
	../../../bin/rm_cvsignore
	(if test -d SunWS_cache ; then \
           $(RM) -rf SunWS_cache ; \
         fi )


ifeq ($(wildcard .depends), .depends)
include .depends
endif
