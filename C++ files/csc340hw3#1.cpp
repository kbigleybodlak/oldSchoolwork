/*
*	Author:Karl Bigley-Bodlak
*	problem: hw3, #1 
*	purpose: using iterative and recursive functions
*	to determine the number of times a number occurs in 
*	an array of ints.
*/

#include <iostream>
using namespace std;

//iterative occurs function. 'desired' is number to test occurences for
//length is length of array a.
int occursit(int a[],int desired, int length)
{
	int count=0;
	for(int i = 0; i<length; i++)
		if(a[i]==desired) count++;
	
	return count;
}

//recursive occurs function. 
int occursrec(int a[], int desired, int length)
{
	if(length<1) return 0;
	if( a[length-1] ==desired)
		return 1 + occursrec(a,desired,length-1);
	else
		return 0 +occursrec(a,desired,length-1);
}

int main(void)
{
	int a[] = {0,1,3,3,2,1,0}; //test array.
	cout << "The number 3 occurs: "<<occursit(a,3,7)<<" times."<< endl;
	cout << "The number 2 occurs: "<<occursrec(a,2,7)<<" times."<< endl;
	return 0;
	
}
//end program.
