/*Weiting Tan
JHED: wtan12*/

#include "opc.h"

#define MAXIN 256

static uint8_t SHIFT = 4;

void disassemble(uint8_t opc, uint8_t address,
                 int d, int count)
{
    char hex[3];
    //shift to right to get op-code
    opc = (d >> SHIFT) & 0xf;
    //do not shift to get the address/argument byte
    address = d & 0xf;


    //Now process the opc and address
    char mne[8];

    to_hexchar(count, hex, 2);
    hex[2] = '\0'; 
    opc_decode(opc, address, mne);
    mne[7] ='\0';
    printf("0x%s  %s\n", hex, mne);
}

int main(int argc, char *argv[])
{

    uint8_t opc = 0;
    uint8_t address = 0;
    int c;
    int count = 0;

    //printf("reach here %d\n", d);
    //read in from a file
    if (argc == 2)
    {
        FILE *fin = fopen(argv[1], "rb");
        if (fin == NULL)
        {
            perror("Error opening file");
            exit(2);
        }
        else
        {
            while (((c = fgetc(fin))!= EOF) && (count < MAXIN))
            {
                
                disassemble(opc, address, c, count);
                count++;
            }
            fclose(fin);
        }
    }
    //read in from stdin
    else if (argc ==1)
    {
        while (((c = getc(stdin)) != EOF) && (count < MAXIN))
        {
            disassemble(opc, address, c, count);
            count++;
        }
    }
    else
    {
        //wrong number of arguments inputted
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
