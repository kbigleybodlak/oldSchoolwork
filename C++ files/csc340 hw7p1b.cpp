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

//c=a x b.  n is size of nxn matrices being multiplied.
void matrixmult(double a[], double b[], double c[], int n)
{
	for(int i=0;i<n;i++)
		for(int j =0; j<n;j++)
			for(int k=0;k<n;k++)
				*(c+(i*n)+j)+= *(a+(i*n)+k) * *(b+(k*n)+j);
}
//*(c+i*n+j)+= *(a+i*n+k) * *(b+k*n+j);


void init(double *a, int n)   // Initialize nxn matrix 
{    int i,r,c;                // Pointer indexing
     for(i=0; i<n*n; i++)      
     {  r = i/n;               
        c = i%n;               
        *(a+r*n+c) = (r+1)+c+1;
     }
}

void show(double *a, int n)    // Show nxn matrix
{    cout<<endl;                
     for(int r=0; r<n; r++, cout<<endl)
       for(int c=0; c<n; c++)
       {  cout << setw(5) << *(a+n*r+c); 
          // cout << setw(5) << a[n*r+c];
       }
}

//j is the size of 3 nxn arrays that dynamic pointers a, b, and
//c point to, respectively.
int main(void)
{
	int j=4;
	double *a= new double[j*j];
	double *b=new double[j*j];
	double *c=new double[j*j];
	init(a,4);
	init(b,4);
	show(a,4);
	show(b,4);
	matrixmult(a,b,c,4);
	show(c,4);
	delete [] a, b, c;
	*a=NULL;
	*b=NULL;
	*c=NULL;
	return 0;
	
}
//end program.
