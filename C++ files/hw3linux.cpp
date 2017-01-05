//Linux Implementation
 #include <stdio.h> 
 #include <unistd.h> 
 #include <string.h> 
 #include <sys/types.h> 
 #include <sys/wait.h> 
 
 #define BUFFERSIZE 1024 
//Create a shell over the Terminal for Linux that accepts up to three args   //other than the filename.
 int main() { 
     char rawInput[BUFFERSIZE]; 
     char* token = NULL; 
     char* input[4];
     const char s[2]=" "; 
     int i = 0; 
     int childID = 0; 
     int status = 0; 
     // Execution loop 
     while(1) { 
     	printf("Myshell> "); 
         // Get user input 
         fgets(rawInput, BUFFERSIZE, stdin);
	 token = strtok(rawInput, "\n"); 
         token = strtok(rawInput, s); 
	//parse input in tokens. Must empty out input array each iteration.
         i = 0; 
	 input[1]=NULL; input[2]=NULL; input[3]=NULL;
         while(token != NULL) { 
             input[i] = token; 
             token = strtok(NULL, s); 
             i++; 
         } 
         // Interperet input. "exit" string will exit the shell. 
         if (strcmp(input[0], "exit") == 0) { 
             return 0; 
         } 
         // Fork the process 
         childID = fork(); 
         // Check whether we are in the child or parent 
         if (childID == 0) { 
         	// Execute child process according to # of args.
	     if(input[3]!=NULL) 
             execlp(input[0], input[0], input[1], input[2], input[3], NULL); 
	     if(input[3]==NULL&&input[2]!=NULL)
             execlp(input[0], input[0], input[1], input[2], NULL);
	     if(input[3]==NULL && input[2]==NULL && input[1]!=NULL)
	     execlp(input[0], input[0], input[1], NULL);
	     if(input[3]==NULL && input[2]==NULL && input[1]==NULL)
	     execlp(input[0], input[0], NULL); 
         } 
         // If in parent, wait for child process to close 
         else if (childID > 0) { 
             wait(&status); 
         } 
         else { 
         	printf("Error creating new process\n"); 
         } 
     } 
     return 0; 
 }

//End Linux implementation.

