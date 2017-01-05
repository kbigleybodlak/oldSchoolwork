/*
	Program Name:Makefile.cpp
	Problem: make a data set in a file, then manipulate it
	using other programs via the system command.
	Purpose: practice executing other programs from a 
	single program using the system command
	Author: Karl Bigley-Bodlak
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<time.h>
using namespace std;

int main(void)
{
	int n=200, num, i;
	srand( (unsigned) time( NULL ) );
	char FN[]= "random.dat";
	ofstream OS1(FN,ios::out);
	while(n--)
	{
	num=0;
	for(i=0;i<12;i++)
	num +=(rand()%9);
	OS1<<num<<"  ";
	}
	OS1.close();
	system("statistics");
	system("distribution");
	return 0;
}
