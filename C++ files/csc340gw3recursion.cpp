/*
*	Author:Karl Bigley-Bodlak
*	problem: hw3, #2, sumarray
*	purpose: compare speed of iterative and recursive functions 
*		     when computing sum of random doubles in an array.
*/


#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

/*make an array of random numbers from 0 to 1, then add them up
* iteratively and recursively, printing runtimes of each function.
* t1 and t2 are markers whose difference will tell the runtime of each function.
*/

//Iterative sumarray. a is array of doubles, length is length of array
double sumarrayit(double a[], int length)
{
	double sum;
	for(int i = 0;i<length; i++)
		sum+= a[i]; //
	return sum;
}

//recursive sumarray function
double sumarrayrec(double a[], int length)
{
	if(length<1) return 0;
	else return sumarrayrec(a,length-1) + a[length-1];
}

//time function used to get operators for comparison.
double sec(void) {return double (clock())/CLOCKS_PER_SEC;}

int main(void)
{
	double t1, t2; 	
	double a[10];
	srand( (unsigned) time(NULL)); //randomizing seed for rand()
	for(int i=0;i<10;i++) a[i]= double(rand())/RAND_MAX;
	t1 = sec();//clock t1 start
	for(int j=0; j<50000000;j++){	sumarrayit(a, 10) ;}//looping for measurable time.
	t2 = sec();//clock t2 end
	double diff = t2 -t1;
	cout <<endl<<"Time for iterative function: "<<diff<<" seconds" <<endl;
	t1 = sec();//clock t1 begin
	for(int j=0; j<50000000;j++){sumarrayrec(a,10);}
	t2 = sec();//clock t2 end
	diff = t2-t1;
	cout <<endl<< "Time for recursive function: "<<diff<< " seconds"<<endl;
	return 0;
}
//end program.
