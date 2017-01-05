/*
	CSC 600 HW3: Procedural programming
	Purpose: create efficient programs using procedural programming
	Prints out a positive integer in a 7*7 frame of an enlarged version of itself
	Author: Karl
	Problem 4: BigIntegers
*/
#include<iostream>
using namespace std;

void BigInt(int n)
{
	int isNegative; //checks for negative number
	int currentDigit; //the current number to process
	int length; //how many numbers to process
	//iterators
	int i;
	int j;
	int k;
	//assuming we won't get ints longer than 100 characters
	int numsToPrint[100]; 
	
	if(n==NULL || n<0)
	{
		cout << "number needs to be postive integer. \n";
		return;
	}
	
	char numbers[11][49]=
	{
		{
				  ' ','@','@','@','@','@',' ',
				  '@','@',' ',' ',' ','@','@',
				  '@','@',' ',' ',' ','@','@',
				  '@','@',' ',' ',' ','@','@',
				  '@','@',' ',' ',' ','@','@',
				  '@','@',' ',' ',' ','@','@',
				  ' ','@','@','@','@','@',' '
		},
		{
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ','@','@','@',' ',' ',
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ',' ','@','@',' ',' ',
				  ' ','@','@','@','@','@','@'
		},
	
		{
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ','@','@','@','@',' ',
				  ' ','@','@',' ',' ','@','@',
				  ' ',' ',' ',' ','@','@',' ',
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ','@','@',' ',' ',' ',
				  '@','@','@','@','@','@','@'
	    },
	
		{	
				  ' ',' ','@','@','@',' ',' ',
				  ' ','@','@','@','@','@',' ',
				  ' ',' ',' ',' ',' ','@','@',
				  ' ',' ','@','@','@','@','@',
				  ' ',' ',' ',' ',' ','@','@',
				  ' ','@','@','@','@','@','@',
				  ' ',' ','@','@','@','@',' '
		},
	
		{
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ','@','@','@',' ',' ',
				  ' ','@','@',' ','@',' ',' ',
				  '@','@','@','@','@','@','@',
				  '@','@','@','@','@','@','@',
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ',' ','@','@',' ',' '
		},	  
	
		{	
		  		  '@','@','@','@','@','@','@',
				  '@','@',' ',' ',' ',' ',' ',
				  '@','@',' ',' ',' ',' ',' ',
				  '@','@','@','@','@','@',' ',
				  ' ',' ',' ','@','@','@','@',
				  ' ',' ','@','@','@','@',' ',
				  '@','@','@','@','@',' ',' '
		},
		
		{
				  ' ','@','@','@','@','@','@',
				  '@','@','@','@','@','@','@',
				  '@','@',' ',' ',' ',' ',' ',
				  '@','@','@','@','@','@','@',
				  '@','@',' ',' ',' ','@','@',
				  '@','@',' ',' ',' ','@','@',
				  ' ','@','@','@','@','@',' '
		},
				  
		{
				  '@','@','@','@','@','@','@',
				  ' ',' ',' ',' ',' ','@','@',
				  ' ',' ',' ',' ','@','@',' ',
				  ' ',' ',' ','@','@',' ',' ',
				  ' ',' ','@','@',' ',' ',' ',
				  ' ','@','@',' ',' ',' ',' ',
				  '@','@',' ',' ',' ',' ',' '
		},	
				  
		{
				  ' ','@','@','@','@','@',' ',
				  '@','@',' ',' ',' ','@','@',
				  '@','@',' ',' ',' ','@','@',
				  ' ','@','@','@','@','@',' ',
				  '@','@',' ',' ',' ','@','@',
				  '@','@',' ',' ',' ','@','@',
				  ' ','@','@','@','@','@',' '
		},
				  
		{
				  ' ','@','@','@','@','@',' ',
				  '@','@',' ',' ',' ','@','@',
				  '@','@',' ',' ',' ','@','@',
				  ' ','@','@','@','@','@','@',
				  ' ',' ',' ',' ',' ','@','@',
				  ' ',' ',' ',' ',' ','@','@',
				  ' ',' ',' ',' ',' ','@','@'
		},
				  
		{
				   ' ',' ',' ',' ',' ',' ',' ',
				   ' ',' ',' ',' ',' ',' ',' ',
			       '@','@','@','@','@','@','@',
				   '@','@','@','@','@','@','@',
			       '@','@','@','@','@','@','@',
			       ' ',' ',' ',' ',' ',' ',' ',
				   ' ',' ',' ',' ',' ',' ',' '
		}
	};		  
	
	/*
		get the right-most number,
		get the pattern it maps to
		add it to the final array to be printed out.
	*/
	i = 0;
	while(n>0)
	{
		
		currentDigit = n%10; //get the right-most digit.
		numsToPrint[i] = currentDigit; //add the digit to an array
		i++;
		n = n/10; //shift the number right.
	}	
	
	k = i-1;
	length = i-1; //length knows how many 7*7 pieces to print. Represents the index of the array to print.
	i=0;
	j=0;
	while(i<7)//for each row of chars to print. the HEIGHT of the number
	{
		while(length>=0)//for each 7-char segment to print.  the WIDTH of the number
		{
			//read the charsToPrint backwards, to print the big number in order.
			while (j<7)
			{			
				cout << numbers[ numsToPrint[length] ][j+(7*i)]; 
				j++;
			}
			cout << " ";	
			j = 0;
			length--;;
		}
		cout<<endl;
		length = k;
		i++;
	}
}

int main(void)
{
	BigInt(572);
}
