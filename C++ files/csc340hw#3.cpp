/*
*	Author:Karl Bigley-Bodlak
*	problem: hw3, #3, binarysearch
*	purpose: compare speed of iterative and recursive functions 
*		     when computing binary search of an array.
*/


#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

//iterative binary search. desired is search value.
//returns position of found int in array.
int binsearchit(int a[],int leng,int desired)
{
	int mid =leng/2, first = 0, last = leng-1;
	while(desired!=a[mid])
	{
		if(a[mid]>desired)
		{
		//if number is not in array, the outside check will pick 
		//up on the length value and print ERROR.
			if(last<first) return leng;
			last = mid-1;
			mid = first +last;
			mid = mid/2;
		}
		else 
		{
			if(first>last) return leng;
			first = mid+1;
			mid = first+last;
			mid = mid/2;
		}
	}
	return mid;	
		
}

//recursive binary search
int binsearchrec1(int a[],int first, int last, int desired)
{
	int mid = (first+last)/2;
	if(first>last) //absence of desired value check.
	//test in main will pick up on bad value passed back.
		return 10;
	if(a[mid]==desired)
		return mid;
	else if(a[mid]<desired) 
		return binsearchrec1(a,mid+1,last,desired);
	else 
		return binsearchrec1(a,first,mid-1,desired);
}

//passes information off to recursive function.
int binsearchrec(int a[],int leng, int desired)
{
	int first = 0, last = leng-1, mid = leng/2;
	return binsearchrec1(a,first, last,desired);
}

//function for time measurements.
double sec(void){return double(clock( ))/CLOCKS_PER_SEC;}

int main(void)
{
	double t1, t2; //time markers for runtime
	int leng = 10;
	int a[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26}; //a[i] =i for i=0,1,...,n-1
	//check to make sure functions work.
	t1 = sec();//time begin iterative
	for(int k=0; k<10000000; k++)
	{
		for(int i=0;i<10;i++)
			if(a[i] != a[binsearchit(a,leng,i)]) cout << "ERROR\n";
	}
	t2 =sec();//time end iterative
	double diff = t2-t1;
	cout <<"time for iterative search: "<<diff<<" seconds\n";
	t1 = sec();//time begin recursive
	for(int l=0;l<10000000;l++)
	{
		for(int j=0; j<10; j++)
			if(a[j] != a[binsearchrec(a,leng,j)]) cout << "ERROR\n";
	}
	t2=sec(); //time end recursive
	diff = t2-t1; 
	cout <<"time for recursive search: "<<diff<<" seconds\n";
	return 0;
}
//end program.
