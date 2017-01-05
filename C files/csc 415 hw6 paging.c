/*
	Karl Bigley-Bodlak	
	CSC415 hw 6
	Write a program that simulates the FIFO and LRU page-replacement algorithms. Your program should
accept four command-line arguments specifying the page size, the total logical memory size, the pagereplacement
algorithm to use, and the number of frames allocated. The page and logical memory sizes
should be specified by their binary logs. Thus, the following command would simulate a page size of
1KB and a logical memory size of 64KB, using LRU page-replacement with 8 frames allocated:
./simulate-paging 10 16 LRU 8
Your program should read lines from standard input, each containing a hexadecimal number
representing the virtual address of a memory reference. With each memory reference, your program
should update an internal page table, keeping track of the number of page faults generated (using pure
demand paging). Your program should also maintain any other data structures necessary to implement
the two page-replacement algorithms. Your program should terminate upon reading a blank line from
standard input. It should then print the total number of page faults and exit.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//TODO: account for someone entering stuff too.
void main (int argc, char *argv[])
{
	int i,j, min, victim;
	int logMemSize;
	int pageSize;
	int numFrames; 
	int numPages;  	
	int* frameTable; 
	unsigned long nextPage;
	int inputs[101];
	int pageFaults=0;
	int ifFault=0;
	char* str;
	//args check.
	if(argc!=5){
		printf("error: requires 4 arguements.\nUsage: pagesize logicalmemsize LRUorFIFO #framesallocated")
		return;
	}
	//need positive numbers for it to work.
	if(argv[1]<0 || argv[2]<0 || arg[4]<=0)
	{
		printf("error: need positive numbers for pageSize, logicalMemSize, and #frames.");
		return;
	}
	
	logMemSize=(int)pow(2,atoi(argv[2]));
	pageSize=(int)pow(2,atoi(argv[1]));
	numFrames = argv[4];
	//if logical memory is smaller than page size, we can assume that logical mem can fit on one page.
	if(pagesize>logMemSize)){
		printf("page faults: 1\n");
		return;
	}

	numPages = (int)(logMemSize/pageSize); 	
	frameTable = (int*)malloc(numPages*2*sizeof(int));
	printf("\nPlease enter your addresses. Enter an empty line to finish.\n")
	//check if page is in frameTable.
	//if not, find an open frame.
	//if no frames available, go to replacement alg.
	//INSTEAD: use fgets with a check before loop and at the end of the while loop, so it reads it each time.
	//fgets writes to a buffer and  checks for newline character at buffer[0]
	//if yes: stop reading, exit loop.
	//then use (unsigned int) strtoul(buffer) to change the strings to an unsigned long 
	//check the number so that it fits into the logical memory. it cannot reference something outside of that memory. if it does, print error and get next value
	//srl to get the page number and store it in the array for inputs.
	
	i=0;	
	fgets(str,100,stdin);
	while(str[0]!="\n"){
		//shift to get pg #, then store in array. only gets 100 inputs.
		//PROBLEM: what if logical memory is smaller. need check.
		nextPage=strtoul(str,NULL,0);
		if(nextPage>logMemSize){
			printf("\nError: Does not fit in logical memory. Please enter new address.\n");
			fgets(str,100,stdin);
			continue;
		}
		nextPage>>(int)argv[1];
		if(i<100){
			inputs[i]=nextPage;
			i++;
		}
		fgets(str,100,stdin);
	}
	inputs[i+1]=-1;
	i=0;
	
	//for each address, check if its page is in the table of pages allocated frames.
	if(arg[3]=="LRU")
	{
		while(inputs[i]>=0)
		{
			for(j=0;j<numPages;j++)
			{
				//if the page matches, put the value of i in the column 
				//to show the frame has been used by the value.
				if(inputs[i]+1==*(frameTable +j*2))
				{
					*(frameTable +j*2 +1)=i;
					ifFault=1;
				}
			}
			//page replacement.
			if(ifFault==0)
			{
				pageFaults++;
				min=*(frametable +1);
				victim=0;
				//getting smallest number in the second column (LRU)
				for(j=1;j<numFrames;j++)
				{
					if(*(frametable +1+j*2)<min)
					{
						min=*(frametable +1+j*2);
						victim=j;
					}
				}
				//replacing victim.
				*(frametable + victim*2)=inputs[i];
				*(frametable + 1 + victim*2)=i;
			}
			
			i++;
			ifFault=0;
		}
	}else if(argv[3]=="FIFO")
	{
		victim =0;
		while(inputs[i]>0)
		{
			for(j=0;j<numPages;j++)
			{
				//if the page matches, put the value of i in the column 
				//to show the frame has been used by the value.
				if(inputs[i]+1==*(frameTable +j*2))
					ifFault=1;
					
			}
			//if the page isnt in the frame table, we pick a victim and replace them.
			//in FIFO, we can use our pageTable like a circular array, considering that we start at 0.
			if(ifFault!=1)
			{
				pageFaults++;
				*(frameTable +(nextVictim%numPages)*2)=inputs[i];
				victim++;
			}
		i++;
		ifFault=0
		}
	}else{
		printf("for the 3rd arguement, please enter LRU or FIFO.\n")
		return;
	}
	
	
	printf("\n%i faults generated.\n",pageFaults);
	free(frameTable);
	return;
}
