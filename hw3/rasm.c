/*
Weiting Tan
JHED:wtan12
*/
#include "rasm.h"
#define LINE_SIZE 128
#define LABEL_SIZE 32


void check_org(char* str)
{
    char opc[4];
    for (int i = 0; i < 3; i++)
    {
        *(opc + i) = *(str+ i);
    }
    opc[3] = '\0';
    int num = opc_check(opc);
    if (num == 33)
    {
        printf("ORG shouldn't has label\n");
        exit(7);
    }

}
int check_digit(const char *str)
{
    //printf("The number being checked: %s\n",str);
    for (int i = 0; i < (int)strlen(str); i++)
    {
        if ((!isdigit(str[i])) &&(!isalpha(str[i])))
        {
            return 0;
        }
    }
    return 1;
}
/*
 * This helper function trims leading and trailing white space as well as comment
 * of the input string and return a new pointer to the trimmed substring.
 */
void trim(char *str)
{

    int len = strlen(str);
    char out[len + 1];
    int count = 0;
    //printf("reach here %d\n", len);
    if (isalpha(str[0]))
    {
        //check if the colon for label is present
        char* c;
        c = strchr(str, ':');
        if (c== NULL)
        {
            printf("bad label\n");
            exit(7);
        }
    }
    for (int i = 0; i < len; i++)
    {
        if ((*(str + i) == ' ') || (*(str + i) == '\t') || (*(str + i) == '\n'))
        {
            //do nothing, let i increment
        }
        else if ((*(str + i)) == ';')
        {

            *(out + count) = '\0';
            //reach comment, reak the loop
            strcpy(str, out);
            break;
        }
        else
        {

            //string value should be copied
            *(out + count) = *(str + i);
            count++;
        }
    }
    *(out + count) = '\0';
    strcpy(str, out);
}

void labelCheck(const char *str)
{
    if (!isalpha(str[0]))
    {
        fprintf(stderr, "Error: illegal label.\n");
        exit(7);
    }
    for (int i = 0; i < (int)strlen(str); i++)
    {
        if ((!isalpha(str[i])) && (!isdigit(str[i])) && (str[i] != '_'))
        {
            fprintf(stderr, "Error: illegal label encountered.\n");
            exit(7);
        }
    }
    char opc[4];
    for (int i = 0; i < 3; i++)
    {
        *(opc + i) = *(str + i);
    }
    opc[3] = '\0';
    if ((opc_check(opc)) != -1)
    {
        //the opcode shouldn't be find in the first three alphabet
        printf("bad label, invalid argument.\n");
        exit(6);
    }
    return;
}

void loadLabel(const char *label, int add)
{
    if (find(label) == 1)
    { // if label already exist
        if (getLabelAdd(label) == -1)
        {
            updateLabel(label, add);
        }
        else
        {
            fprintf(stderr, "Error: Label \"%s\" already defined.\n", label);
            exit(7);
        }
    }
    else
    {
        append(label, add);
    }
}

/*
 * Parse the file line by line and check for error as well as load them into respective 
 * arrays using helper functions.
 */
void parseFile(char *input, int *used, int *ca, uint8_t *opc, char **adr)
{

    //printf("%s\n", input);
    int len = strlen(input);
    if (!len)
    {
        // the input is empty line
        //do nothing, move to next line
        return;
    }

    char temp[len];
    char *colon;     // position of the colon.
    char label[len]; // string name of label

    colon = strchr(input, ':');

    if (!colon)
    { // if only instruction
        //printf("reach here, no colon\n");
        loadInstruc(input, used, ca, opc, adr);
        return;
    }

    //there's label in the line
    memset(label, '\0', sizeof(label));
    strncpy(label, input, colon - input);
    labelCheck(label);

    // At this point we verified label syntax is correct and we can load it in
    // the linked list of labels, regardless of if it is used or if it is empty.
    loadLabel(label, *ca);
    strncpy(temp, input + strlen(label) + 1, len); // 1 for colon
    strncpy(input, temp, len);
    int new_len = strlen(input);
    
    if (!new_len)
    {
        if (((*used) >= SCRAM_SIZE) || ((*ca) >= SCRAM_SIZE))
        {
            printf("too many lines of input\n");
            exit(4);
        }
        // if empty string, go to next line
        //do not increment the address, different labels have same address is possible
        return;
    }

    //after label, there shouldn't be ORG directive:
    check_org(input);
    loadInstruc(input, used, ca, opc, adr); // all thats left is instruction
}

int datacheck(char *data)
{
    long val;
    char *ptr;
    val = strtol(data, &ptr, 0);

    if (ptr == data)
    {
        printf("%s\n", data);
        //check if there's error during conversion
        //if argument that should be number is not number, then error
        printf("Conversion error occurred\n");
        exit(6);
    }
    else if ((val > 255) || (val < -128))
    {
        fprintf(stderr, "data value out of range.\n");
        exit(6);
    }
    //the value can be converted to number
    //check if data it's not digit
    if (!check_digit(data))
    {
        //printf("val: %d, data : %s\n",val, data);
        printf("invalid number entered aa\n");
        exit(6);
    }
    //printf("reach here data:%d\n", val);
    return val;
}

int loadTempLabel(const char *label)
{
    if (find(label) != 1)
    { // if label doesn't exist
        append(label, -1);
        return 0; 
    }
    return 1;
}

int addCheck(const char *add)
{
    long val;
    char *ptr;
    val = strtol(add, &ptr, 10);

    if (ptr == add)
    {
        //add is label instead of a value
        // if after converting to string the pointer isnt \0
        labelCheck(add); // check if valid label
        if (loadTempLabel(add))
        {
            return getLabelAdd(add);
        }
        return -1;
    }
    else if ((val > 15) || (val < -8))
    {
        fprintf(stderr, "Error: Address out of range (max 15) encountered\n");
        exit(6);
    }
    //the value can be converted to number
    //check if data it's not digt
    if (!check_digit(add))
    {
        printf("invalid number entered\n");
        exit(6);
    }
    return val;
}

//given the line of instruction, load it into the opc and add array
void loadInstruc(const char *ins, int *used, int *ca, uint8_t *opc_array, char **adr_array)
{
    char opc[4];
    int len = strlen(ins);
    char *add = malloc((len)*sizeof(char));
    if (add == NULL)
    {
        printf("malloc error when creating address.\n");
        exit(9);
    }
    //printf("%s\n", ins);
    if (len < 3)
    {
        //invalid instruction
        //printf("len: %d\n",len);
        printf("An invalid op-code was encountered\n");
        exit(5);
    }

    //after triming, the first three alphabet should be the opcode
    for (int i = 0; i < 3; i++)
    {
        *(opc + i) = *(ins + i);
    }
    opc[3] = '\0';
    long val;
    int num = opc_check(opc);
    if (num == -1)
    {
        printf("opcode not found.\n");
        exit(5);
    }
    //printf("%s\n", opc);

    //the opcode does not require address
    if ((num == 0) || ((num > 15) && (num < 32)))
    {
        //check if there's any argument, if yes, then error
        if (len != 3)
        {
            printf("invalid opcode, shouldn't have argument\n");
            exit(5);
        }
    }
    else
    {
        //the address is require for the operation
        strncpy(add, ins + 3, len); //copy the address string into add
        //printf("%s\n", add);
        if (num == 32)
        {
            //the instruction is DAT
            val = datacheck(add);
            //printf("dat instruction has value: %d string is: %s\n", val, add);
        }
        else if (num == 33)
        {

            //the instruction is ORG
            *ca = datacheck(add);
            return;
        }
        else
        {
            val = addCheck(add);
            //check special situation for the EXT 0
            if ((num == 1) && (val == 0))
            {
                printf("invalid opcode EXT 0.\n");
                exit(5);
            }
        }
    }

    //printf("current address is %d:\n", *ca);
    opc_array[*ca] = num;
    //printf("the number stored at location %d is: %d\n", *ca, num);
    //free(*(adr_array + (*ca)));
    *(adr_array + (*ca)) = add;
    //printf("address stored at location %d is %s\n",*ca, *(adr_array+ (*ca)));

    if (((*used) >= SCRAM_SIZE) || ((*ca) >= SCRAM_SIZE))
    {
        printf("too many lines of input\n");
        exit(4);
    }
    (*ca)++;
    (*used)++;
}

void construct(uint8_t *mem, int *ca, uint8_t *opc_array, char **add_array)
{

    //printf("construct address %d", *ca);
    long val = 0;     // intermediate value
    char *ptr = NULL; // intermediate pointer
    uint8_t add = 0;  // address
    //printf("address is %c\n", add_array[1]);
    for (int i = 0; i < (*ca); i++)
    {
        int len = strlen(add_array[i]);
        //no argument
        if (!len)
        {
            mem[i] = opc_encode_n(opc_array[i]);
        }
        else
        {
            //there's argument presented

            val = strtol(add_array[i], &ptr, 0);
            //printf("reach i:%d, add: %s\n", i, add_array[i]);
            if (ptr == add_array[i])
            { // if after converting the address is label

                //need to check if the instruction is EXT, then the upper four bits are preserved:
                add = getLabelAdd(add_array[i]);
                if (opc_array[i] == 1)
                {
                    add = (add >>4) &0x0f;
                    if (add == 0)
                    {
                        printf("EXT 0 where 0 is from a label.\n");
                        exit(5);
                    }
                }
                else
                {
                    add = add & 0x0f;
                }
                //printf("reah here add: %d\n", add);
            }

            else
            {
                add = val;
                //printf("add = val: %d",val);
            }

            if (opc_array[i] == 32)
            { // if opc is DAT
                mem[i] = add;
                //printf("address %d value is %d\n", i, add);
            }
            else
            { // if opc is not DAT
             
                int temp = opc_encode_y(opc_array[i]);
                mem[i] = (temp << 4);
                mem[i] = mem[i] + add;
                //printf("mem is %x\n",mem[i]);
            }
        }
    }
}
