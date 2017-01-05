/*
	CSC 600 HW3: Procedural programming
	Purpose: create efficient programs using procedural programming
	Date fue: 3/4/16
	Author: Karl
	Problem 2: linear approximation
*/

/*
	create a program that for any value x, x1< x <x3  
	computes the corresponding value y 
	assuming that the segment of curve can be approximated with the parabola y = ax^2 + bx +c
	*****use n = 40 equidistant points.
	(a) Insert points  3 points into the parabola equation, (X1,Y1) (X2,Y2) and (X3,Y3 ) ,(),,(),,( 3 32211 y xyxyx in parabola 2 () y x ax bx c ? ? ? . 
	You will get three linear equations; solve them and find a,b,c. 
	Then, display the table of function y(x) from x1 to x3. 
	(b) Solve the same problem using Lagrange interpolation formula. 
	(c) Compare your two solutions and show your conclusions
*/

#include<iostream>
#include<math.h>
using namespace std;
//solving linear equations to get a,b,c

double y(int x1, int y1, int x2, int y2, int x3, int y3, double x)
{
	/*substitue three points into the equation ax^2 +bx +c
	  you get three different coefficients for a b and c
	  
	*/
	
	double min = x1;
	double max = x3;
	int i;
	//the values we want to find: a, b, c
	int coeffAMaster;
	int coeffBMaster;
	int cMaster;
	int coeffa1 = pow(x1,2.0);
	int coeffa2 = pow(x2,2.0);
	int coeffa3 = pow(x3,2.0);
	
	double multby;
	//check that x1 < x < x3
	if(x1 > x || x>x3)
	{
		cout << "x1 < x < x3\n";
		return NULL;
	}	
	
	//(2) - (1) gets rid of c, leaving ax^2 + bx
	coeffa2 = coeffa2 - coeffa1;
	y2 = y2 - y1;
	x2 = x2 - x1;
	
	//(3) - (1) gets rid of c 
	coeffa3 = coeffa3 - coeffa1;
	y3 = y3 - y1;
	x3 = x3 - x1;
	
	//(2) - (3) to get one variable isolated.   coeffa2 + x2 = y2  with coeffa3 + x3 = y3
	//  find the number to multiply x2 by to cancel out with x3
	multby = (double)x3/(double)x2;
	
	//then we can assume this will cancel out the x's when we subtract (2) from (3), so multiply (2) by multby
	//Then we perform the subtraction.
	coeffa3 = coeffa3 - coeffa2*multby;
	y3 = y3 - y2*multby;

	// ax^2 = y     a = y3/coeffa3
	coeffAMaster = y3/coeffa3;
	//now plug a into (2) to find b: b = (y2 - coeffAMaster)/x2		ax2^2 + bx2 = y2
	coeffBMaster = (y2 - coeffAMaster*coeffa2)/x2;
	//then find c : cMaster = y1 - coeffMasterA*coeffa1 - coeffBMaster*x1
	cMaster = y1 - coeffAMaster*coeffa1 - coeffBMaster*x1;
	
	return(coeffAMaster*pow(x,2) + coeffBMaster*x + cMaster);	
}

//using Lagrange interpolation
double y1(int x1, int y1, int x2, int y2, int x3, int y3, double x){
	if(x1 > x || x>x3)
	{
		cout << "x1 < x < x3\n";
		return NULL;
	}
	return ( ( (x-x2)*(x-x3) )/ ( (x1-x2)*(x1-x3) ) )*y1 + (( (x-x1)*(x-x3) )/ ( (x2-x1)*(x2-x3) ) )*y2 + (( (x-x1)*(x-x2) )/ ( (x3-x2)*(x3-x1) ) )*y3;
}

int main(void){
	
	double n = 40.; //number of equidistant points to use.
	double min = -1.0; //the minimum x value being used.
	double max = 2; //the maximum x-value being used
	int i = 1;
	double step = (max - min)/n; //measuring the equidistant points.
	cout << "Linear Equations method.\n";
	//the solution to the equation using the points (-1,4),(1,-2), and (2,5) is: a = 2, b = 1, c = -5
	while(min < max)
	{
		cout << "x"<<i<<" = " << min << " | y = " << y(-1,-4,1,-2,2,5,min) << "\n"; 
		min = min+step;
		i++;
	}
	
	min = -1.0;
	i = 1;
	cout << "\nLagrange polynomial method.\n";
	while(min < max)
	{
		cout << "x"<<i<<" = " << min << " | y = " << y1(-1,-4,1,-2,2,5,min) << "\n"; 
		min = min+step;
		i++;
	}
}

