#ifndef _RSIM_H
#define _RSIM_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<fcntl.h>
#include <unistd.h>
#include "opc.h"

int load(FILE* fin,uint8_t* mem);
void retrieve(char* mne, char* ins);
int run_program(uint8_t* pc, uint8_t* ac, char *mne, uint8_t adr,uint8_t* mem);
void display(uint8_t* pc, uint8_t* ac, char *mne);
void sim_cat(char *pc_out, char *mne, char *ac_out, char *output);
int check_adr(int adr);

#endif
