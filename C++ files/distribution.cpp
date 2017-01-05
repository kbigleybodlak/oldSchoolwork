/*
	Program Name:distribution.cpp
	Purpose: plot histogram of random.dat
	Author: Karl Bigley-Bodlak
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
using namespace std;
//n is number of lines.
void line(int n)
{
	while(n)
	{
		cout<<'*';
		n-=1;
	}
}
/*
	data is array of data from random.dat
	lines is array for storing number in ranges.
	n is an iterator
	min and max are used for the display range.
*/
int main(void)
{
	char FN[]="random.dat";
	double data[200], lines[19];
	int n=0, min=0, max=5;
	
	ifstream IS(FN, ios::in);
	while(IS>>data[n])	n++;
	//processes each element of array and gives +1 to its range.
	for(n=0; n<200;n++)
	{
		if(data[n]<=5) lines[0]++;
		else  if(data[n]<=10) lines[1]++;
		else  if(data[n]<=15) lines[2]++;
		else  if(data[n]<=20) lines[3]++;
		else  if(data[n]<=25) lines[4]++;
		else  if(data[n]<=30) lines[5]++;
		else  if(data[n]<=40) lines[6]++;
		else  if(data[n]<=45) lines[7]++;
		else  if(data[n]<=50) lines[8]++;
		else  if(data[n]<=55) lines[9]++;
		else  if(data[n]<=60) lines[10]++;
		else  if(data[n]<=65) lines[11]++;
		else  if(data[n]<=70) lines[12]++;
		else  if(data[n]<=75) lines[13]++;
		else  if(data[n]<=80) lines[14]++;
		else  if(data[n]<=85) lines[15]++;
		else  if(data[n]<=90) lines[16]++;
		else  if(data[n]<=95) lines[17]++;
		else  if(data[n]<=100) lines[18]++;
		
	}
	//display the histogram.
	for(n=0;n<19;n++)
	{
	cout<<min<<"-"<<max<<"\t |";
	line(lines[n]);
	cout<<endl;
	min+=5;
	max+=5;
	}
	return 0;
}
