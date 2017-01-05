/*
*	Author:Karl Bigley-Bodlak
*	problem: store data about cars into a file
	from the user. display cars from this file that
	meet certain criteria.
*	Program: carComparer
*	purpose: practice file manipulation with user input.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
//manufacturer, model, year, miles,cost of each car.
int main (void)
{
	double miles, cost;
	string manufacturer, model, year, myline;
	char FN[]="used.car.dat";
	ofstream OS1(FN, ios::out);
	cout<< "please enter, in order, the manufacturer, model, "
		<<"year, miles, and cost of the car.\nWhen you are done," 
		<<"use ctrl-z.\n";
	//user input gets put into file.
	while(getline(cin,myline))
	{
		OS1<<myline<<endl;
	}
	OS1.close();
	
	//open up file to read.
	ifstream IF1(FN, ios::in);
	cout<<"\n\n The cars with less than 50,000 miles and"
		<<"cost less than $9,000.\n\n"
	while(IF1>>manufacturer>>model>>year>>miles>>cost)
	{
		if(miles<50000. && cost<9000.)
		cout<<manufacturer<<'\t'<<model<<'\t'<<year<<'\t'
			<<miles<<'\t'<<cost<<endl;
	}
	
	
	return 0;
}

