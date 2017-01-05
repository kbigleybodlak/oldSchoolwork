/*
	Karl Bigley-Bodlak
	CSC 415 homework # 4
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 65537
#define NUMTHREADS 4

/*multithreaded ASCII character count program.
	recieves a file, reads from the file into a buffer.
	spawn threads according to preprocessor variable.
	partitions the buffer according to how many threads there are
	each thread records number of ASCII characters by +1 an array
	element in a two-dimensional array.
	partition bounds should be roughly equal in size.and then passed to each worker thread using a struct.
	pass a thread index to each thread so that it knows where to write its local count in the global 2-
	dimensional int array.
	It should then add the partition counts for each ASCII character and print each overall count.
*/
//global two-dimensional array to hold #of chars read.
int counter[NUMTHREADS][128];
//buffer of items read from file.
char buff[65537];

//threads should have an id# and a capture size.
struct thread_data
{
	//thread id.
	int t_id;
	//size of partition.
	double pSize;
	thread_data(int id, double partitionSize)
	{
		t_id=id;
		pSize = partitionSize;
	}
};

//where thread will begin execution.
DWORD WINAPI thread_func(LPVOID lpParameter)
{
	thread_data *td = (thread_data*)lpParameter;
	//calculate starting and end point in buffer for thread.
	int start = (int)td.pSize*td.t_id;
	int end= start + (int)td.pSize;
	//reads partition up to end or limit of obtained chars.
	while(start<end && buff[start]!='\0')
		counter[td.t_id][(int)buff[start]]++;
		start++;
	return 0;
}

void main (int argc, char *argv[])
{	
	//number of bytes read from file.
	DWORD nbytesread;
	//I/O handle
	HANDLE finput;
	int i, j; //iterators
	double ubound;	
	int sum;
	//array of spawned thread handles used in wait function.
	HANDLE threds[NUMTHREADS];
	
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
		 threds[i]=CreateThread(
 		 NULL,
 		 0,
 		 thread_func,
 		 new thread_data(i,ubound),
 		 0,
 		 NULL
		);
	}
	
	WaitForMultipleObjects(NUMTHREADS,threds,TRUE,INFINITE);
	//when threads are done executing, add up values in the 2-dim array and print them.
	for(i=0; i<128;i++)
	{
		for(j = 1; j<=NUMTHREADS; j++)	
		{
			sum+=buff[j][i];
		}
		printf("%i occurrences of ", sum);
		if(i <= 32 || i == 127)
			printf("%#02x\n", i);
		else
			printf("%c\n",i);
	}
		
		
	
	
	/*last thread must account for less information to read in partition.
		CreateThread(
 		 NULL,
 		 0,
 		 thread_func,
 		 new thread_data(NUMTHREADS,ubound,remainder),
 		 0,
 		 NULL
		);
	*/
	
}


