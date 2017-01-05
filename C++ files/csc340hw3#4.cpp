/*
*	Author:Karl Bigley-Bodlak
*	problem: hw3, #4, recursive asterisks
*	purpose: use recursion to print asterisks and
* 	make a histogram from this function.
*/


#include <iostream>
#include <cstdlib>
using namespace std;

void line(int n)
{
	//base case is n=0;
	if(n>0)
	{
		cout <<"*";
		line(n-1);
	}	
}

//histogram function, leng is length of array.
void hist(int h[],int leng)
{
	for(int i=0;i<leng;i++)
	{
		cout<< h[i]<< " ";
	    line(h[i]); 
		cout<<endl;
	}
}

int main(void)
{
	//sample values for hist function.
	int h[]={2,4,6,7,2};
	hist(h,5);
	return 0;
}
