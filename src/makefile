IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=obj


_DEPS = register_structures.h math_instructions.h helper_functions.h cpu_emulator.h global_declarations.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = mattygboy.o register_structures.o math_instructions.o helper_functions.o cpu_emulator.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJTEST = unit_tests.o register_structures.o math_instructions.o helper_functions.o cpu_emulator.o
OBJTEST = $(patsubst %,$(ODIR)/%,$(_OBJTEST))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mattygboy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

tests: $(OBJTEST)
	$(CC) -o $@ $^ $(CFLAGS)
