/*
*	Author:Karl Bigley-Bodlak
*	problem: hw6, #2, triangleclass
*	purpose: Practice using classes and creating 
*	function sets for these classes.
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include<cstring>
#include <math.h>
using namespace std;

/*Create the input file triangle.dat using an editor and insert values needed for testing of
all functions. Write a main program that demonstrates the work with this class.
Declare all objects and variables. Display only equilateral triangles from the input file.*/

/*
	instantiated with an array of 100 triangles, T.
*/
class triangle
{
	//three sides of triangle.
	private:
		int a,b,c;
	public:
	triangle(){triangle(0,0,0);}
		//basic constructor, three sides given d, e, and f.
	triangle(int d, int e, int f)
	{
		a=d;
		b=e;
		c=f;
	}
	//uses strlen() and pow to determine size of number 
	//and converts it.
	int stringtoint(string number)
	{
		int length=0,value=0,j=0;
		while(number[length++]);
		while(length)
		{
			value+=(pow(10,length)*((int)number[j]-48));
			j++;
			length--;
		}
		return value;
	}
	/*
	takes three values from a file and set them as the sides
	of the triangle.  FN is filename. 
	terminates at eof.
	*/
	int readfile(ifstream & IS)
	{
		string d,e,f;
		IS>>a>>b>>c;
		return !IS.eof();
	}	
	
	//calculates area and returns it.
	//if not a triangle, returns -1.
	double area()
	{
		double area;
		//pythagorean check. negative distances don't count.
		if(a+b<c||a+c<b||b+c<a ||a<0||b<0||c<0)
			return -1;
		double s=(a+b+c)/2.;
		area=sqrt(s*(s-a)*(s-b)*(s-c));
		return area;
	}
	
	//returns perimeter
	int perimeter()
	{
		return a+b+c;
	}
	
	//displays sides, area, and perimeter of triangle.
	void show()
	{
		cout<<"side a: "<<a<<" side b: "<<b<<" side c: "<<c
			<<endl<<"area of triangle: "<<area()<<endl
			<<"Perimeter of triangle: "<<perimeter()<<endl;
	}
	
	//returns 1 if triangle is equilateral, 0 if not.
	//in this case, a 0 0 0 (default) triangle is not equilateral.
	int isequilateral()
	{
		if(a+b+c!=(3*a) || a<=0||b<=0||c<=0) return 0;
		else return 1;
	}
		
};

int main(void)
{
	triangle a[100];
	char* FN="triangle.dat";
	ifstream IS(FN, ios::in);
	
	int j,i=0;
	while(a[i].readfile(IS)) i++;
	IS.close();
	for(j=0;j<i;j++)
	{
		if(a[j].isequilateral())
			a[j].show();
	}
	return 0;
}
