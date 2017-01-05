/*
*	Author:Karl Bigley-Bodlak
*	problem: hw 8, #3
*	program: relativefiles
*	purpose: practice manipulating relative files.
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;
#define SIZE 10

struct     client        // Client record
{   int    account;      
    char   name[20];
    double balance;
};

//create a file with specified number of blank records.
void make_file(char filename[], int number_of_records)
{
    cout << "\nMAKE_FILE: Creating a blank relative file " << filename
         << " containing " << number_of_records << " records.";
    ofstream OS(filename, ios::out);
    if(!OS) {cerr << "File open error." << endl; exit(1);}
    
    client blank={0, "", 0.0}; // Create an empty client record
    while(number_of_records--)
      OS.write((char *)&blank, sizeof(blank));
    cout << "\nFile created.";
    OS.close();
}


void update_file(char filename[], int maxrec) // Update existing file
{
    client c;
    cout << "\nUPDATE_FILE: enter records in any order)\n";
    fstream OS(filename, ios::in | ios::out);  // Open for random access
    if(!OS) {cerr << filename<< " file open error." << endl; exit(1);}
    
    cout << "\nAccount[1.." << maxrec 
         << "], Name, Balance (0 0 0 to exit)= ";
    cin >> c.account >> c.name >> c.balance;
    
    while(0 < c.account) 
    {
      OS.seekp((c.account-1) * sizeof(client));  // position the pointer
      OS.write((char *)&c, sizeof(c));
      cout << "Account[1.."<< maxrec 
           << "], Name, Balance (0 0 0 to exit)= ";
      cin >> c.account >> c.name >> c.balance;
    }
    OS.close();
}


void show_file(char filename[])  // Sequential display of all records
{
    client c;
    int n=0;
    void *ptr;
    
    ifstream IS(filename, ios::in);  // Open for sequential read
    if(!IS) {cerr << filename<< " file open error." << endl; exit(1);}

    cout << "\n\nSHOW_FILE: The contents of file " << filename;
    while(ptr=IS.read((char *)&c, sizeof(c)))
    {
      cout <<'\n'<< setw(3)<< ++n << setw(6) << c.account <<setw(20)
           << c.name << setw(10) << c.balance;
    }
    IS.close();
}

//allows random access to file for user to add 5% to an account balance
void add_5_percent(char filename[], int maxrec)
{
    client c;
    int acc;
    fstream IOS(filename, ios::in|ios::out);  // Open for read
    if(!IOS) {cerr << filename<< " file open error." << endl; exit(1);}

    cout << "\nadd_5_percent: adds 5% to a balance:";   
    cout << "\n\nAccount number (0 to exit) = "; cin >> acc;
    while(0 < acc && acc <= maxrec)
    {
      IOS.seekg((acc-1) * sizeof(client));  // position the pointer
      IOS.read((char *)&c, sizeof(c));
      if(c.account) 
	  {
	  	c.balance*=1.05;//adding 5% to balance
	  	IOS.seekp((acc-1) * sizeof(client));  // position the pointer
      	IOS.write((char *)&c, sizeof(c));

	  } 
      else cout << "\nEmpty record";
      cout << "\n\nAccount number (0 to exit) = "; cin >> acc;
    }
    IOS.close();
}

//FN is filename
int main(void)
{
	char FN[] ="bankclients.dat" ;
	make_file(FN, SIZE);
	update_file(FN, 10);
	show_file(FN);
	add_5_percent(FN,10);
	show_file(FN);
	return 0;
}
