/*Weiting Tan
JHED: wtan12*/
#ifndef _OPC_H
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define _OPC_H
#define SCRAM_SIZE 256


/* convert to hex in a string format */
void to_hexchar(int decimal, char *hex, int numBits);
/* concatenate the string */
void cat(char *out, char *opc, char *add);
/*
 * String representation for given opcode. Returns NULL on error
 * (including for DAT which doesn't have an encoding).
 */
void opc_decode(int opc, int add, char* output);
void opc_decode_sim(int opc, int add, char *output);

#endif
