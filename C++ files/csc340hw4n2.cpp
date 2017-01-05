/*
*	Author:Karl Bigley-Bodlak
*	problem: determine the number of upper-case letters,
*	lower-case letters, and digits in a line put in
*	by the user.
*	Program: lineReader
*	purpose: practice input processing with 
*	lines of text.
*/

#include <iostream>
#include <cstring>
using namespace std;


int main(void)
{
	cout<<"please enter a line of text.\n";
	char mystring[80];
	int uppercount=0, lowercount=0, digitcount=0,i=0;
	while( i<79&&(mystring[i]=cin.get())!='\n')
	{
		if(mystring[i]>=97&&mystring[i]<=122) lowercount++;
		if(mystring[i]>=65&&mystring[i]<=90) uppercount++;
		if(mystring[i]>=48&&mystring[i]<=57) digitcount++;
		i++;
	}
	cout<< "number of uppercase letters: "<< uppercount<<endl
	<<"number of lowercase letters: "<<lowercount<<endl
	<<"number of digits: "<<digitcount<<endl;
	return 0;
}
