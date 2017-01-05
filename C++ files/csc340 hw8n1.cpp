/*
*	Author:Karl Bigley-Bodlak
*	problem: hw 8, #1 
*	program: MonteCarlo
*	purpose: practice comparing the accuracy of the Monte Carlo
*	method of integration versus the trapezoid method.
*/

#include <iostream>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <cstdlib>
using namespace std;

double urn(void)
{
       return double(rand())/RAND_MAX;
}

/*	
	integal of e^x from 0 to 1 is e-1.
	2.71828 is value of e.
	finding integral of e^x from 0 to 1.
	i is an iterator
	n is the number of random data points used for the integral.
	N is the number of points below the equation line.
	integral is the result of the integral
	error is the % difference between the monte Carlo result
	and the known value.
	emc is the value of e as computed using the result of the
	integral.
*/
int main(void)
{
	int i, n = 1000000, N=0;
	double x, y, integral, analytic = exp(1)-1, error;
    for(i=0; i<n; i++)
    {  
       x=0.+1.*urn(); y=2.71828*urn(); 
       if(y <= pow(2.71828,x)) N++;      
    }
    integral = 1.*exp(1)*double(N)/double(n);
    error = 100.*(integral - analytic)/analytic;
    double emc = integral +1;
    cout << "\nIntegral of e^x from 0 to 1\n\n"
         << "Analytic result    = " << analytic
         << "\nMonte Carlo result = " << integral
         << "\nRelative error [%] = " << error
         << "\nValue of e from calculation = "<<emc<<"\n\n";

/*
	now use the trapezoid method
	x0 is the left point of each trapezoid
	x1 is the right side of each trapezoid
	h is interval length
	using method h(x0/2 +x1+x2+...+xn-1+xn/2)
*/
	n=1000;  y=1;
	double  h=0.001, A=0, x1, x0=0;
	//1000 trapezoid estimation between 0 and 1.
	A+=  (exp(0.) +exp(1.) )/2.;
	for(i=1; i<n; i++)
	{
		x1= x0 + i*h;
		A += exp(x1); //right side of trapezoid height
	}
	A *= h;
	error = 100.*(A-analytic)/analytic;
	cout<< "the value of the integral using the trapezoid method "
		<<" is: "<<A<<"\nThe relative error[%] from the trapezoid"
		<<" method is: "<<error<<"\nThe accuracy of the trapezoid"
		<<" method is better than the Monte Carlo method.\n";
	return 0;
}
