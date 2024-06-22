NAME := kaktus_c

SOURCEDIR := src/
BUILDDIR := build/
TARGETDIR := target/


CC := clang
CCWARNINGS := -Wall -Werror -pedantic -pedantic-errors -fcolor-diagnostics -fcaret-diagnostics -fshow-source-location
CCLIBS :=
CCINCLUDE := -I $(SOURCEDIR)
CCFLAGS := $(CCWARNINGS) $(CCLIBS) $(CCINCLUDE)


SOURCES := $(wildcard $(SOURCEDIR)*.c)
OBJECTS := $(patsubst $(SOURCEDIR)%.c,$(BUILDDIR)%.o,$(SOURCES))

EXEPATH := $(TARGETDIR)$(NAME)

main: $(OBJECTS)
	echo "[ build ] main."
	$(CC) -o $(EXEPATH) $(OBJECTS) $(CCFLAGS)

$(OBJECTS): $(BUILDDIR)%.o: $(SOURCEDIR)%.c
	$(CC) -o $@ -c $< $(CCFLAGS)
