/*
*	Author:Karl Bigley-Bodlak
*	problem: copy a text file into another file whose
	lines are numbered.
*	Program: fileCopierWithLines
*	purpose: practice file manipulation.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
int main (void)
{
	string myline;
	char* IFN = "sample.dat";
	char* OFN = "numbered.dat";
	//opening input and outputfiles.
	ifstream IS1(IFN, ios::in);
	ofstream OS1(OFN, ios::out);
	//i is line number.
	int i=1;
	//while we can get a line from input file,
	//it will write the line number and then the line
	//into the output file.
	while(getline(IS1,myline))
	{
		OS1 <<i<<": "<<myline<<endl;
		i++	;
	}
	//close files.
	IS1.close();
	OS1.close();
	
	return 0;
}
//end program.
