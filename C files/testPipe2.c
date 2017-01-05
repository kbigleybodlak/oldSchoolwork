/* CSC 415 
* HW3 Win32 
Only need to support ONE operator per command.
*/
 
 #include <stdio.h> 
 #include <windows.h> 
 #include <string.h> 
 

 #define BUFFERSIZE 1024 
 
 int main() {
 
  	char input[BUFFERSIZE+1];
  	fgets(input,BUFFERSIZE,stdin);
  	printf("The output\n %s",input);
  	return 0;
}
