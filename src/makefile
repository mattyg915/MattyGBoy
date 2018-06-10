IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=obj


_DEPS = cpu_control_instructions.h load_instructions.h control_instructions.h bit_rotate_shift_instructions.h logical_instructions.h register_structures.h math_instructions.h helper_functions.h cpu_emulator.h global_declarations.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = cpu_control_instructions.o load_instructions.o control_instructions.o bit_rotate_shift_instructions.o logical_instructions.o mattygboy.o register_structures.o math_instructions.o helper_functions.o cpu_emulator.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mattygboy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
