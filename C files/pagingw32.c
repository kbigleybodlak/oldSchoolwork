/*
	Karl Bigley-Bodlak	
	CSC415 hw 6
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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
	int shift;
	int ifFault=0;
	char str[101];
	//args check.
	if(argc!=5){
		printf("error: requires 4 arguements.\nUsage: pagesize logicalmemsize LRUorFIFO #framesallocated");
		return;
	}
	if(strcmp(argv[3],"FIFO")==0 ||strcmp(argv[3],"LRU")==0)
	{}else{
		printf("error:Please enter FIFO or LRU for the 3rd arg.\n");
		return;
	}
	//need positive numbers for it to work.
	if(atoi(argv[1])<0 || atoi(argv[2])<0 || atoi(argv[4])<=0)
	{
		printf("error: need positive numbers for pageSize, logicalMemSize, and #frames.");
		return;
	}
	shift = (int)atoi(argv[1]);
	logMemSize=(int)pow(2,atoi(argv[2]));
	pageSize=(int)pow(2,atoi(argv[1]));
	numFrames = atoi(argv[4]);
	//if logical memory is smaller than page size, we can assume that logical mem can fit on one page.
	if(pageSize>logMemSize){
		printf("page faults: 1\n");
		return;
	}

	numPages = (int)(logMemSize/pageSize); 	
	frameTable = (int*)malloc(numPages*2*sizeof(int));
	for(j=0; j<numFrames;j++)
		*(frameTable+1+j*2)=0;
	printf("\nPlease enter your addresses. Enter an empty line to finish.\n");

	
	i=0;	
	fgets(str,100,stdin);
	while(strcmp(str,"\n")!=0){
		//shift to get pg #, then store in array. only gets 100 inputs.
		//PROBLEM: what if logical memory is smaller. need check.
		nextPage=strtoul(str,NULL,0);
		if(nextPage>logMemSize){
			printf("\nError: Does not fit in logical memory. Please enter new address.\n");
			fgets(str,100,stdin);
			continue;
		}
		nextPage =nextPage >> shift;
		if(i<100){
			//all pages stored as numbers>0
			inputs[i]=(int)nextPage+1;
			i++;
		}
		fgets(str,100,stdin);
	}
	inputs[i]=0;
	i=0;
	//for each address, check if its page is in the table of pages allocated frames.
	if(strcmp(argv[3],"LRU")==0)
	{
		//while we still have page nums>0.
		while(inputs[i]>0)
		{
			//check column if page is in table already.
			for(j=0;j<numFrames;j++)
			{
				//if the page matches, put the value of i in the column 
				//to show the frame has been used by the value.
				if(inputs[i]==*(frameTable +j*2))
				{
					*(frameTable +j*2 +1)=i+1;
					ifFault=1;
					break;
				}
			}
			//page replacement.
			if(ifFault==0)
			{
				pageFaults++;
				min=*(frameTable +1);
				victim=0;
				//getting smallest number in the second column (LRU) and setting victim to min's first column.
				for(j=1;j<numFrames;j++)
				{
					if(*(frameTable +1+j*2)<min)
					{
						min=*(frameTable +1+j*2);
						victim=j;
					}
					
				}
				//debugging tool for LRU.
				//printf("%i  %i.\n",min, victim);
				//replacing victim.
				*(frameTable +victim*2)=inputs[i];
				*(frameTable + 1 + victim*2)=i+1;
			}
			
			i++;
			ifFault=0;
		}
	}else 
	{
		victim =0;
		while(inputs[i]>0)
		{
			for(j=0;j<numFrames;j++)
			{
				//if the page matches, put the value of i in the column 
				//to show the frame has been used by the value.
				if(inputs[i]==*(frameTable +j*2))
				{
				ifFault=1;
				break;
				}	
			}
			//if the page isnt in the frame table, we pick a victim and replace them.
			//in FIFO, we can use our pageTable like a circular array, considering that we start at 0.
			if(ifFault!=1)
			{
				pageFaults++;
				victim=victim%numFrames;
				*(frameTable +victim*2)=inputs[i];
				victim++;
			}
		i++;
		ifFault=0;
		}
	}
	
	
	printf("\n%i faults generated.\n",pageFaults);
	free(frameTable);
	return;
}
