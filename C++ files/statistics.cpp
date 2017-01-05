/*
	Program Name:statistics.cpp
	Purpose: run statistics operations on a .dat file.
	Author: Karl Bigley-Bodlak
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<math.h>
using namespace std;
/*
	n is iterator
	mean is mean of data
	variance is variance, which is used to find stddev,
	the standard deviation.
	coeffvar is the coefficient of variation.
*/
int absolute(double n)
{
	if(n<0) n*=-1;
	return n;
}
int main(void)
{
	int n=0;
	double data[200], mean, variance, stddev, coeffvar;
	char FN[] = "random.dat";
	ifstream IS1(FN, ios::in);
	while (IS1>>data[n]) n++;
	for(n=0;n<200;n++)//mean calculation
	mean+=data[n];
	mean/=200;
	for(n=0;n<200;n++)//variance and stddev calculation
		variance+=pow(data[n]-mean,2);
	variance/=199;
	stddev=sqrt(variance);
	coeffvar = stddev/mean;//coeffvar calculation.
	cout<<"The mean of the data is: "<<mean<<"\n\n"
	<<"the standard deviation is: "<<stddev<<"\n\n"
	<<"the coefficient of variation is: "<<coeffvar
	<<"\n\n";
	
	return 0;
}

