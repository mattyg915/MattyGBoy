#ifndef REGISTERSTRUCTURES
#define REGISTERSTRUCTURES

typedef struct Registers {
	// Game Boy CPU uses 8 8-bit registers, F is used for flags
	unsigned char A, B, C, D, E, F, H, L;
} Registers;

typedef struct Pointers {
	// Two 16-bit registers are used for stack pointer and program counter
	unsigned short SP, PC;
} Pointers;

Registers* init_registers();

Pointers* init_pointers();

#endif
