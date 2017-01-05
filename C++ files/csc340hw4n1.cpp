/*
*	Author:Karl Bigley-Bodlak
*	problem: read a string from the user and display the 
*			corresponding American date to the console.
*	Program: datePrinter
*	purpose: Practice with manipulating C-strings and 
*				the string class.
*/

//begin program. This is the C-string version
#include <iostream>
#include <cstring>
using namespace std;

/*
	printdate asks the user for a numerical date, checks the month, 
	day, and year for validity, and then prints the American
	date.
	date is the array that user input is stored in.
	a and b are used to manipulate chars in the c-string.
	monthdate is the c-string used for the final display of the 
	date.
	month is the numerical value of the date.
	day is the integer form of the day input.
	year is the year input by the user as an int
	note: this version has only a hundred year span,
	with the center limits being 1951 to 2050.
*/
void printDate()
{
	char date[80];
	int a,b;
	cout<< "please enter a numerical date with each section using " 
		<< "two numbers and seperated by /. no spaces in between numbers, "
		<<"and please only type it in the left-most spaces of your input."
		<<endl;
	cin.getline(date,80);
	a= (int)date[0] -48;
	b= (int)date[1] -48;
	int month = (10*a)+b;
	/*uses numerical value of month to create a c-string that
	monthdate points to. default case restarts program if
	the month is not 1-12.
	*/
	 char* monthdate;//NOTE: INEFFICIENT: take it from an array.
		switch(month)
		{
			case 1:
				monthdate = "January";
				break;
			case 2:
				monthdate = "February";
				break;
			case 3:
				monthdate = "March";
				break;
			case 4:
				monthdate = "April";
				break;
			case 5:
				monthdate = "May";
				break;
			case 6:
				monthdate = "June";
				break;
			case 7:
				monthdate = "July";
				break;
			case 8:
				monthdate = "August";
				break;
			case 9:
				monthdate = "September";
				break;
			case 10:
				monthdate = "October";
				break;
			case 11:
				monthdate = "November";
				break;
			case 12:
				monthdate = "December";
				break;
			default:
				cout<< "please enter a valid date."<<endl;
				printDate();
				break;
		}
	//taking next two numbers and converting to ints for day.
	a = (int)date[3]-48;
	b = (int)date[4]-48;
	int day = (a*10) + b;
	//final two chars convert to ints for year.
	a = (int)date[6]-48;
	b = (int)date[7]-48;
	int year = (a*10)+b;
	//sets range from 2050 to 1950.
	if(year<=50) a = 2000; else a = 1900;
	int yearDate = a + year;
	//final output.
	cout << monthdate <<" "<< day <<", "<< yearDate;
}

int main(void)
{
	printDate();
	return 0;
}
//end program.
