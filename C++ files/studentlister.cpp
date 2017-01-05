/*
	Program Name:StudentLister.cpp
	Problem: given a file of students, store and manipulate
	data about the students using structs.
	Purpose: practice making structs to organize data
	Author: Karl Bigley-Bodlak
	date:11/12/14
*/
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<string>
#include<math.h>
using namespace std;

struct Date 
{ int month;
int day;
int year;
} ;
struct Student
{ string name;
Date dob;
double GPA;
} S[200];

/*
	grabs a file called students.txt and reads it word by 
	word into variables firstname, lastname, date, and gpa.
	realgpa is the gpa given to the struct Student.
	meangpa is the mean of the gpa, mean age is mean of ages, 
	stddevgpa is standard deviation for gpa, likewise for age.
	variancegpa is the variance for gpa, similar for age.
	coeffvar is coefficient of variation, with endings to denote
	age or gpa.
	i is the number of entries that are currently in the array
	of students, S.
*/
int main(void)
{
	char FN[]="students.txt";
	//n is an iterator, month day year are the data 
	//within dob.	
	int n=0, month, day, year;
	string  firstname, lastname, date, gpa;
	double realgpa, meangpa,meanage, stddevgpa, coeffvargpa,
		i=0.,variancegpa, varianceage, stddevage,coeffvarage,
		meanyear;
	ifstream IS(FN, ios::in); //open file
	while(IS>>firstname>>lastname>>date>>gpa)
	{
		S[n].name = firstname+lastname;
		day = ((date[3]-'0')*10)+(date[4]-'0');
		month = ((date[0]-'0')*10)+(date[1]-'0');
		year =((date[6]-'0')*10)+(date[7]-'0');
		if(year<15) year+=2000;
		else year+=1900;
		S[n].dob.day =day ;
		S[n].dob.month=month;
		S[n].dob.year=year;
		//cast to double for ability to use decimals.
		realgpa = ((double)gpa[0]-48.)+
				(((double)gpa[2]-48.)/10.)
				+(((double)gpa[3]-48.)/100.);
		S[n].GPA=realgpa;
		n++; i++;
	}
	IS.close(); //close file.
	//only goes through array until last entry put in.
	for(n=0; n<i;n++)
	{
		meangpa+=S[n].GPA;
		//this year - birth year
		meanage+=(2014.-S[n].dob.year);
		//if birthday has not happened yet, subtract one.
		if(S[n].dob.month>11 &&S[n].dob.day>12)
			meanage-=1;
	}
	meangpa/=i;//mean= (sum of n terms)/n
	meanage/=i;
	cout<<"the mean gpa is: "<<meangpa<<endl
	    <<"the mean age is: "<<meanage<<endl;
	meanyear = (2014.-meanage);
	for(n=0; n<i;n++)
	{	//variance=sum of square differences over n-1 terms
		variancegpa+=pow(S[n].GPA-meangpa,2);
		varianceage+=pow(S[n].dob.year-meanyear,2);
	}
	variancegpa/=i-1.;
	varianceage/=i-1.;
	stddevgpa=sqrt(variancegpa);
	stddevage=sqrt(varianceage);
	coeffvargpa = stddevgpa/meangpa;
	coeffvarage = stddevage/meanage;
	cout<<"the standard deviation for age is "<<stddevage
		<<endl<<"the standard deviation for gpa is "
		<<stddevgpa<<endl<<"the coefficicent of variation for age is: "
		<<coeffvarage<<endl<<"the coefficient of variation for gpa "
		<<"is "<<coeffvargpa<<endl;
	return 0;
}

