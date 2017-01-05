/*
	Karl BIgley-Bodlak
	CSC 415 hw 5
	producer consumer problem with a bounded buffer.
	Use full and empty semaphores to keep track of the numbers of full and empty slots available to the consumers and
    producers, respectively.
    Use a mutex to coordinate access to the buffer
    The consumers need to each consume the same number of items before exiting
    consumer threads should consume these items by printing them.
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int coconuts[16];

//control for place in circular array to go to next for each producer and consumer.
int prodplace=0;
int consumeplace=0;

//mutex for buffer, then 2 semaphores.
void* buffmutex;
void* full;
void* empty;

/*
	t_id is thread id.
	num_items is the number of items to process.
*/
typedef struct
{
	int t_id;
	int max_items;

}thread_data;

//thread_data *producer_info;
//thread_data *consumer_info;

DWORD WINAPI produce(LPVOID lpParameter);
DWORD WINAPI consume(LPVOID lpParameter);
 
/*
	i is an iterator
	num_to produce is number of items to produce
	num_to_consume is # items to consume. 
	last_producer_thread holds the last producer 
	thread created for main function wait.
	buffmutex is the mutex for the global buffer coconuts.
	full is the semaphore for the number of full slots in 
	the coconuts array.
	empty is the semaphore for the empty slots.
*/
void main(int argc, char* argv[]){
	
	int i;
	int num_to_produce;
	int num_to_consume;
	HANDLE* producers;
	HANDLE* consumers;
	buffmutex = CreateMutex(NULL,FALSE,NULL);
	full = CreateSemaphore(NULL,0,15,NULL);
	empty = CreateSemaphore(NULL,15,15,NULL);
	
	if(argc!=4){
		printf("error:Please enter 3 arguments");
		return;
	}
	
	int num_producers =(int)pow(2,atof(argv[1]));
	int num_consumers =(int)pow(2,atof(argv[2]));
	int num_produced = (int)pow(2,atof(argv[3]));
	num_to_produce = num_produced/num_producers;
	num_to_consume = num_produced/num_consumers;
	
	//creating dynamically sized arrays of thread information
	thread_data* producer_info=
	(thread_data*)malloc(sizeof(thread_data) * num_producers);
	thread_data* consumer_info=
	(thread_data*)malloc(sizeof(thread_data)*num_consumers);
	
	producers = (HANDLE*)malloc(sizeof(HANDLE)*num_producers);
	consumers = (HANDLE*)malloc(sizeof(HANDLE)*num_consumers);
	
	//spawn producers
	for(i = 0; i<num_producers;i++){
		producer_info[i].max_items=num_to_produce;
		producer_info[i].t_id=i;
		producers[i]=CreateThread(
			NULL,
 			0,
 			produce,
 			&producer_info[i],
 			0,
 			NULL
		);
	}
	
	//spawn consumers.
	for(i = 0; i<num_consumers;){
		consumer_info[i].max_items=num_to_consume;
		consumer_info[i].t_id=i;

		consumers[i]=CreateThread(
			NULL,
 			0,
 			consume,
 			&consumer_info[i],
 			0,
 			NULL
		);
		i++;
	}
	//wait for thread resolutions.
	for(i=0;i<num_producers;i++)
		WaitForSingleObject(producers[i],INFINITE);
	for(i=0;i<num_consumers;i++)
		WaitForSingleObject(consumers[i],INFINITE);
	free(producer_info);
	free(consumer_info);
	printf("\nJob complete.\n");	
	return;
}

/*producer thread execution start.
  use empty semaphore to determine ability to produce.
  waits for buffmutex and then produces value in circular array.
*/
DWORD WINAPI produce(LPVOID lpParameter){
	thread_data td = *(thread_data*)lpParameter;
	int i=0;
	while(i<td.max_items){
	WaitForSingleObject(empty,INFINITE);
	WaitForSingleObject(buffmutex,INFINITE);
	coconuts[prodplace%16]=td.t_id * td.max_items + i;
	prodplace++;
	ReleaseSemaphore(full,1,NULL);
	ReleaseMutex(buffmutex);
	i++;
	}
	return 0;
}

//Consumer execution function.
DWORD WINAPI consume(LPVOID lpParameter){
	thread_data td = *(thread_data*)lpParameter;
	int i=0;
	while(i<td.max_items){
	WaitForSingleObject(full,INFINITE);
	WaitForSingleObject(buffmutex,INFINITE);
	printf("%i\n",coconuts[consumeplace%16]);
	consumeplace++;
	ReleaseSemaphore(empty,1,NULL);
	ReleaseMutex(buffmutex);
	i++;
	}
	return 0;
}

