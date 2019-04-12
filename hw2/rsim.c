/*Weiting Tan
JHED: wtan12*/
#include "rsim.h"

//load the content in the file/stdin into the memory of 256 bytes, truncate if too long
void load(FILE *fin, uint8_t *mem)
{
    int c;
    int num = 0;
    while (((c = fgetc(fin)) != EOF) && (num < SCRAM_SIZE))
    {
        mem[num] = c;
        num++;
    }
    if (!feof(fin))
    {
        fprintf(stderr, "Program too long, truncated to %d bytes.\n",
                SCRAM_SIZE);
    }
}

void retrieve(char *mne, char *ins)
{
    for (int i = 0; i < 3; i++)
    {
        ins[i] = mne[i];
    }
    ins[3] = '\0';
}

void sim_cat(char *pc_out, char *mne, char *ac_out, char *output)
{
    output[0] = '0';
    output[1] = 'x';
    //add the address into final output
    for (int i = 0; i < 3; i++)
    {
        output[2 + i] = pc_out[i];
    }
    output[4] = ' ';
    output[5] = ' ';
    for (int i = 0; i < 8; i++)
    {
        output[6 + i] = mne[i];
    }
    output[14] = ' ';
    output[15] = ' ';
    output[16] = ' ';
    output[17] = ' ';
    output[18] = 'A';
    output[19] = 'C';
    output[20] = 'C';
    output[21] = '=';
    output[22] = '0';
    output[23] = 'x';
    output[24] = *ac_out;
    output[25] = *(ac_out + 1);
    output[26] = '\0';
}

//display the message as required and also increment pc
void display(uint8_t *pc, uint8_t *ac, char *mne)
{
    //prepare for catenation for ACC
    char ac_out[3];
    //for the address, converted by programming counter:
    char pc_out[3];
    //prepare for concatenation
    char final_out[27];
    int deci_pc = *pc;
    int deci_ac = *ac;
    to_hexchar(deci_ac, ac_out, 2);
    to_hexchar(deci_pc, pc_out, 2);
    //display the simulation
    sim_cat(pc_out, mne, ac_out, final_out);

    printf("%s\n", final_out);

    *pc = *pc + 1;
}


int check_adr(int size, int adr)
{
    if (size < adr)
    {
        return 1;
    }
    return 0;
}

//return 0 if keep running, 1 if stop
int run_program(uint8_t *pc, uint8_t *ac, char *mne, uint8_t adr, uint8_t *mem, int size)
{

    //retrieve the instruction to compare with all the instructions:
    char ins[4];
    retrieve(mne, ins);

    //C flag
    uint8_t C = 0;

 

    if (strcmp(ins, "HLT") == 0)
    {
        *pc = 0;
        display(pc, ac, mne);
        return 1;
    }
    else if (strcmp(ins, "EXT") == 0)
    {

        display(pc, ac, mne);
        adr = adr << 4;
        if (run_program(pc, ac, mne, adr, mem, size) == 1)
        {
            return 1;
        }
        return 0;
    }
    else if (strcmp(ins, "LDA") == 0)
    {

        if (check_adr(size, adr))
            exit(5);

        *ac = mem[adr];
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "LDI") == 0)
    {
        if (check_adr(size, adr))
            exit(5);
        uint8_t mbr = mem[adr];
        if (check_adr(size, mbr))
            exit(5);

        *ac = mem[mbr];
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "STA") == 0)
    {

        if (check_adr(size, adr))
            exit(5);
        mem[adr] = *ac;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "STI") == 0)
    {

        if (check_adr(size, adr))
            exit(5);
        uint8_t mbr = mem[adr];
        if (check_adr(size, mbr))
            exit(5);

        mem[mbr] = *ac;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "ADD") == 0)
    {

        if (check_adr(size, adr))
            exit(5);

        if ((int)*ac + (int)mem[adr] > 255)
            C = 1;

        *ac = *ac + mem[adr];
        display(pc, ac, mne);
        return 0;
    }

    else if (strcmp(ins, "SUB") == 0)
    {

        if (check_adr(size, adr))
            exit(5);

        *ac = *ac + ~mem[adr] + 1;
        //check the flag
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "JMP") == 0)
    {

        display(pc, ac, mne);
        if (check_adr(size, adr))
            exit(4);

        *pc = adr;
        return 0;
    }
    else if (strcmp(ins, "JMZ") == 0)
    {

        display(pc, ac, mne);
        if (*ac == 0)
        {
            if (check_adr(size, adr))
                exit(4);

            *pc = adr;
        }
        return 0;
    }
    else if (strcmp(ins, "AND") == 0)
    {

        if (check_adr(size, adr))
            exit(5);
        *ac = *ac & mem[adr];
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "IOR") == 0)
    {

        if (check_adr(size, adr))
            exit(5);
        *ac = *ac | mem[adr];
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "XOR") == 0)
    {

        if (check_adr(size, adr))
            exit(5);
        *ac = *ac ^ mem[adr];
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "ADL") == 0)
    {

        if (adr < 16 && (adr >> 3) == 1)
            adr = 0xF0 + adr;
        if ((int)*ac + (int)adr > 255)
            C = 1;

        *ac = *ac + adr;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "ADC") == 0)
    {

        if (check_adr(size, adr))
            exit(5);

        if ((int)*ac + (int)mem[adr] + C > 255)
            C = 1;

        *ac = *ac + mem[adr] + C;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "SBB") == 0)
    {

        if (check_adr(size, adr))
            exit(5);

        if ((int)*ac + (int)~mem[adr] + C > 255)
            C = 1;

        *ac = *ac + (~mem[adr]) + C;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "NEG") == 0)
    {

        *ac = (~*ac) + 1;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "COM") == 0)
    {

        *ac = ~*ac;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "CLR") == 0)
    {

        *ac = 0;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "SET") == 0)
    {

        *ac = 0xff;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "RTL") == 0)
    {

        *ac = ((*ac << 1) | (*ac >> 7)) & 0xff;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "RTR") == 0)
    {

        *ac = ((*ac << 7) | (*ac >> 1)) & 0xff;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "LSL") == 0)
    {

        *ac = *ac << 1;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "LSR") == 0)
    {

        *ac = *ac >> 1;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "ASR") == 0)
    {

        *ac = ((*ac >> 1) & 0x7f) | (*ac & 0x80);
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "TST") == 0)
    {

        if (*ac != 0)
        {
            *ac = 0x01;
        }
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "CLC") == 0)
    {

        C = 0;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "SEC") == 0)
    {

        C = 1;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "TCA") == 0)
    {

        *ac = C;
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "TVA") == 0)
    {

        *ac = C ^ (adr >> 7);
        display(pc, ac, mne);
        return 0;
    }
    else if (strcmp(ins, "JAL") == 0)
    {

        *ac = *pc + 1;
        display(pc, ac, mne);
        *pc = *ac;
        return 0;
    }
    else if (strcmp(ins, "NOP") == 0)
    {

        //do nothing
        display(pc, ac, mne);
        return 0;
    }
    else
    {
        exit(1);
    }
}
