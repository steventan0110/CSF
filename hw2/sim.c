/*Weiting Tan
JHED: wtan12*/

#include "rsim.h"

static uint8_t mem[SCRAM_SIZE]; /* memory of the SCRAM */

void run()
{
    //initialize the SCRAM
    uint8_t pc = 0;
    uint8_t ac = 0;

    while (1)
    {

        //fetch the instruction and get the opc_code and address
        uint8_t ir = mem[pc];
        uint8_t opc = (ir >> 4) & 0xf;
        uint8_t adr = ir & 0xf;

        //generate mne that's ready to be outputted
        char mne[9];
        int deci_adr = adr;
        opc_decode_sim(opc, deci_adr, mne);
        mne[8] = '\0';

        if (run_program(&pc, &ac, mne, adr, mem) == 1)
        {
            break;
        }
    }
}

int main(int argc, char *argv[])
{

    //read in from a file
    if (argc <= 2)
    {
        if (argc == 2)
        {
            FILE *fin = fopen(argv[1], "rb");
        
            if (fin == NULL)
            {
                perror("Error opening input file");
                exit(2);
            }
            
            load(fin, mem);
            run();
            fclose(fin);
        }
        else
        {
            load(0, mem);
            run();
        }
    }

    //output to a file the memory
    else if (argc == 3)
    {
        FILE *fin = fopen(argv[1], "rb");
        if (fin == NULL)
        {
            perror("Error opening input file");
            exit(2);
        }
        FILE *fout = fopen(argv[2], "wb");
        if (fout == NULL)
        {
            perror("Error opening output file");
            exit(2);
        }
        int size = load(fin, mem);
        run();

        //now need to dump the memory into the output file
        fwrite(mem, sizeof(uint8_t), size+1, fout);
        fclose(fin);
        fclose(fout);
    }
    else
    {
        //wrong number of arguments inputted
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
