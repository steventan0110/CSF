/* Weiting Tan
JHED: wtan12
*/
#include "opc.h"
#include "Label.h"
#include "rasm.h"

static uint8_t mem[SCRAM_SIZE]; /* memory of the SCRAM */
static int ca;                  /*current address */
static int adr_used;
static uint8_t opc_array[SCRAM_SIZE]; //store the opcode
//static char add_array[SCRAM_SIZE][sizeof(char)]; //store the address

void toStringMem()
{
    for (int i = 0; i < SCRAM_SIZE; i++)
    {
        printf("mem at address %d is %x\n", i, mem[i]);
    }
}

/* check if multiple number exist.*/
void check_argument(char *str)
{
    int count = 0;
    for (int i = 0; i < (int)strlen(str) - 1; i++)
    {
        if (isdigit(str[i]))
        {
            if (!isdigit(str[i + 1]))
            {
                count++;
            }
        }
    }
    if (count > 1)
    {
        printf("more than one number entered\n");
        exit(6);
    }
}

void free_arr(char **adr)
{
    for (int i = 0; i < ca; i++)
    {
        if ((*(adr + i)) != NULL)
        {
            free(*(adr + i));
            *(adr + i) = NULL;
        }
    }
    free(adr);
}

int main(int argc, char *argv[])
{

    //read in from a file
    if (argc == 2)
    {
        FILE *fin = fopen(argv[1], "rb");
        if (fin == NULL)
        {
            perror("Error opening input file");
            exit(2);
        }
        //for label initialization:
        init_list();

        //initialize the address array:
        char **add_array = malloc(SCRAM_SIZE * sizeof(char));
        for (int i = 0; i < SCRAM_SIZE; i++)
        {
            *(add_array + i) = NULL;
        }

        //for read in
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fin)) != -1)
        {
            //printf("Retrieved line of length %zu :\n", read);
            check_argument(line);
            trim(line);
            //printf("line %s has len %d\n", line, strlen(line));
            parseFile(line, &adr_used, &ca, opc_array, add_array);
        }
        //check if any label has value that's not initialized
        checkList();

        construct(mem, &ca, opc_array, add_array);
        //toString();
        //toStringMem();
        //free the label:
        freeList();
        fclose(fin);
        //remember to free the add array!
        free_arr(add_array);

        for (int i = 0; i < SCRAM_SIZE; i++)
        {
            printf("%c", mem[i]);
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
        //for label initialization:
        init_list();

        //for read in
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        //initialize the address array:
        char **add_array = malloc(SCRAM_SIZE * sizeof(char));
        for (int i = 0; i < SCRAM_SIZE; i++)
        {
            *(add_array + i) = malloc(sizeof(char));
        }

        while ((read = getline(&line, &len, fin)) != -1)
        {
            printf("Retrieved line of length %zu :\n", read);
            trim(line);
            printf("%s\n", line);
            parseFile(line, &adr_used, &ca, opc_array, add_array);
        }
        //check if any label has value that's not initialized
        checkList();

        construct(mem, &ca, opc_array, add_array);
        //toString();
        toStringMem();
        //free the label:
        freeList();
        //now need to dump the memory into the output file
        if (((int)fwrite(mem, sizeof(uint8_t), 256, fout) < 256))
        {
            perror("Error writing to output file");
            exit(3);
        }
        fclose(fin);
        fclose(fout);
    }

    else
    {
        perror("wrong number of arguments inputted");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
