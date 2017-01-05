#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main (int argc, char *argv[]){
	HANDLE inputFile;
	inputFile=CreateFile("randomAddresses.txt",GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	
}
