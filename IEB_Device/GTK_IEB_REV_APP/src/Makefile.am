## Process this file with automake to produce Makefile.in

INCLUDES = \
	-I$(top_srcdir)/intl \
	$(GNOME_INCLUDEDIR)

bin_PROGRAMS = ieb

ieb_SOURCES = \
	main.c main.h \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	fnd_test.c fnd_test.h \
	dot_test.c dot_test.h \
	led_test.c led_test.h \
	st_motor_test.c st_motor_test.h \
	dc_motor_test.c dc_motor_test.h 

ieb_LDADD = $(GNOME_LIBDIR) $(GNOMEUI_LIBS) $(INTLLIBS)

