/*
	Karl BIgley-Bodlak
	CSC 415 hw 5
	producer consumer problem with a bounded buffer.
	LINUX VERSION.
	Use full and empty semaphores to keep track of the numbers of full and empty slots available to the consumers and
    producers, respectively.
    consumer threads should consume these items by printing them.
*/
#include <pthread.h> 
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int coconuts[16];

//control for place in circular array to go to next for each producer and consumer.
int prodplace=0;
int consumeplace=0;

//mutex for buffer, then 2 semaphores.
pthread_mutex_t lock;
sem_t full;
sem_t empty;

/*
	t_id is thread id.
	num_items is the number of items to process.
*/
typedef struct
{
	int t_id;
	int max_items;

}thread_data;

void* produce(void* lpParameter);
void* consume(void* lpParameter);
 
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
	pthread_t * producers;
	pthread_t * consumers;
	
	if(argc!=4){
		printf("error:Please enter 3 arguments");
		return;
	}
	
	if(pthread_mutex_init(&lock,NULL) != 0){
  		printf("\nmutex creation error.\n");
  		return;
  	}
  	if(pthread_mutex_init(&lock,NULL) != 0){
  		printf("\nmutex creation error.\n");
  		return;
  	}
	if(sem_init(&full,0,0) != 0 || sem_init(&empty,0,15) != 0) {
  		printf("\nsemaphore creation error.\n");
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
	
	producers = (pthread_t*)malloc(sizeof(pthread_t) * num_producers);
	consumers = (pthread_t*)malloc(sizeof(pthread_t) * num_consumers);

	//spawn producers
	for(i = 0; i<num_producers;i++){
		producer_info[i].max_items=num_to_produce;
		producer_info[i].t_id=i;
		pthread_create(&producers[i],NULL,&produce,&producer_info[i]);
	}
	
	//spawn consumers.
	for(i = 0; i<num_consumers;i++){
		consumer_info[i].max_items=num_to_consume;
		consumer_info[i].t_id=i;
		pthread_create(&consumers[i],NULL,&consume,&consumer_info[i]);
	}
	//wait for thread resolutions. waitng for only the last thread created works fine.
	for(i=0;i<num_producers;i++)
		pthread_join(producers[i],NULL);
	for(i=0;i<num_consumers;i++)
		pthread_join(consumers[i],NULL);
	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&lock);
	printf("\nJob complete.\n");	
	return;
}

/*producer thread execution start.
  use empty semaphore to determine ability to produce.
  waits for buffmutex and then produces value in circular array.
*/
void* produce(void* lpParameter){
	thread_data td = *(thread_data*)lpParameter;
	int i=0;
	while(i<td.max_items){
	sem_wait(&empty);
	pthread_mutex_lock(&lock);
	coconuts[prodplace%16]=td.t_id * td.max_items + i;
	prodplace++;
	sem_post(&full);
	pthread_mutex_unlock(&lock);
	i++;
	}
	pthread_exit(NULL);
}

//Consumer execution function.
void* consume(void* lpParameter){
	thread_data td = *(thread_data*)lpParameter;
	int i=0;
	while(i<td.max_items){
	sem_wait(&full);
	pthread_mutex_lock(&lock);
	printf("%i\n",coconuts[consumeplace%16]);
	consumeplace++;
	sem_post(&empty);
	pthread_mutex_unlock(&lock);
	i++;
	}
	pthread_exit(NULL);
}

