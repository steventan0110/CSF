#ifndef _RASM_H
#define _RASM_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "opc.h"
#include "Label.h"




char* trim(char* str);

void loadInstruc(const char *ins, uint8_t* ca, uint8_t** opc_array, char** adr_array);
void parseFile(FILE *fin, uint8_t* cl, uint8_t* ca, uint8_t**opc, uint8_t**adr);
void loadTempLabel(const char *label);
int addCheck(const char *add);
int datacheck(char *data);
void construct(uint8_t* mem, uint8_t *ca, uint8_t **opc_array, char **adr_array);

#endif