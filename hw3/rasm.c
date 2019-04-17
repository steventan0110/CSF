/*
Weiting Tan
JHED:wtan12
*/
#include "rasm.h"
#define LINE_SIZE 128
#define LABEL_SIZE 32

/*
 * This helper function trims leading and trailing white space as well as comment
 * of the input string and return a new pointer to the trimmed substring.
 */
char *trim(char *str)
{
    char *out = "";
    int len = strlen(str);
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (*(str + i) == ' ' || *(str + i) == '\t')
        {
            //do nothing, let i increment
        }
        else if (*(str + i) == ';')
        {
            count++;
            //reach comment, break the loop
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
    return out;
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
        if ((!isalpha(str[i])) || (!isdigit(str[i])) || (str[i] != '_'))
        {
            fprintf(stderr, "Error: illegal label encountered.\n");
            exit(7);
        }
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
            fprintf(stderr, "Error: Label \"%s\" already defined.", label);
            exit(6);
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
void parseFile(FILE *fin, uint8_t *cl, uint8_t *ca, uint8_t **opc, uint8_t **adr)
{
    char line[LINE_SIZE] = ""; // buffer for current line being parsed.
    char temp[LINE_SIZE] = "";
    char *colon;                 // position of the colon.
    char label[LABEL_SIZE] = ""; // string name of label
    *cl = 0;                     //initialize curretn line
    *ca = 0;                     //initialize current address
    while (!feof(fin))
    {
        *cl++;
        memset(line, '\0', sizeof(line));
        fgets(line, LINE_SIZE, fin);
        strncpy(temp, trim(line), LINE_SIZE);
        strncpy(line, temp, LINE_SIZE);
        if (!*line)
        { // if empty string, go to next line
            continue;
        }
        colon = strchr(line, ':');
        if (!colon)
        { // if only instruction
            loadInstruc(line, ca, opc, adr);
            continue;
        }
        //there's label in the line
        memset(label, '\0', sizeof(label));
        strncpy(label, line, colon - line);
        labelCheck(label);
        // At this point we verified label syntax is correct and we can load it in
        // the linked list of labels, regardless of if it is used or if it is empty.
        loadLabel(label, *ca);
        strncpy(temp, line + strlen(label) + 1, LINE_SIZE); // 1 for colon
        strncpy(line, temp, LINE_SIZE);
        strncpy(temp, trim(line), LINE_SIZE);
        strncpy(line, temp, LINE_SIZE);
        if (!*line)
        { // if empty string, go to next line
            continue;
        }
        loadInstruc(line, ca, opc, adr); // all thats left is instruction
    }
}

int datacheck(char *data)
{
    long val;
    char *ptr;
    val = strtol(data, &ptr, 0);
    if (*ptr)
    { // if after converting to string the pointer isnt \0
        fprintf(stderr, "Error: invalid data value \n");
        exit(6);
    }
    else if (val > 256)
    {
        fprintf(stderr, "data value too large.\n");
        exit(6);
    }
    return val;
}

void loadTempLabel(const char *label)
{
    if (find(label) != 1)
    { // if label doesn't exist
        append(label, -1);
    }
}

int addCheck(const char *add)
{
    long val;
    char *ptr;
    val = strtol(add, &ptr, 10);
    if (*ptr)
    {                    // if after converting to string the pointer isnt \0
        labelCheck(add); // check if valid label
        loadTempLabel(add);
        return -1;
    }
    else if (val > 15)
    {
        fprintf(stderr, "Error: Address out of range (max 15) encountered\n");
        exit(6);
    }
    return val;
}

//given the line of instruction, load it into the opc and add array
void loadInstruc(const char *ins, uint8_t *ca, uint8_t **opc_array, uint8_t **adr_array)
{
    char opc[4];
    char add[LABEL_SIZE] = "";
    char temp[LABEL_SIZE] = "";

    int len = strlen(ins);
    if (len < 3)
    {
        //invalid instruction
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
    //the opcode does not require address
    if ((num == 0) || ((num > 15) && (num < 32)))
    {
        if (len != 3)
        {
            printf("invalid opcode");
            exit(5);
        }
    }
    else
    {
        strncpy(add, ins + 3, LINE_SIZE); //copy the address string into add
        if (num == 32)
        {
            val = datacheck(add);
        }
        else
        {
            val = addCheck(add);
        }
    }

    *ca++;
}