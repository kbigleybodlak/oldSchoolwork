/*
*	Author:Karl Bigley-Bodlak
*	problem: hw7, #2 
*	program: dynamicstringappender
*	purpose: practice appending dynamic character arrays.
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <new>
using namespace std;


//takes references str and add and appends add to the end
// of str and returns a pointer to the appended string.
char *append(char *str, char *add)
{
	//create new array for combined space of c-strings.
	char *c = new char[strlen(str)+strlen(add)+1]; 
	//keep a pointer to the first element of the new array.
	char *b =c;
	while(*str!='\0')*c++=*str++; //copy first word.
	while(*add!='\0')*c++=*add++;//add second word.
	//pass back a reference to the start of the appended string.
	return b;
}
/*
	a,b,c,d, and e are sample dynamic c-strings.  b,c,d, and e
	will be appended to a.
*/
int main(void)
{
	char *a= new char[5];
	char *b = new char[7];
	char *c = new char[4];
	char *d = new char[3];
	char *e = new char[6];
	//assignment
	a="the ";
	b="donkey ";
	c="bit ";
	d="my ";
	e="hand. ";
	cout<< a<<b<<c<<d<<e<<endl; //display without appending.
	a=append(a,b);
	a=append(a,c);
	a=append(a,d);
	a=append(a,e);
	cout<<a<<endl;//display appended c-string
	delete [] a;	//freeing memory
	return 0;
}
//end program.
