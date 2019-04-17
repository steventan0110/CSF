/* Weiting Tan
JHED: wtan12
*/
#include "opc.h"
#include "Label.h"

static uint8_t mem[SCRAM_SIZE];                   /* memory of the SCRAM */
static uint8_t ca;                                /*current address */
static uint8_t cl;                                // current line number
static uint8_t opc_array[SCRAM_SIZE][LABEL_SIZE]; //store the opcode
static char add_array[SCRAM_SIZE][LABEL_SIZE];    //store the address

/** process the input file and read in the file line by line.*/
char **readin(FILE *fin)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fin)) != -1)
    {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }
    return &line;
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
            // char **line = readin(fin);
            // for (int i = 0; i < strlen(line); i++)
            // {
            //     //trim the lines so that spaces are removed
            //     trim(*(line+i));
            // }
            init_list();
            parseFile(fin, &cl, &ca, opc_array, add_array);
            checkList();
            construct(mem, &ca, opc_array, add_array);
            for (int i = 0; i < ca; i++)
            {
                printf("%c", mem[i]);
            }
            freeList();
            fclose(fin);
        }
        else
        {
            init_list();
            parseFile(stdin, &cl, &ca, opc_array, add_array);
            checkList();
            construct(mem, &ca, opc_array, add_array);
            for (int i = 0; i < ca; i++)
            {
                printf("%c", mem[i]);
            }
            freeList();
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
        init_list();
        parseFile(fin, &cl, &ca, opc_array, add_array);
        checkList();
        construct(mem, &ca, opc_array, add_array);
        for (int i = 0; i < ca; i++)
        {
            fprintf(fout, "%c", mem[i]);
        }
        freeList();
        fclose(fin);
        fclose(fout);

        // //now need to dump the memory into the output file
        // if (((int)fwrite(mem, sizeof(uint8_t), 256, fout) < 256))
        // {
        //     perror("Error writing to output file");
        //     exit(3);
        // }
        // fclose(fin);
        // fclose(fout);
    }
    else
    {
        perror("wrong number of arguments inputted");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}