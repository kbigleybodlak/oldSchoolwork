/*
*	Author:Karl Bigley-Bodlak
*	problem: multiply matrices together, once using a static
*	matrix with indices and the other using a dynamic matrix
*	with pointers.
*	Program: MatrixMultiplier
*	purpose: practice using static and dynamic matrices.
*/

#include <iostream>
#include <iomanip>
using namespace std;

const int N = 20;

//two matrices a and b are multiplied and put into c.
//n is the size of the nxn matrices.
void matrixmult( double a[][N],  double b[][N], double c[][N], int n )
{
	int i, j, k;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			for(c[i][j]=k=0; k<n; k++)
				c[i][j] += a[i][k]*b[k][j];

}
	
//n is the size of the nxn matrix
void show(double a[][N], int n) // Show matrix [][] 
{    cout<<endl;                // Regular indexing
     for(int r=0; r<n; r++, cout<<endl)
       for(int c=0; c<n; c++)
         cout << setw(5) << a[r][c];
}


//initialize a matrix of size n x n with values from 0 
//to n*n-1
void init( double a[][N], int n) 
{                               
     for(int i=0; i<n*n; i++) a[i/n][i%n]=i;
} 

//a and b are the matrices being multiplied, c is the 
//destination for the product.
int main(void)
{
	static double a[N][N], b[N][N], c[N][N];
	init(a, 4);
	init(b, 4);
	show(a,4);
	show(b,4);
	matrixmult(a,b,c,4);
	show(c,4);

	return 0;
}
