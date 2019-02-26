#include <unistd.h>
#include <stdio.h>

void insert(char *out, char *in, int pos, int len)
{
    for (int i = 0; i < len; i++)
    {
        *(out+pos+i) = *(in+i);
    }
}
int main()
{
   
    char output[] = "000000000                           ";
    
    char in[3] = "abc";
    insert(output, in, 6, 3);
    write(STDOUT_FILENO, output, 31);
}