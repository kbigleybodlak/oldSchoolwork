/*
	CSC 600 HW3: Procedural programming
	program:maxLength
	Purpose: Write a function maxlen(a,n) that returns the length of the longest sequence of  identical numbers 
	Author: Karl
	Problem 1: Plateau
*/
#include<iostream>
using namespace std;
/**

	@param int a[] the sorted integer array to be analyzed.
	@param int n the length of the array
*/
int MaxLength(int a[], int n)
{
	int longestLength = 1;
	int currentLongestLength = 0;
	int nextLongestLength;
	int currentNum;
	int iterator;
	
	int i=0;
	//checking for empty array variable.
	if(a == NULL)
	{
		return 0;
	}
	
	currentNum = a[0];
	while(i<n)
	{
		iterator = a[i];
		
		//when we reach a new number
		if(iterator != currentNum)
		{
			//make that number the current number being counted
			currentNum = iterator;
			//change the longestLength if the previous count was greater.
			if(currentLongestLength > longestLength){
				longestLength = currentLongestLength;
			}
			//reset the count.
			currentLongestLength = 1;
				
		}else{
			currentLongestLength++;
		}
		
		i++;
	}
	
	return longestLength;
}

int main(void)
{
	int maxLength = 0;
	int a[] = {1,1,1,2,2,4,4,4,45,45,45,109,109,109,109,109,110,110,110,111};
	maxLength = MaxLength(a,20);
	cout << "maxlength of the array is : " << maxLength << "\n";
	
	
}







/* 2.

*/
