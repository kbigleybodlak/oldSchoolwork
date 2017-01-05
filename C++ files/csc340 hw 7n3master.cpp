/*
*	Author:Karl Bigley-Bodlak
*	problem: hw7, #3
*	program: polymaster
*	purpose: practice using master/engine model to pass command
*	line arguments
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

int main(void)
{
	char FN[]="polysolutions.dat",myline[80];
	system("polyengine 7.7 7.7 6 polysolutions.dat");
	system("polyengine -0.99 89.8 0 polysolutions.dat");
	system("polyengine 1 5 -2 polysolutions.dat");
	system("polyengine 8.62 9 14 polysolutions.dat");
	ifstream IS(FN,ios::in);
	//display contents of file
	while(IS.getline(myline,80)) cout<<myline<<endl;
	return 0;
}
//end program

/*
x1: 0.5 + i(0.727476)  x2: 0.5 - i(0.727476)
x1: -90.7071  x2: 0
x1: 5.37228  x2: -0.372281
x1: 0.522042 + i(1.16258)  x2: 0.522042 - i(1.16258)

--------------------------------
Process exited after 2.241 seconds with return value 0
Press any key to continue . . .
*/
