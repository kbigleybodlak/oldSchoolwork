/*
	CSC 600 HW3: Procedural programming
	program:arrayReduce
	Purpose: Write a function that removes all instances of 
	the three largest integers in an unsorted array.
	Author: Karl
	Problem 3: array reduction
*/
#include<iostream>
#include<new>
using namespace std;

/*
iterative solution:
iterate through array to get largest values.
make a new array , copy over values, 
EXCEPT the ones that are the largest.
and assign a to the new array.
note: need dynamic array to make the new array, 
don't know how many values to copy over.
*/

/*
	TEST CASES:
	all values in array are same number
	less than 3 values in array.
	
*/
int reduce(int a[], int n){
	int newLength = 0;
	int *reducedArray = NULL; // will make the new array that will be assigned to a upon completion. 
	int newN = 0; // the length of the reduced array.
	
	int i = 1;
	int j = 0;
	int x; //largest integer in array.
	int xCount =1; //counts the occurrences, used to determine size of reduced array.
	int y; //second largest
	int yCount = 0;
	int z; // third largest
	int zCount = 0;
	//check to see if the array is large enough to process.
	if(a == NULL){
		cout << "array is null.\n";
		return n;
	}
	//before the while loop, process first three elements for the largest among them.
	x = a[0];
	/*if(a[1] > x && x != a[1])
	{
		y = x;
		x = a[1];
	} 
	else
	{
		y = a[1];
	}
	
	if (a[2] > x  )
	{
		z = y;
		y = x;
		x = a[2];
	}
	else if(a[2] > y && x != a[1]) 
	{
		z = y;
		y = a[2];	
	}*/
	//now x is the current largest, y the second, and z the third.
	//process the array to get the three largest integers.
	while(i<n){
	
	if (a[i] > x ) //case of new biggest number.
	{
		z = y;
		zCount = yCount;
		y = x;
		yCount = xCount;
		x = a[i];
		xCount = 0;
		
	}
	else if(a[i] > y && x != a[i]) //case of new second highest value.
	{
		z = y;
		zCount = yCount;
		y = a[i];
		yCount = 0;	
	} 
	else if(a[i] > z && x != a[i] && y != a[i])
	{
		z = a[i];
		zCount = 0;
	}
	
	if(a[i] == x)
		xCount++;
	if(a[i] == y)
		yCount++;
	if(a[i] == z)
		zCount++;
		
		i++;
	}
	cout << "the three largest integers are: "<<x<<" "<<y<<" "<<z<<"\n";
	cout << "they appear: "<<xCount<<" "<<yCount<<" "<<zCount<<"\n";

	newN = n - xCount - yCount - zCount;
	
	//reducedArray = new int[newN];
	//reducedArray[0] = 43;
	//Reduction of array to remove the largest integers.
	//copy over values to a new array, skipping over the largest values.
	i=0;
	while(i<n)
	{
		if(a[i] != x && a[i] != y && a[i]!=z){
			a[j] = a[i];
			j++;
		}
			
		i++;
	}
	
	return newN;
}




int main(void){
	int i = 0;
	int n = 20; //length of array.
	int a[]  = {9,9,9,9,9,1,15,2,2,15,9,11,11,9,15,9,9,2,6,7};
	cout << "values in array before reduction: ";
	while(i < n){
		cout << a[i];
		if(i != n-1)
			cout << ",";
		i++;
	}
	cout << "\n";
	
	n = reduce(a,n);
	
	i=0;
	cout << "values in array after reduction: ";
	while(i<n){
		cout << a[i] ;
		if(i != n-1)
			cout << ",";
		i++;
	}
	
	
}
