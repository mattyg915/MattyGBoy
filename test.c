/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/2018 13:31:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
	// Handle optional command line arguments
	int flag;
	// Initializing values for all registers
	int eax_init = 0; int ebx_init = 0; int ecx_init = 0; int edx_init = 0;
	int esi_init = 0; int edi_init = 0; int ebp_init = 0; int eip_init = 0;
	int esp_init = 0;
	// Check variable for verbose flag
	int verbose = 0;
	while ((flag = getopt(argc, argv, "i:s:B:a:b:c:d:S:D:v")) != -1) {
		switch (flag) {
			case 'i':
				eip_init = strtol(optarg, NULL, 16);
				break;
			case 's':
				esp_init = strtol(optarg, NULL, 16);
                break;
			case 'B':
				ebp_init = strtol(optarg, NULL, 16);
                break;
			case 'a':
				eax_init = strtol(optarg, NULL, 16);
                break;
			case 'b':
				ebx_init = strtol(optarg, NULL, 16);
                break;
			case 'c':
				ecx_init = strtol(optarg, NULL, 16);
                break;
			case 'd':
				edx_init = strtol(optarg, NULL, 16);
                break;
			case 'S':
				esi_init = strtol(optarg, NULL, 16);
                break;
			case 'D':
				edi_init = strtol(optarg, NULL, 16);
                break;
			case 'v':
				verbose = 1;
                break;
		}
	}
	if (optind == argc) { // Check for non-optional filename argument
		printf("USAGE: ./xsim [.o filename]\n");
		exit(1);
	}
	
	//unsigned char *virtual_memory = malloc(sizeof(char) * 10485760);

	// Read instructions into memory, track how many are read
	int inst_read = 0;
	FILE *binary_file = fopen(argv[optind], "rb"); // Open newly dumped file
	/*
	char inst_line[5];
	while (fgets(inst_line, 4, binary_file) != NULL) {
		// Convert to single-byte number and store in memory array
		virtual_memory[inst_read] = (unsigned char)strtol(inst_line, NULL, 16);
		inst_read++;
	}
	*/
	long filelen;
	fseek(binary_file, 0, SEEK_END);
	filelen = ftell(binary_file);
	rewind(binary_file);
	unsigned char *virtual_memory = malloc((filelen+1)*sizeof(char));
	fread(virtual_memory, filelen, 1, binary_file);
	fclose(binary_file);
	
	for (int i = 0; i < filelen; i++) {
		printf("instruction at %d is %x\n",i, virtual_memory[i]);
	}

}
