#
# $Source: /cvsroot/cantera/cantera/ext/cvode/Makefile.in,v $
# $Author: hkmoffa $
# $Revision: 1.10 $
# $Date: 2008/12/30 21:49:42 $
#
#----------------------------------------------------------------------------
#                                CVODE                                      
#----------------------------------------------------------------------------
# This file will compile all the CVODE modules in order to make the Unix
# library cvodelib.a. All object (.o) files are removed after the library
# has been created. 
#
# The following variables are used:
#
# COMPILER - set to use the gcc compiler
# OPTS     - list of compiler options
# OBJS     - list of object files in cvodelib.a
#
# Modify the COMPILER and OPTS variables as needed.
#
do_ranlib = 1

all: /Cantera1.8-Radcal/build/lib/x86_64-unknown-linux-gnu/libcvode.a

PURIFY=

PIC_FLAG=-fPIC
   
COMPILER = gcc

OPTS = -I../include   $(CXX_OPT) $(PIC_FLAG)

OBJS = source/cvode.o source/cvdense.o source/dense.o source/cvband.o \
       source/band.o source/cvdiag.o source/cvspgmr.o source/spgmr.o  \
       source/iterativ.o source/cvbandpre.o source/nvector.o source/llnlmath.o


/Cantera1.8-Radcal/build/lib/x86_64-unknown-linux-gnu/libcvode.a: $(OBJS)
	$(RM) /Cantera1.8-Radcal/build/lib/x86_64-unknown-linux-gnu/libcvode.a
	(ar rcv /Cantera1.8-Radcal/build/lib/x86_64-unknown-linux-gnu/libcvode.a $(OBJS))
ifeq ($(do_ranlib),1)
	ranlib /Cantera1.8-Radcal/build/lib/x86_64-unknown-linux-gnu/libcvode.a
endif

source/cvode.o: source/cvode.c include/cvode.h include/llnltyps.h \
                include/nvector.h include/llnlmath.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c cvode.c)

source/cvdense.o: source/cvdense.c include/cvdense.h include/cvode.h \
                  include/dense.h include/llnltyps.h include/nvector.h \
                  include/llnlmath.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c cvdense.c)
 
source/dense.o: source/dense.c include/dense.h include/llnltyps.h \
                include/nvector.h include/llnlmath.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c dense.c)
 
source/cvband.o: source/cvband.c include/cvband.h include/cvode.h \
                 include/band.h include/llnltyps.h include/nvector.h \
                 include/llnlmath.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c cvband.c)
 
source/band.o: source/band.c include/band.h include/llnltyps.h \
               include/nvector.h include/llnlmath.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c band.c)
 
source/cvdiag.o: source/cvdiag.c include/cvdiag.h  include/cvode.h \
                 include/llnltyps.h include/nvector.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c cvdiag.c)
 
source/cvspgmr.o: source/cvspgmr.c include/cvspgmr.h include/cvode.h \
                  include/llnltyps.h include/nvector.h include/llnlmath.h \
                  include/iterativ.h include/spgmr.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c cvspgmr.c)
 
source/spgmr.o: source/spgmr.c include/spgmr.h include/iterativ.h \
                include/llnltyps.h include/nvector.h include/llnlmath.h 
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c spgmr.c)
 
source/iterativ.o: source/iterativ.c include/iterativ.h include/llnltyps.h \
                   include/nvector.h include/llnlmath.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c iterativ.c)
 
source/cvbandpre.o: source/cvbandpre.c include/cvbandpre.h include/cvode.h \
                    include/nvector.h include/llnltyps.h include/llnlmath.h \
                    include/band.h 
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c cvbandpre.c)
 
source/nvector.o: source/nvector.c include/nvector.h include/llnltyps.h \
                 include/llnlmath.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c nvector.c)
 
source/llnlmath.o: source/llnlmath.c include/llnlmath.h include/llnltyps.h
	(cd source; $(PURIFY) $(COMPILER) $(OPTS) -c llnlmath.c)

$(OBJS): Makefile

clean:
	$(RM)  /Cantera1.8-Radcal/build/lib/x86_64-unknown-linux-gnu/libcvode.a
	$(RM)  $(OBJS)

depends:

