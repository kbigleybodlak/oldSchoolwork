/********************************************\
| Program: #5 hw 2 (triangles)               |                   
| Problem: create a function triangle(n) that|
|	     prints out a sequence of triangles|
| Purpose: practice use of control structures|
|          to manipulate character images.   |
| Author: Karl Bigley-Bodlak                 |
|                                            |                          
\********************************************/
//begin program.

#include <iostream>
#include <math.h>
using namespace std;

/* I used a numbering system for each row and column to map out where the spaces and asterisks would be placed by adding or subtracting row and col.  I switched to the lower half of the triangle with a conditional, this pattern does not work perfectly with even lengths.
*/
void triangle(int n)
{
	int col, row;
	for(row = 0 ;row<n ;row++)
	{
		for(col=0;col<=(n/2)+1;col++)
		{
			//midpoint switch
			if(row>(n/2))
			{
				if(row - col <n/2)
					cout <<"*";
				else
					cout << " ";
			} else if(row + col <=n/2)
						cout << " "; 
				   else 
						cout << "*";
			}
			cout << endl;
		}
	}

int main(void){
	int n;
	cout << "How many triangles do you want to print?" << endl;
	cin >> n;
	


	//exception handling
	while(n<=0)
	{
		cout << "please enter a number greater than zero." << endl;
		cin>>n;
	}
	for(n;n;n--)
	{
		triangle(n);
		cout << endl;
	}
	return 0;
}
//end program.

