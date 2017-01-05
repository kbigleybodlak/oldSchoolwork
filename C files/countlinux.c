/* 
 * Karl Bigley-Bodlak 
 * CSC 415 HW4 POSIX
 * purpose: count the ASCII chars in a file using multiple
 * threads in a process. 
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
int counter[NUMTHREADS][128]; 
//buffer for file input.
char buff[BUFFERLENGTH]; 
 
//function prototype.
void *thread_func(void *param); 
 
/* struct for thread information */ 
typedef struct t_info { 
	int partition; //size of partition length.
	int t_id; //thread id.
} t_info; 
 
 
void main(int argc, char* argv[]) { 
	pthread_t threds[NUMTHREADS]; 
    t_info info[NUMTHREADS]; 
    //threadp is size of partitions calculated in main.
    //source is source id.
    //source_length is #bytes read.
 	int source, source_length, threadp, total, i, j;  
 
	//command line args check.
 	if(argc != 2) { 
 		fprintf(stderr, "usage: a.out <ASCII file name>\n"); 
 		return; 
 	} 
	//checking source file validity.
 	source = open(argv[1], O_RDONLY); 
 	if(source == -1) { 
         fprintf(stderr, "could not open source file\n"); 
         return; 
    } 
    /* reading the file into the buffer */ 
    source_length = read(source, buff, BUFFERLENGTH); 
    close(source);  
 
    /* calculating the size of the partitions the threads will work on */ 
    threadp = ceil((double) source_length / (double) NUMTHREADS); 
  
    /* creating and executing the threads */ 
 	for(i = 0; i < NUMTHREADS; i++) { 
 	    info[i].t_id = i; 
        info[i].partition = threadp; 
 		if(pthread_create(&threds[i], NULL, &thread_func, &info[i]) != 0) { 
            fprintf(stderr, "Error creating thread %i\n", i); 
            return; 
        } 
	} 
 
 
    /* waiting for the threads to finish execution */ 
	for(i = 0; i < NUMTHREADS; i++) { 
		pthread_join(threds[i], NULL); 
	} 
 
 
     /* printing out the data */ 
     for(i = 0; i < 128; i++) { 
         total = 0; 
         for(j = 0; j < NUMTHREADS; j++) { 
             total += counter[j][i]; 
         } 
         printf("%i occurrences of ", total); 
         if(i <= 32 || i == 127) 
             printf("%#02x\n", i); 
         else 
             printf("%c\n", i); 
     } 
} 

/* calculates the number of times an ASCII character shows up */ 
void *thread_func(void *param) { 
    int i; 
    t_info* info = (t_info*) param; 
	int location = info->t_id * info->partition; 
    /* location is based on which thread and the size of the chunks so they do not overlap */ 
    char current_char = buff[location]; 
	for(i = 0; i < info->partition && location < BUFFERLENGTH; i++, current_char = buff[location++]) { 
		counter[info->t_id][current_char]++; 
	} 
    pthread_exit(NULL); 
} 

