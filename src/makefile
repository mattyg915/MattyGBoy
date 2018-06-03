IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=obj


_DEPS = bit_rotate_shift_instructions.h logical_instructions.h register_structures.h math_instructions.h helper_functions.h cpu_emulator.h global_declarations.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = bit_rotate_shift_instructions.o logical_instructions.o mattygboy.o register_structures.o math_instructions.o helper_functions.o cpu_emulator.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJTEST = bit_rotate_shift_instructions.o logical_instructions.o unit_tests.o register_structures.o math_instructions.o helper_functions.o cpu_emulator.o
OBJTEST = $(patsubst %,$(ODIR)/%,$(_OBJTEST))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mattygboy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

unit_tests: $(OBJTEST)
	$(CC) -o $@ $^ $(CFLAGS)
