#ifndef _RASM_H
#define _RASM_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "opc.h"
#include "Label.h"




int check_digit(const char* str);
void trim(char* str);
void loadInstruc(const char *ins,int*used, int* ca, uint8_t* opc_array, char** adr_array);
void parseFile(char* input, int*used,int* ca, uint8_t*opc, char** adr);
int loadTempLabel(const char *label);
int addCheck(const char *add);
int datacheck(char *data);
void construct(uint8_t* mem, int *ca, uint8_t *opc_array, char **adr_array);

#endif
