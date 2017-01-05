/* CSC 415 
* HW3 Linux
Only need to support ONE operator per command.
*/
 
 #include <stdio.h> 
 #include <unistd.h>
 #include <sys/types.h>
 #include <string.h> 
 #include <fcntl.h>
 #include <sys/stat.h>
//0 is stdin, 1 is stdout, 2 is std err
 #define BUFFERSIZE 1024 
 
 int main() { 
      int i=0;
     int errorCode = 0;
     char rawInput[BUFFERSIZE]; //the raw input to the command line
     char* firstInput[10]; //the parsed first command without the additional re-direction ops.
     char* secondInput[10];//the parsed second command without redirection ops.

     char* commandFull = NULL; //token holder for each expression.
     char* nextCommand = NULL; //placeholder for where in strtok_s the pointer is for commandFull
     char* parsedCommand = NULL; //the token older for the input with " " delim.
     char* nextToken = NULL; //placeholder for where in strtok_s the pointer is for parsedCommand
     char* firstCommand = NULL;
     char* secondCommand = NULL;
     int childID = 0; 
     int status = 0; 
	 int asyncFlag = 0;
 	 int pipeFlag = 0;
 	 int firstInputIndex=0;
 	 int secondInputIndex=0;
 	 int	pipeID[2]; //the pipe array.
 	 int switchFlag= 0;
 	 int pid1, pid2;

	 int ReadHandle, WriteHandle;
	 
	
     // Execution loop 
     while(1) { 
         printf("KarlShell> "); 
         // Get user input ended by \n, if it ends in &, set a flag so that parent will not wait.
         fgets(rawInput, BUFFERSIZE, stdin); 
         commandFull = (char*)strtok_r(rawInput, "\n", &nextCommand);
		 parsedCommand = strtok_r(rawInput, " \n", &nextToken);
		 if(parsedCommand==NULL)
		 	errorCode=1;
         // Interperet input 
         //need to keep original command seperate from redirection operators.
         



         //detect if  a pipe is in the input.
         //detect if a redirection operator is in the input
         
         
         // `exit` command will quit the shell 
         if (strcmp(parsedCommand, "exit") == 0) {
		 	
             return 0; 
         } 
         
         
        while(parsedCommand !=NULL && errorCode==0){
         		
        	if(strcmp(parsedCommand,"&")==0)
         	{
         		asyncFlag =1;
         		parsedCommand = strtok_r(NULL, " \n",&nextToken);
         		continue;
         	}
         	//piping output of first command to the next command, ASSERT: no other redirection.
         	if(strcmp(parsedCommand,"|")==0)
       	 	{
				if ((status = pipe(pipeID)) == -1) { /* error exit - bad pipe */
					printf("Bad pipe");
					errorCode=1;
					break;
				}
parsedCommand = strtok_r(NULL," \n",&nextToken);
       	 		
				while(parsedCommand!=NULL)
				{
						
					secondInput[secondInputIndex]=parsedCommand;
					secondInputIndex++;
parsedCommand = strtok_r(NULL," \n",&nextToken);
				}
				switchFlag=1;
				break;


	       	}

       		//NEAT TRICK: ORDER DOES NOT MATTER WHEN PUTTING THESE IN A COMMAND.
       		//ONLY RIGHT-MOST REDIRECTION COUNTS
       		//rediercting stdout to a file, no piping out
			if(strcmp(parsedCommand,">")==0)
         	{
         		//gets the thing after the >
         		parsedCommand = strtok_r(NULL, " \n", &nextToken);
         		if(parsedCommand!=NULL)
         		{

         			WriteHandle = open(parsedCommand, O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU);

         			if(WriteHandle==-1)
         			{
         				printf("Error: could not open output file.\n");
         				errorCode = 1;
         				break;
         			}
         			switchFlag=2;
         			//continues reading 
         			parsedCommand = strtok_r(NULL, " \n", &nextToken);
         			continue;
         		}else{
         			printf("error: need new direction after > operator.\n");
         			errorCode = 1;
         			break;
         		}
         	}
         		
         	//redirecting stdin from a file
         	if(strcmp(parsedCommand,"<")==0)
         	{
        		parsedCommand = strtok_r(NULL, " \n", &nextToken);
         		if(parsedCommand!=NULL)
         		{
         			ReadHandle = open(parsedCommand, O_RDONLY );
         			if(ReadHandle == -1)
         			{
         				printf("Error: could not open input file.\n");
         				errorCode = 1;
         				break;
         			}
         			switchFlag=3;
         			//continues reading 
         			parsedCommand = strtok_r(NULL, " \n", &nextToken);
         			continue;
         		}else{
         			printf("error: need new direction after < operator.\n");
         			errorCode = 1;
         			break;
         		}
           	}
         		//redirecting and appending stdout to a file. no piping out
         	if(strcmp(parsedCommand,">>") == 0)
         	{
        		parsedCommand = strtok_r(NULL, " \n", &nextToken);
         		if(parsedCommand!=NULL)
         		{
         			WriteHandle = open(parsedCommand, O_WRONLY | O_APPEND | O_CREAT,S_IRWXU);
         			if(WriteHandle == -1)
         			{
         				printf("Error: could not open output file.\n");
         				errorCode = 1;
         				break;
         			}
         			switchFlag = 4;
         			//continues reading 
         			parsedCommand = strtok_r(NULL, " \n", &nextToken);
         			continue;
         		}else{
         			printf("error: need new direction after >> operator.\n");
         			errorCode = 1;
         			break;
          		}
        	}
        		//redirecting stderr to a file.
        	if(strcmp(parsedCommand, "2>" )==0)
        	{
        		parsedCommand = strtok_r(NULL, " \n", &nextToken);
        		if(parsedCommand!=NULL)
        		{
         			WriteHandle = open(parsedCommand, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
         			if(WriteHandle == -1)
         			{
         				printf("Error: could not open output file.\n");
         				errorCode = 1;
         				break;
       				}
         			switchFlag=5;
         			//continues reading 
         			parsedCommand = strtok_r(NULL, " \n", &nextToken);
         			continue;
         		}else{
         			printf("error: need new direction after 2> operator.\n");
         			errorCode =1;
         			break;
          		}
       		}
        		//redirecting stderr and appending it to a file.
         	if(strcmp(parsedCommand,"2>>")==0)
         	{
        		parsedCommand = strtok_r(NULL, " \n", &nextToken);
         		if(parsedCommand != NULL)
         		{
         			WriteHandle = open(parsedCommand, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
         			if(WriteHandle == -1)
         			{
         				printf("Error: could not open error output file.\n");
         				errorCode = 1;
         				break;
         			}
         			switchFlag=6;
         			//continues reading 
         			parsedCommand = strtok_r(NULL, " \n", &nextToken);
         			continue;
         		 }else{
         			printf("error: need new direction after 2>> operator.\n");
         			errorCode = 1;
         			break;
         			
         		}
         	}
         	//Once we have a redirection operator in the command, you can just add the rest of the command, and begin process forking, 
			 //using the local variable as guidance on what will be changed in the child.
         	if(parsedCommand != NULL && errorCode !=1)
         	{
         		if(firstInputIndex>9)
         		{
         			break;
         		}
          		firstInput[firstInputIndex] = parsedCommand;
         		
         		firstInputIndex++;

         		parsedCommand = strtok_r(NULL, " \n", &nextToken);
         	}
        }
         
     	if(errorCode == 1){
         	errorCode=0;
         	memset(&firstInput[0], 0, sizeof(firstInput));
		memset(&secondInput[0], 0, sizeof(secondInput));
		firstInputIndex=0;
		secondInputIndex=0;
         	continue;
        }

        if(switchFlag == 1)
        {
			if ((pid2 = fork()) == -1)
			{
				fprintf(stderr, "Create Process 2 Failed\n");
				continue;
			}
			//redirecting input to pipe.
			if(pid2==0)
			{
				close (0);
				dup (pipeID[0]);
				close (pipeID[0]);
				close(pipeID[1]);
			
			//executing second process based on number of args.
				switch(secondInputIndex) 
				{
					case 0:
						break;
					case 1: 
						if(!execlp(secondInput[0],secondInput[0],NULL))
printf("create Process failed");
						break;
					case 2:
						execlp(secondInput[0],secondInput[0],secondInput[1],NULL);
						break;
					case 3:
						execlp(secondInput[0],secondInput[0],secondInput[1],secondInput[2],NULL);
						break;
					case 4:
						execlp(secondInput[0],secondInput[0],secondInput[1],secondInput[2],secondInput[3],NULL);
						break;
					case 5:
						execlp(secondInput[0],secondInput[0],secondInput[1],secondInput[2],secondInput[3],secondInput[4],NULL);
						break;
					case 6:
						execlp(secondInput[0],secondInput[0],secondInput[1],secondInput[2],secondInput[3],secondInput[4],secondInput[5],NULL);
						break;
					case 7:
						execlp(secondInput[0],secondInput[0],secondInput[1],secondInput[2],secondInput[3],secondInput[4],secondInput[5],secondInput[6],NULL);
						break;
					case 8:
						execlp(secondInput[0],secondInput[0],secondInput[1],secondInput[2],secondInput[3],secondInput[4],secondInput[5],secondInput[6],secondInput[7],NULL);
						break;
					case 9:
						execlp(secondInput[0],secondInput[0],secondInput[1],secondInput[2],secondInput[3],secondInput[4],secondInput[5],secondInput[6],secondInput[7],secondInput[8],NULL);
						break;
					case 10:
						execlp(secondInput[0],secondInput[0],secondInput[1],secondInput[2],secondInput[3],secondInput[4],secondInput[5],secondInput[6],secondInput[7],secondInput[8],secondInput[9],NULL);
						break;
					default: 
						printf("too many args for shell to process\n"); 
						break;
				}
			/* error exit - exec returned */
				perror("Execl returned");
			}
		}
		//fork first process.
		if ((pid1 = fork()) == -1)
		{
			fprintf(stderr, "Create Process 1 Failed\n");
			
			continue;
		}
		//do redirection stuff for forked process, then execute it.
		if(pid1==0)
		{
		
			switch(switchFlag)
			{
				//case of no change.
				case 0:
					break;
			// | pipe
				case 1:
					close (1);
					dup(pipeID[1]);
					close(pipeID[0]);
					close(pipeID[1]);
					break;
				// > redirection
				case 2:
					dup2(WriteHandle,1);	
					close(WriteHandle);
					break;
				// < redirection.
				case 3:
					dup2(ReadHandle,0);
					close(ReadHandle);
					break;
				// >> redirection
				case 4:
					dup2(WriteHandle,1);
					close(WriteHandle);
					break;
					
				// 2> redirection
				case 5:
					dup2(WriteHandle,2);
					close(WriteHandle);
					break;
						
				//2>> redirection.
				case 6:
					dup2(WriteHandle,2);
					close(WriteHandle);
					break;
					
				//here for lols.
				default:
					break;
			 
			}
			//execution part.
			switch(firstInputIndex)
			{
				//nothing was entered into the shell.
				case 0:
					break;
				case 1:
					if(!execlp(firstInput[0],firstInput[0],NULL))
printf("execution failed\n");
					break;
				case 2:
					execlp(firstInput[0],firstInput[0],firstInput[1],NULL);
					break;
				case 3:
					execlp(firstInput[0],firstInput[0],firstInput[1],firstInput[2],NULL);
					break;
				case 4:
					execlp(firstInput[0],firstInput[0],firstInput[1],firstInput[2],firstInput[3],NULL);
					break;
				case 5:
					execlp(firstInput[0],firstInput[0],firstInput[1],firstInput[2],firstInput[3],firstInput[4],NULL);
					break;
				case 6:
					execlp(firstInput[0],firstInput[0],firstInput[1],firstInput[2],firstInput[3],firstInput[4],firstInput[5],NULL);
					break;
				case 7:
					execlp(firstInput[0],firstInput[0],firstInput[1],firstInput[2],firstInput[3],firstInput[4],firstInput[5],firstInput[6],NULL);
					break;
				case 8:
					execlp(firstInput[0],firstInput[0],firstInput[1],firstInput[2],firstInput[3],firstInput[4],firstInput[5],firstInput[6],firstInput[7],NULL);
					break;
				case 9:
					execlp(firstInput[0],firstInput[0],firstInput[1],firstInput[2],firstInput[3],firstInput[4],firstInput[5],firstInput[6],firstInput[7],firstInput[8],NULL);
					break;

				default:
					break;
			}

		}
		if(switchFlag==1)
		{
			close(pipeID[0]);
			close(pipeID[1]);
			wait(pid2,0,0);
			
		}
		if(asyncFlag==0 && errorCode==0)
		{
			wait(pid1,0,0);
			
			
		}else{
			asyncFlag=0;
		}
	


        
         //IDEA:::: SWITCH statement with number of args.
         // Start the other process using commandFull as the string passed to the command line.

            
		
	for( i =0; i<firstInputIndex; i++)
        	memset(&firstInput[0], 0, sizeof(firstInput));
	for(i = 0; i<secondInputIndex; i++)
		memset(&secondInput[0], 0, sizeof(secondInput));
	secondInputIndex=0;
        firstInputIndex=0;
	switchFlag=0;
 	asyncFlag=0;
	errorCode=0;
     } 
     return 0; 
 }
 
/* MCM 615 Lab2 Demo #2
**	See 615 Notes slide #48 for details!
**	Compile/execute under Linux using gcc
**
**	Usage (note that this program is implementing a
**	simple shell pipe:  'ps aux | grep mcm'
**	> ./lab2demo2 ps aux grep mcm
*
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

main(int argc, char *argv[]) {
	int	pid1,pid2;
	int	pipeID[2];
	int	status;

	if ((status = pipe(pipeID)) == -1) { /* error exit - bad pipe *
		perror("Bad pipe");
		exit(-1);
	}
	if ((pid1 = fork()) == -1) {  /* error exit - bad fork *
		perror("Bad fork");
		exit(-1);
	}
	if (pid1 == 0) { /* The first child process */
	/* make sure you start the last process in the pipeline first! *
		printf("The first child is starting: %s %s\n",argv[3],argv[4]);
		close (0);
		dup (pipeID[0]);
		close (pipeID[0]);
		close(pipeID[1]);
		execlp(argv[3],argv[3],argv[4],0); 
		/* error exit - exec returned *
		perror("Execl returned");
		exit(-1);
	}
	/* this is the parent again *
	if ((pid2 = fork()) == -1) { /* error exit - bad fork *
		perror("Bad fork");
		exit(-1);
	}
	if (pid2 == 0) { /* the second child process *
		printf("The second child is starting: %s %s\n",argv[1],argv[2]);
		close (1);
		dup(pipeID[1]);
		close(pipeID[0]);close(pipeID[1]);
		execlp(argv[1],argv[1],argv[2],0); 
		/* error exit - exec returned *
		perror("Execl returned");
		exit(-1);
	}
	/* back to the parent again *
	close(pipeID[0]);
	close(pipeID[1]);
	wait(pid1,0,0);
	wait(pid2,0,0);
	printf("The parent is exiting\n");
}*/
