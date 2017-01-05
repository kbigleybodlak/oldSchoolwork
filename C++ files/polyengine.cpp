/*
*	Author:Karl Bigley-Bodlak
*	problem: hw7, #3
*	program: polyengine
*	purpose: practice using master/engine model to pass command
*	line arguments
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;
/*
	a, b, and c are the arguements in the quadratic eq.
	ax^2+bx+c of which the roots r1 and r2 will be found.
	check is the value of the number in the radical of
	the quadratic equation. r is the value to the left
	of the +/- sign in the quadratic eq. and t is the value
	of the right side of the +/- sign.
	quadratic formula is (-b +/- sqrt(b*b-4*a*c))/2a
*/
int main(int argcnt,char *argvec[])
{
	double a,b,c,check,r,t,r1,r2;
	int icheck=0;
	if(argcnt<4) //interactive work
	{
		cout<<"Please enter three decimal numbers, a, b, and c, \nfor the "
			<<"quadratic equation form ax^2+bx+c.\n";
			cin>>a>>b>>c;
		check=b*b-4*a*c;
		/*
		If the square root will have a negative number 
		inside, it triggers a flag and then negates it
		so it can be used in the sqrt() function.
		*/
		if(check<0) 
		{
			check=-1*check;
			icheck=1;
		}
		//calculating both sides of the +/- seperately
		r=b/(2*a);
		t=(sqrt(check))/(2*a);
		//if i was flagged, puts i in front of second term
		//to denote it is an imaginary number
		if(icheck)
		{
			cout<<"x1: "<<r<<" + "<<"i("<<t<<")  x2: "<<r
				<<" - "<<"i("<<t<<")"<<endl;
		}
		else //calculation is normal
		{
			r1=r+t;
			r2=r-t;
			cout<<"x1: "<<r1<<"  x2: "<<r2<<endl;
		}
			return 0;
	}
	
	if(argcnt<5)// uses given values to display x1 and x2
	{
		a=atof(argvec[1]);
		b=atof(argvec[2]);
		c=atof(argvec[3]);
		check=b*b-4*a*c;
		if(check<0) 
		{
			check=-1*check;
			icheck=1;
		}
		//We assume that x1 = r1 + i*t1 and x2 = r2 + i*t2,
		// i=sqrt(-1).
		r=b/(2*a);
		t=(sqrt(check))/(2*a);
		if(icheck)
		{
			cout<<"x1: "<<r<<" + "<<"i("<<t<<")  x2: "<<r
				<<" - "<<"i("<<t<<")"<<endl;
		}
		else
		{
			r1=r+t;
			r2=r-t;
			cout<<"x1: "<<r1<<"  x2: "<<r2<<endl;
		}
		return 0;
	}
	
	// uses command line args to put x1 and x2 in a file.
	else	 
	{
		a=atof(argvec[1]);
		b=atof(argvec[2]);
		c=atof(argvec[3]);
		char* FN = argvec[4]; //filename FN
		check=b*b-4*a*c;
		if(check<0) 
		{
			check=-1*check;
			icheck=1;
		}
		r=b/(2*a);
		t=(sqrt(check))/(2*a);
		ofstream OS(FN, ios::app); //open file
		if(icheck)
		{
			OS<<"x1: "<<r<<" + "<<"i("<<t<<")  x2: "<<r
				<<" - "<<"i("<<t<<")"<<endl;
		}
		else
		{
			r1=r+t;
			r2=r-t;
			OS<<"x1: "<<r1<<"  x2: "<<r2<<endl;
		}
		OS.close();//close file
		return 0;
	}
}
//end program
