/********************************************\
| Program: #4 hw 2                           |                   
| Problem: test numbers to see if they are   |
|		   Fibonacci numbers.                |
| Purpose: practice using control statements |
| Author: Karl Bigley-Bodlak                 |
|                                            |                          
\********************************************/

#include <iostream>
#include <math.h>
using namespace std;

void fiboTest(int n){
	/* a is the number currently being compared, b is the next value, 
	** and c is the value after that, which is determined by the 
	** previous two values in the sequence.
	*/
	int a = 0, b = 1, c;
	while(a<=n){
		if(n==a){
		cout << "1" <<endl;
		return;
		}
		c = a+b;
		a = b;
		b = c;
	}
	cout <<"0"<<endl;
}

int main(void){
	fiboTest(7);
	fiboTest(13);
	return 0;
}
