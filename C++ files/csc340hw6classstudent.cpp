/*
*	Author:Karl Bigley-Bodlak
*	problem: hw6, #1, studentclass
*	purpose: Practice using classes and creating 
*	function sets for these classes.
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include<cstring>
using namespace std;

/*
	I was aiming for the student class to be applicable to any 
	filename, so it could be possible to input a file and read
	it for student objects.
	NOTE: I generalized most of the functions in this program
	so they could be easily applicable to other programs.
	This may have decreased the efficiency of this program 
	by opening and closing files repeatedly, but I 
	reasoned that adaptability would be more favorable 
	than maximum effieciency for thepurpose of practicing
	writing code in this class.
*/
class student
{
	private:
	string name;
	int age;
	double gpa;			
	public:
	student(){student(" ",0,0.0);} 
	
	student(string x,int y, double z)
	{
		name=x;
		age=y;
		gpa=z;

	}
	

	
	//prompts user to enter name, age, and gpa of student
	int read()
	{
		string age1, name1,gpa1;
		cout<<"please enter the students in this format: fullname "
		<<"age gpa.\nMake sure you put age in two digits and  "
		<<"gpa with two significant figures\n "
		<<"enter CTRL-Z when you are finished.\n\n";
		//read data input until user enters ctrl-Z
		cin>>name1>>age1>>gpa1;
		if(cin.eof()) return 0;
		name=name1;
		//conversion 
		age = 10*((int)age1[0]-48)+((int)age1[1]-48);
		gpa = ((int)gpa1[0]-48)+
		(((int)gpa1[2]-48)/10.)
		+(((int)gpa1[3]-48)/100.);

		return 1;
	}
	//displays student name, age, and gpa.
	void show()
	{
		cout<<name<<": age: "<<age<<" gpa: "<<gpa<<'\n';
	}
	
	//gets the gpa of a student from inputted students
	double getgpa()	{return gpa;}
	//gets gpa of student from a file. If not found, 
	//returns -1.
	double getgpa(string st,char* FN)
	{
		ifstream IS2(FN, ios::in);
		string string1,age1,gpa1;
		while(IS2>>string1>>age1>>gpa1)
			if(string1==st) 
			{
				IS2.close();
				return ((int)gpa1[0]-48)+
				(((int)gpa1[2]-48)/10.)
				+(((int)gpa1[3]-48)/100.);
			}
		IS2.close();
		cout<<"student not found.\n\n";
		return -1.;

	}
	
	/*
	appends the record of the student into designated filename.
	sets width of variables to fill in zeroes on the end of 
	values such as 2.00 or 3.30.
	*/
	void writefile(char* FN)
	{
		ofstream OS(FN, ios::app);
		OS.setf( std::ios::fixed, std:: ios::floatfield ); 
		OS<<name<<"  ";
		OS.width(2);
		OS<<age<<"  ";
		OS.precision(2);
		OS.width(3);
		std::cout.setf( std::ios::fixed, std:: ios::floatfield ); 
		std::cout.precision(2);
		OS<<gpa<<'\n';
		OS.close();
	}
	
	/*
	display record of student in FN, filename. 
	if not found in file, displays message and returns 0.
	can be used with any object of type of class student.
	returns 1 if search is successful.
	*/
	int readfile(char* FN)
	{
		ifstream IS1(FN, ios::in);
		string name1, name2;
		char printline[80];
		cout<<"please enter the name of the student you are searching for.";
		cin>>name2;
		while(IS1>>name1)
		{
			if(name1==name2)
			{
				IS1.getline(printline,80);
				cout<<name2<<": "<<printline<<'\n';
				IS1.close();
				return 1;
			}
		}
		cout<<"Record for student not found in file.\n";
		IS1.close();
		return 0;
	}
}S[100];

//Opens a passed file, extracts three elements,
//converts to proper values, and calculates mean gpa for 
//all students in passed file name. 
double findfilemean(char* FN)
{
	string name1,age1,gpa1;
	int p=0; //counter for number of entries in file
	double mean; //the gpa mean
	ifstream IS(FN, ios::in); 
	//display contents of file and add gpa to mean
	while(IS>>name1>>age1>>gpa1)
	{
		mean+=((double)gpa1[0]-48.)+
		(((double)gpa1[2]-48.)/10.)
		+(((double)gpa1[3]-48.)/100.);
		p++;
	}
	IS.close();
	mean/=p;
	return mean;
}
/*
	i is an iterator for number of entries through the read.
	j is an iterator for total entries in file.
	k is a simple iterator.
	FN is filename.
	a is a blank student used for general commands in 
	class student.
*/
int main(void)
{
	char* FN= "student.dat";
	student a;
	cout<<"searching file using readfile.\n";
	a.readfile(FN);
	int i=0, j=0,k;

	//continues until eof is detected in input.
	while (!cin.eof())
	{
		if(S[i].read())
	//only writes to file if read is successful.
		{
			S[i].writefile(FN);
			i++;
		}
	}
	cout<<"last record entered.\n";
	S[i-1].show();
	cout<<"second record entered.\n";
	S[1].show();
	
	//display contents of file after putting it in an
	//array for easy processing.
	cout<<"below records are from file.\n";
	ifstream IST(FN, ios::in); //input file FN
	string name, age1,gpa1;
	int age;
	double gpa;
	//problem: out of bounds error when gpa has zeroes at beginning or end.
	while(IST>>name>>age1>>gpa1)
	{
		age = 10*((int)age1[0]-48)+((int)age1[1]-48);

		gpa = ((int)gpa1[0]-48)+
		(((int)gpa1[2]-48)/10.)
		+(((int)gpa1[3]-48)/100.);
		S[j]= student(name, age, gpa);
		j++;
	}
	for(k=0;k<j;k++)
		S[k].show();

	cout<<"the mean gpa is: "<<findfilemean(FN)<<endl;
	cout<<"the gpa of the last student entered is: "
		<<S[j-1].getgpa()<<endl;
	cout<<"robert's gpa from the file: "
		<<a.getgpa("tronton","student.dat")<<endl;

	return 0;
}
