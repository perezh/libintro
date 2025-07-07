# object files for shared libraries need to be compiled as position independent
# code (-fPIC) because they are mapped to any position in the address space.

VERSION := 2022.1

CFLAGS += -O0 -Wall -Werror -I./include -std=c99 -fPIC
ifndef RANLIB
	RANLIB = ranlib
endif

# COMPILING SETUP
CC        = gcc
LD        = ld
AR        = ar
RANLIB    = ranlib

all: lib/libintro.a bin/test_io bin/test_random

obj/%.o: src/%.c Makefile
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

lib/libintro.a: obj/intro.o
	mkdir -p $(@D)
	$(AR) rc $@ $^ && $(RANLIB) $@

lib/libintro.so: obj/intro.o
	mkdir -p $(@D)
	$(CC) -shared $^ -o $@

ctags:
	geany -g intro.c.tags ./src/*.c
	mv intro.c.tags ./geany-ctags

.PHONY: deb
deb: lib/libintro.a
	rm -rf build/deb

	# temporary fpm source
	mkdir -p build/deb/libintro/usr/local
	cp -r $(addprefix ./, include lib) build/deb/libintro/usr/local
	# geany ctags
	#mkdir -p build/deb/libintro/usr/share/geany/tags
	#cp ./geany-ctags/*.tags build/deb/libintro/usr/share/geany/tags
	mkdir -p build/deb/libintro/usr/local/share/man/man3
	#cp -r $(MANS) build/deb/libintro/usr/local/share/man/man3
	fpm \
	    --after-install postinst \
	    --after-remove postrm \
	    --category libs \
	    --chdir build/deb/libintro \
	    --deb-priority optional \
	    --description "Intro_SW library for C" \
	    --input-type dir \
	    --maintainer "Intro_SW <perezh@unican.es>" \
	    --name libintro \
	    --output-type deb \
	    --package build/deb \
	    --provides libintro \
	    --replaces libintro \
	    --url https://www.istr.unican.es/asignaturas/intro_sw/ \
	    --vendor Intro_SW \
	    --version $(VERSION) \
	    .

	rm -rf build/deb/libintro

documentation:
	( cat doc/config/Doxyfile ; echo "PROJECT_NAME= libintro" ) | doxygen -

bin/test_io: tests/test_io.c lib/$(wildcard libintro.*)
	mkdir -p ./bin
	$(CC) -o $@ $< $(CFLAGS) -L./lib -lintro

bin/test_random: tests/test_random.c lib/$(wildcard libintro.*)
	mkdir -p ./bin
	$(CC) -o $@ $< $(CFLAGS) -L./lib -lintro

install: lib/$(wildcard libintro.*)
	sudo cp lib/libintro.* /usr/local/lib
	sudo cp include/* /usr/local/include

windows: windows/libintro-win32.a

windows/%.o: windows/%.c Makefile
	$(CC) -m32 -c -o $@ $< $(CFLAGS)

windows/libintro-win32.a: windows/intro.o
	$(AR) rc $@ $^ && $(RANLIB) $@

.PHONY: all clean

clean:
	rm -rf obj lib bin tmp
	rm -f *~
