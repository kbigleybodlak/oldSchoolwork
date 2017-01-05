/* 
 * Karl Bigley-Bodlak 
 * CSC 415 HW4 POSIX
 * purpose: count the ASCII chars in a file using multiple
 * threads in a process. 
 *this version uses a mutex lock to prevent data racing.
 */ 
#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h> 
#include <math.h> 
#include <unistd.h> 

#define NUMTHREADS 4 
#define BUFFERLENGTH 65536 

//what will hold the ASCII char count.
int counter[128]; 
//buffer for file input.
char buff[BUFFERLENGTH]; 
 
pthread_mutex_t lock;
 
void *thread_func(void *param); 
 
/* struct for thread information */ 
typedef struct t_info { 
	int partition; //size of partition length.
	int t_id; //thread id.
} t_info; 
 
/*threadp is size of partitions calculated in main.
  source is source id.
  source_length is #bytes read. 
*/
void main(int argc, char* argv[]) { 
	pthread_t threds[NUMTHREADS]; 
    t_info info[NUMTHREADS]; 
	int source, source_length, threadp, i, j;  
 
	//command line args check.
 	if(argc != 2) { 
 		fprintf(stderr, "error: please enter one filename.\n"); 
 		return; 
 	} 
	//checking source file validity.
 	source = open(argv[1], O_RDONLY); 
 	if(source == -1) { 
         fprintf(stderr, "error: could not open source file\n"); 
         return; 
    } 
    /* reading the file into the buffer */ 
    source_length = read(source, buff, BUFFERLENGTH); 
    close(source);  
 
    /* calculating the size of the partitions the threads will work on */ 
    threadp = ceil((double) source_length / (double) NUMTHREADS); 
  	
  	/* Initializing the mutex lock.*/
  	if(pthread_mutex_init(&lock,null) != 0){
  		printf("\nmutex creation error.\n");
  		return;
  	}
  	
    /* creating and executing the threads */ 
 	for(i = 0; i < NUMTHREADS; i++) { 
 	    info[i].t_id = i; 
        info[i].partition = threadp; 
 		if(pthread_create(&threds[i], NULL, &thread_func, &info[i]) != 0) { 
            fprintf(stderr, "Error creating thread %i\n", i); 
            return; 
        } 
	} 
 
 
    /* waiting for the threads to finish */ 
	for(i = 0; i < NUMTHREADS; i++) { 
		pthread_join(threds[i], NULL); 
	} 
 
 
     /* printing data */ 
     for(i = 0; i < 128; i++) {  
         printf("%i occurrences of ", counter[i]); 
         if(i <= 32 || i == 127) 
             printf("%#02x\n", i); 
         else 
             printf("%c\n", i); 
     } 
} 

/* calculates the number of times an ASCII character shows up */ 
void *thread_func(void *param) { 

	pthread_mutex_lock(&lock);
    int i; 
    t_info* info = (t_info*) param; 
	int location = info->t_id * info->partition; 
    /* location is based on which thread and the size of the chunks so they do not overlap */ 
    char current_char = buff[location]; 
	for(i = 0; i < info->partition && location < BUFFERLENGTH; i++, current_char = buff[location++]) { 
		counter[current_char]++; 
	} 
	pthread_mutex_unlock(&lock);
    pthread_exit(NULL); 
} 

