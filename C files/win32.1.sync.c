/*
	Karl Bigley-Bodlak
	CSC 415 homework # 5a
	redo hw 4 but with a one-dimensional array no mutex.
*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 65537
#define NUMTHREADS 8

//global one-dimensional array to hold #of chars read.
int counter[128];
//buffer of items read from file.
char buff[65537];
//mutex for array access.
void* mut; 
//threads should have an id# and a capture size.
typedef struct
{
	//thread id.
	int t_id;
	//size of partition.
	double pSize;
}thread_data;


//where thread will begin execution.
DWORD WINAPI thread_func(LPVOID lpParameter);

void main (int argc, char *argv[])
{	
	//number of bytes read from file.
	DWORD nbytesread;
	//I/O handle
	HANDLE finput;
	int i, j; //iterators
	double ubound;	
	mut = CreateMutex(NULL,FALSE,NULL);
	//array of spawned thread handles used in wait function.
	HANDLE threds[NUMTHREADS];
	//array of each thread's data.
	thread_data newtd[NUMTHREADS];
	//arg check.
	if(argc!=2)
	{	
		printf("error:only type filename as arguement.");
		return;
	}
	
	//open file and check if it exists.
	finput=CreateFile(argv[1],GENERIC_READ,0,
	NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if((GetLastError()==ERROR_FILE_NOT_FOUND))
	{
		printf("error:could not read input file.");
		return;
	}
	//grab text from file.
	ReadFile(finput,buff,BUFFER_SIZE,&nbytesread,NULL);
	CloseHandle(finput);
	//use NUMTHREADS to partition the array 
	ubound = ceil(nbytesread/NUMTHREADS);
	//create threads.
	for(i=0;i<NUMTHREADS;i++)
	{
		newtd[i].t_id=i;
		newtd[i].pSize=ubound;
		//create thread and store handle in array.
		threds[i]=CreateThread(
 	    NULL,
 		0,
 		thread_func,
 		&newtd[i],
 		0,
 		NULL
		);
		//)
		//{
		//	printf("error in creating thread");
	//		return;
		//}
	}
	for(i=0;i<NUMTHREADS;i++)
		WaitForSingleObject(threds[i],INFINITE);

	//when threads are done executing, add up values in the 2-dim array and print them.
	int sum=0;
	for(i=0; i<128;i++)
	{
		printf("%i occurrences of ", counter[i]);
		if(i <= 32 || i == 127)
			printf("%#x\n", i);
		else
			printf("%c\n",i);
		sum=0;
	}
}
	
	//calculate starting and end point in buffer for thread.
	//reads partition up to end or limit of obtained chars.
	//Uses mutex to prevent data racing.
	DWORD WINAPI thread_func(LPVOID lpParameter)	
	{

		thread_data td = *(thread_data*)lpParameter;

	
		int start = (int)td.pSize*td.t_id;
		int end= start + (int)td.pSize;
		while(WaitForSingleObject(mut,INFINITE)){};
	
		while(start<end && buff[start]!='\0')
		{
			counter[(int)buff[start]]++;
			start++;
		}
		ReleaseMutex(mut);
		return 0;
	}


