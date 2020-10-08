#!/bin/sh

############################################################################
#
#  Makefile to compile and link a C++ or Fortran application to 
#  Cantera.
#
#############################################################################

# the name of the executable program to be created
PROG_NAME = __PROGRAM__

# the object files to be linked together.
OBJS = __OBJS__

# additional flags to be passed to the linker. If your program
# requires other external libraries, put them here
LINK_OPTIONS = 


#############################################################################

# the Fortran compiler
FORT = g77

# Fortran compile flags  
FORT_FLAGS = -O3   -fno-second-underscore 

# Fortran libraries
FORT_LIBS = 

# the C++ compiler
CXX = g++

# C++ compile flags
CXX_FLAGS = -O3 -Wall  

# external libraries
EXT_LIBS =  -luser -loneD -lzeroD -lequil -lkinetics -ltransport -lthermo -lctnumerics -lctmath -ltpx -lctspectra -lconverters -lctbase -lsundials_cvodes -lsundials_nvecserial -lctlapack -lctblas -lctf2c 



#------  you probably don't have to change anything below this line -----


# the directory where the Cantera libraries are located
CANTERA_LIBDIR=@CANTERA_LIBDIR@

# required Cantera libraries
CANTERA_LIBS =  

# the directory where Cantera include files may be found.
CANTERA_INCDIR=@CANTERA_INCDIR@

# flags passed to the C++ compiler/linker for the linking step
LCXX_FLAGS = -L$(CANTERA_LIBDIR)  -L/Cantera1.8-Radcal/build/lib/x86_64-unknown-linux-gnu -L/usr/local/lib -O3 -Wall  

# how to compile C++ source files to object files
.cpp.o:
	$(CXX) -c $< -I$(CANTERA_INCDIR) $(CXX_FLAGS)

# how to compile Fortran source files to object files
.f.o: 
	$(FORT) -c $< $(FORT_FLAGS)

PROGRAM = $(PROG_NAME)$(EXE_EXT)

DEPENDS = $(OBJS:.o=.d)

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS) $(LCXX_FLAGS) $(CANTERA_LIBS) $(LINK_OPTIONS) $(EXT_LIBS)  $(FORT_LIBS)

%.d:
	g++ -MM $*.cpp > $*.d

clean:
	$(RM) $(OBJS) $(PROGRAM)

depends: $(DEPENDS)
	cat *.d > .depends
	$(RM) $(DEPENDS) 

TAGS: 
	etags *.h *.cpp

ifeq ($(wildcard .depends), .depends)
include .depends
endif






