.PHONY: build test clean help

CC = clang
AR = ar
CFLAGS = -Wall --std=c11
OBJDIR = build/obj
LIBDIR = build/lib
BINDIR = build/bin
LIB = $(LIBDIR)/libcollex.a

SRCFILES := $(wildcard src/*.c)
MODULES  := $(basename $(notdir $(SRCFILES)))
OBJS := $(patsubst %, $(OBJDIR)/%.o, $(MODULES))

TESTFILES := $(wildcard tests/test_*.c)
TESTS := $(basename $(notdir $(TESTFILES)))
TESTEXES := $(patsubst %, $(BINDIR)/%, $(TESTS))


help:
	@echo "This Makefile builds a modular C project using a static library architecture. It compiles individual modules into object files, archives them into a static library (libcollex.a), and organizes all output files into a structured build/ directory."
	@echo "Commands:"
	@echo "\t- build \t\t Compile this project"
	@echo "\t- test  \t\t Compile this project"
	@echo "\t- clean \t\t Clean build directory"

build: $(OBJS) 
	@mkdir -p $(LIBDIR)
	$(AR) rcs $(LIB) $^

$(OBJDIR)/%.o: src/%.c include/%.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf build

test: $(TESTEXES)
	@for test in $(TESTEXES); do echo "Running $$test..."; $$test || exit 1; done

$(BINDIR)/%: $(TESTFILES) $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@
