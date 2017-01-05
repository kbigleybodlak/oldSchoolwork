/*
*	Author:Karl Bigley-Bodlak
*	problem: hw 8, #2
*	program: mycrypto
*	purpose: practice using simple encryption/decryption of 
*	files
*/

#include <iostream>
#include <time.h>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <math.h>
#include <cstdlib>
using namespace std;

/*
	Exclusive or function.
	compares left-most bits and then shifts left, adding 1 to
	the return value, c, if the bits are the same.
	Returns a char based on the 8 bits that make up c.
*/
unsigned char eor(unsigned char a,unsigned char b)
{
	unsigned char c = 0;
	for(int i=0;i<8;i++)//8 bits for a char,
	{
		c*=2;
		//compares left-most value of a and b.
		if((a>127) != (b>127)) c++;
		a *= 2;
		b *= 2;
	}

	return c;
}

unsigned int randombyte()
{
	unsigned int a=0;
	for (int i=1; i<8;i++)
	{
		a+=(rand() % 2);
		a*=2;
	}
	return a;
}

/*
	Gets a key from the user, creates random numbers from that, 
	and then encrypts a given input file by using the exclusive 
	or function to compare each char to a randomly generated int
	based on the seed of the key.  The result of eor for the 
	taken char and the random number are put into the output
	file as an unsigned char, which gets converted to a char.
	IFN is input file name, OFN is output file name, a is the 
	numerical key given by the user.  b is the char taken from
	the input file.  c is a random number to compare to a in the
	eor function.
*/
int main(void)
{

	char IFN[20], OFN[20];
	unsigned int a;
	unsigned char b, check;
	cout<<"Please enter a key (unsigned int) "
		<<"for the encryption or decryption of "
		<<" the file, then the input file, then "
		<<"the output file.\n\n";
	cin>>a>>IFN>>OFN; //secret key given here
	srand(a); 			//key used for random seed
	unsigned char c=randombyte();
	ifstream IS(IFN, ios::in);
	ofstream OS(OFN, ios::out);
	b=IS.get();
	
	while(!IS.eof())
	{
		//check result of exclusive or so it does not put an eof 
		//marker before true eof.
		check =(eor(c,b));
		if(check=='\0') check+=45;
		OS.put(check);
		c=randombyte();
		b=IS.get();
	}
	cout<<"File encrypted/decrypted.\n";
	return 0;
}



