ACLOCAL_AMFLAGS= -I m4
include_HEADERS = \
 include/uPowerSim.h\
 include/simulator.h

bin_PROGRAMS = bin/upowersim
bin_upowersim_SOURCES = \
 src/instr_translator.c\
 src/uPowerSim.c\
 src/simulator.c
bin_upowersim_CPPFLAGS = -I$(top_srcdir)/include
#bin_upowersim_LDADD = libm.so
#bin_upowersim_LDFLAGS = -lm