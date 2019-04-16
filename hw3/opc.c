/*Weiting Tan
JHED: wtan12*/
#include "opc.h"

static char *opcodes[] = {"HLT", "EXT", "LDA", "LDI", "STA", "STI",
						  "ADD", "SUB", "JMP", "JMZ", "AND", "IOR",
						  "XOR", "ADL", "ADC", "SBB", "NEG", "COM",
						  "CLR", "SET", "RTL", "RTR", "LSL", "LSR",
						  "ASR", "TST", "CLC", "SEC", "TCA", "TVA",
						  "JAL", "NOP"};

void to_hexchar(int decimal, char *hex, int numBits)
{
	/*
	 * Note that hex is a single pointer and not a double because
	 * we only need to change the contents of hex; we do not need
	 * the original array of hex to point to another array.
	 */
	int maxNum = 1;
	for (int i = 0; i < numBits; i++)
	{
		maxNum *= 16;
	}
	//Ensures that hexadecimal wraps back to zero
	//once max is reached in decimal form.
	decimal = decimal % maxNum;

	int result;
	//Only four bits is allowed for the address.
	for (int i = numBits - 1; i >= 0; i--)
	{
		result = decimal / 16;
		int rem = decimal - result * 16;
		if (rem >= 10)
			////In ASCII, 65 is 'A', which is correct for when rem = 10.
			*(hex + i) = (55 + rem);
		else
			//In ASCII 48 is '0', which is correct when rem is 0.
			*(hex + i) = (rem + 48);
		decimal = result;
	}
	hex[numBits] = '\0';
}

void cat(char *out, char *opc, char *add)
{
	for (int i = 0; i < 3; i++)
	{
		*(out + i) = *(opc + i);
	}
	out[3] = ' ';
	out[4] = '0';
	out[5] = 'x';
	for (int i =0; i< (int) strlen(add); i++)
	{
		out[6+i] = *(add+i);
	}
}

void opc_decode(int opc, int add, char *output)
{
	char *opc_out;
	char add_out[2];

	//Operation starting from NEG has no address
	if (opc == 15)
	{
		//index from NEG
		int index = 16 + add;
		opc_out = opcodes[index];
		for (int i = 0; i < 3; i++)
		{
			*(output + i) = *(opc_out + i);
		}
		output[3] = '\0';
	}
	else
	{

		//special case of HLT
		if (opc == 0 && add == 0)
		{
			opc_out = opcodes[0];
			for (int i = 0; i < 3; i++)
			{
				*(output + i) = *(opc_out + i);
			}
			output[3] = '\0';
		}
		else
		{
			opc_out = opcodes[opc + 1];

			to_hexchar(add, add_out, 1);
			cat(output, opc_out, add_out);
		}
	}
}
void opc_decode_sim(int opc, int add, char *output)
{
	char *opc_out;
	char add_out[2];

	//Operation starting from NEG has no address
	if (opc == 15)
	{
		//index from NEG
		int index = 16 + add;
		opc_out = opcodes[index];
		for (int i = 0; i < 3; i++)
		{
			*(output + i) = *(opc_out + i);
		}
		output[3] = ' ';
		output[4] = ' ';
		output[5] = ' ';
		output[6] = ' ';
		output[7] = ' ';
	}
	else
	{

		//special case of HLT
		if (opc == 0 && add == 0)
		{
			opc_out = opcodes[0];
			for (int i = 0; i < 3; i++)
			{
				*(output + i) = *(opc_out + i);
			}
			output[3] = ' ';
			output[4] = ' ';
			output[5] = ' ';
			output[6] = ' ';
			output[7] = ' ';
		}
		else
		{

			opc_out = opcodes[opc + 1];
		
			to_hexchar(add, add_out, 2);
			cat(output, opcodes[opc + 1], add_out);
		}
	}
}

