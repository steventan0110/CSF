#include <unistd.h>

/* Format of output line:
aaaa  hh hh hh hh hh hh hh hh  cccccccc\n
*/

/* You may want to use this */
char hex2asc[17] = "0123456789ABCDEF";

void parse_buffer(unsigned char *buffer, int len)
{
  //change the value that's unprintable into period
  for (int i = 0; i < len; i++)
  {
    if (((int)buffer[i] < 32) || ((int)buffer[i] > 126))
    {
      buffer[i] = '.';
    }
  }
}

// void to_hexchar(int input, unsigned char *out, int num)
// {
//   int i = 0;
//   while (input > 0)
//   {
//     int a = input % 16;
//     if (a > 9)
//     {
//       out[num - 1 - i] = 'A' + (a - 10);
//     }
//     else
//     {
//       out[num - 1 - i] = '0' + a;
//     }
//     input = input / 16;
//     i++;
//   }
// }
void to_hexchar(int decimal, char * hex, int numBits) {
	/*
	 * Note that hex is a single pointer and not a double because
	 * we only need to change the contents of hex; we do not need
	 * the original array of hex to point to another array.
	 */
	int maxNum = 1;
	for(int i = 0; i < numBits; i ++) {
		maxNum *= 16;
	}
	//Ensures that hexadecimal wraps back to zero
	//once max is reached in decimal form.
	decimal = decimal%maxNum;

	int result;
	//Only four bits is allowed for the address.
	for(int i = numBits - 1; i >= 0; i--) {
		result = decimal/16;
		int rem = decimal - result*16;
		if (rem >= 10)
			////In ASCII, 65 is 'A', which is correct for when rem = 10.
			*(hex+i) = (55 + rem);
		else
			//In ASCII 48 is '0', which is correct when rem is 0.
			*(hex+i) = (rem + 48);
		decimal = result;
	}
}

void insert(char *out, char * in, int pos, int len)
{
  for (int i = 0; i < len; i++)
  {
    out[i + pos] = in[i];
  }
}

int main()
{
  int address = 0;
  char add[4] = "0000";

  unsigned char buffer[8];
  char data[2] = "00";

  //create the output besides the buffer
  char output[] = "0000                           ";

  //read in 8 digitis line by line
  int a = read(0, buffer, 8);
  if (a < 0)
  {
    write(STDOUT_FILENO, "Error Input", 11);
    return 1;
  }

  while (a > 0)
  {
    char final_output[32 + a];
    //update the address bits
    to_hexchar(address, add, 4);
    insert(output, add, 0, 4);

    //parse the buffer to get the corresponding data
    for (int i = 0; i < a; i++)
    {
      to_hexchar((int)buffer[i], data, 2);
      // write(STDOUT_FILENO, data,2);
      // write(STDOUT_FILENO,"\n",1);
      //update the data bits
      insert(output, data, 6 + i * 3, 2);
    }
    //clean the data representation for next loop's use
    for (int i = 0; i < 2; i++)
    {
      data[i] = '0';
    }

    if (a != 8)
    {
      for (int i = 6 + 3 * a; i < 31; i++)
      {
        output[i] = ' ';
      }
    }

    //change the unprintable value into dot
    parse_buffer(buffer, a);

    //print out the value in corresponding format
    insert(final_output, output, 0, 31);
    insert(final_output, (char*)buffer, 31, a);

    write(STDOUT_FILENO, final_output, 31 + a);

    write(STDOUT_FILENO, "\n", 1);
    // after printing out, increment the addres by 8
    if (address >= 0xFFF8)
    {
      address = 0;
    }
    else
    {
      address = address + 8;
    }
    //readin another 8 digits and repeat the process
    a = read(STDIN_FILENO, buffer, 8);
    if (a < 0)
    {
      write(STDOUT_FILENO, "Error Input", 11);
      return 1;
    }
  }
}
