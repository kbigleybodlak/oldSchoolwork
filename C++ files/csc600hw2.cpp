/*
	Project name: csc600hw2 Basic data types
	Purpose: to test various data types' limitations in C++ arithmetic operations
	Author: Karl Bigley-Bodlak
*/


#include <iostream>
#include <cmath>
#include <limits>
#include <string>
using namespace std;
int main(void){
	//1. Show that for unsigned int a,b and a>0, b>0, we can get a+b < a 
	unsigned int a1 = 900000000000;
	unsigned int b1 = 900000000000;
	cout << "unsigned int overflow: " << (a1+b1) << "\n\n";
	
	//2. Show that for int a,b and a>0, b>0, we can get a+b < 0 
	int a2 = 90000000000;
	int b2 = 90000000000;
	cout << "signed int overflow: " << (a2+b2) << "\n\n";
	
	//3. Show that for int a,b and a<0, b<0, we can get a+b > 0 
	int a3 = -90000000000;
	int b3 = -90000000000;
	cout << "signed int underflow : " << (a3+b3) << "\n\n";
	
	//4. Show that for double x and x>0 we can get 1. + x  = =  1. 
	double x = 0.000000001;
	cout <<"x = " << x << "\n1. + x>0 = " << (1. +x) << "\n\n";
	
	//5. Show that for double a,b,c in some cases (a+b)+c  !=  (c+b)+a 
	//*note: this is a smart compiler and 
	double a = 0.000004;
	double b = 0.000004;
	double c = 1.0;
	double aplusb = a+b;
	double cplusb = c+b;
	
	cout <<"a + b: " << aplusb << "\n";
	cout <<"c + b: " << cplusb << "\n";
	cout << "( a + b ) + c = " << (aplusb)+c << "\n";
	cout <<"( c + b ) + a = " << (cplusb)+a << "\n\n";
	
	//6. Show the results of the following power function: pow(-2., 3),  pow(-2., 3.0) , pow(-2., 3.00000000001) 
	cout << "power funtions testing \n";
	cout << pow (-2.,3) << "\n";
	cout << pow (-2. , 3.0) << "\n";
	cout << pow(-2., 3.00000000001) << "\n\n";
	
	//7. Show the memory size of the following constants 1. , 1.F, 1 , '1' ,  and "1" 
	cout << "memory sizes\n";
	string one = "1";
	cout << "size of 1. = " << sizeof(double) << " bytes\n";
	cout << "size of 1.F = " << sizeof(float) << " bytes\n";
	cout << "size of 1 = " << sizeof(int) << " bytes\n";
	cout << "size of \'1\' = " << sizeof(char) << " bytes\n";
	cout << "size of \"1\" = " << sizeof(one) << " bytes\n";
	cout << "the maximum value of a float is "<< (float)pow(2,127) << "\n";
	cout << "the maximum value of a double is "<< pow(2,pow(2,9))<< "\n\n";
	cout << sizeof(long double) << "\n" << sizeof(long)<< "\n";
	
	//8. Display 1./3. using 20 digits and show the correct and incorrect digits 
	cout << "1./3. using 20 digit precision.\n";
	cout.precision(20);
	cout << 1./3. << "\n\n";
	
	/*9. Display all printable characters of the ASCII table in 3 columns:                  
	first column: 32-63, second column: 64-95, third column: 96-127. 
	Each column must include the numeric value and the corresponding character. 
	Following is an example of one of 32 rows in the ASCII table: 
	33  !       65  A       97  a 
	*/
	unsigned int col1 = 32;
	unsigned int col2 = 65;
	unsigned int col3 = 97;
	cout << "printable ASCII characters \n";
	while(col3 < 128){
		cout << col1 << "\t" << (char)col1 << "\t\t" 
			 << col2 << "\t" << (char)col2 << "\t\t"
			 << col3 << "\t" << (char)col3 << "\t\t\n";
		col1++;
		col2++;
		col3++;
	}
	cout <<"\n";
	
	//10. Compute sqrt(2.) using your own program for square root function. 
	//this uses the convergence method starting with a starting x0 of 1.2, refines it 5 times.
	double x0 = 1.2;
	int i = 0;
	while (i<5){
		x0 = 0.5 * (x0 + 2./x0); 
		i++;
	}
	cout <<"the square root of 2. is : "<< x0 << "\n";
	
	
	
	return 0;
}
