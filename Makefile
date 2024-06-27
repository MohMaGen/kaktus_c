NAME := kaktus-c

SOURCEDIR := src/
BUILDDIR := build/
TARGETDIR := target/


CCWARNINGS := -Wall -Werror -pedantic -pedantic-errors
CCLIBS :=
CCINCLUDE := -I $(SOURCEDIR)
DEBUG := -g -gmodules
CCFLAGS := $(CCWARNINGS) $(CCLIBS) $(CCINCLUDE)


SOURCES := $(wildcard $(SOURCEDIR)*.c)
OBJECTS := $(patsubst $(SOURCEDIR)%.c,$(BUILDDIR)%.o,$(SOURCES))
OBJECTS_DEBUG := $(patsubst $(SOURCEDIR)%.c,$(BUILDDIR)debug/%.o,$(SOURCES))

TARGETPATH := $(TARGETDIR)$(NAME)
DEBUGPATH := $(TARGETDIR)debug-$(NAME)

main: $(OBJECTS)
	@echo "[ build ] main."
	$(CC) -o $(TARGETPATH) $(OBJECTS) $(CCFLAGS)

main-run: main
	$(TARGETPATH)

debug: $(OBJECTS_DEBUG)
	@echo "[ build ] main."
	$(CC) -o $(DEBUGPATH) $(OBJECTS_DEBUG) $(CCFLAGS)

debug-run: debug
	$(DEBUGPATH)

debug-gdb: debug
	gdb $(DEBUGPATH)

$(OBJECTS): $(BUILDDIR)%.o: $(SOURCEDIR)%.c
	$(CC) -o $@ -c $< $(CCFLAGS)

$(OBJECTS_DEBUG): $(BUILDDIR)debug/%.o: $(SOURCEDIR)%.c
	$(CC) -o $@ -c $< $(CCFLAGS) $(DEBUG)
