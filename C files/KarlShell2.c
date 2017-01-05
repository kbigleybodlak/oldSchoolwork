/* CSC 415 
* HW3 Win32 
Only need to support ONE operator per command.
*/
 
 #include <stdio.h> 
 #include <windows.h> 
 #include <string.h> 
 

 #define BUFFERSIZE 1024 
 
 int main() { 
     int exit = 0; 
     int errorCode = 0;
     char rawInput[BUFFERSIZE]; //the raw input to the command line
     char firstInput[BUFFERSIZE]=""; //the parsed first command without the additional re-direction ops.
     char* secondInput = NULL;//the parsed second command without redirection ops.
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
 	 int inputIndex=0;
 	 
     STARTUPINFO si; 
     PROCESS_INFORMATION pi; 
 	 STARTUPINFO si2;
	 PROCESS_INFORMATION pi2;
	 HANDLE ReadHandle, WriteHandle;
	 SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	


 
     ZeroMemory( &si, sizeof(si) ); 
     si.cb = sizeof(si); 
     ZeroMemory( &pi, sizeof(pi) ); 
     
 	 ZeroMemory(&si2, sizeof(si2));
 	 si2.cb = sizeof(si2);
 	 ZeroMemory(&pi2, sizeof (pi2));


     // Execution loop 
     while(1) { 
         printf("KarlShell> "); 
         // Get user input ended by \n, if it ends in &, set a flag so that parent will not wait.
         fgets(rawInput, BUFFERSIZE, stdin); 
         commandFull = strtok_s(rawInput, "\n", &nextCommand);
		 parsedCommand = strtok_s(rawInput, " \n", &nextToken);
		 if(parsedCommand==NULL)
		 	errorCode=1;
         // Interperet input 
         //need to keep original command seperate from redirection operators.
         
	 	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	 	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	 	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	 	si.dwFlags = STARTF_USESTDHANDLES;
	 	
	 	si2.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	 	si2.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	 	si2.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	 	si2.dwFlags = STARTF_USESTDHANDLES;


         //detect if  a pipe is in the input.
         //detect if a redirection operator is in the input
         
         
         // `exit` command will quit the shell 
         if (strcmp(parsedCommand, "exit") == 0) {
		 	 CloseHandle(pi.hProcess);
			 CloseHandle(pi.hThread);
			 CloseHandle(pi2.hProcess);
			 CloseHandle(pi2.hThread); 
             return 0; 
         } 
         
         
        while(parsedCommand !=NULL && errorCode==0){
         		
        	if(strcmp(parsedCommand,"&")==0)
         	{
         		asyncFlag =1;
         		parsedCommand = strtok_s(NULL, " \n",&nextToken);
         		continue;
         	}
         	//piping output of first command to the next command, ASSERT: no other redirection.
         	if(strcmp(parsedCommand,"|")==0)
       	 	{
			if (!CreatePipe(&ReadHandle, &WriteHandle, &sa, 0))
			{
					fprintf(stdout, "Create Pipe Failed\n");
		
			}
       	 		si.hStdInput=ReadHandle;
				si2.hStdOutput=WriteHandle;

				parsedCommand = strtok_s(NULL,"\n",&nextToken);	
				secondInput=parsedCommand;
				pipeFlag=1;
				break;


	       	}

       		//NEAT TRICK: ORDER DOES NOT MATTER WHEN PUTTING THESE IN A COMMAND.
       		//ONLY RIGHT-MOST REDIRECTION COUNTS
       		//rediercting stdout to a file, no piping out
			if(strcmp(parsedCommand,">")==0)
         	{
         		//gets the thing after the >
         		parsedCommand = strtok_s(NULL, " \n", &nextToken);
         		if(parsedCommand!=NULL)
         		{
         			WriteHandle = CreateFile(parsedCommand, GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,&sa,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
         			if(WriteHandle==INVALID_HANDLE_VALUE)
         			{
         				perror("Error: could not open output file.\n");
         				errorCode = 1;
         				break;
         			}
         			si.hStdOutput = WriteHandle;
         			//continues reading 
         			parsedCommand = strtok_s(NULL, " \n", &nextToken);
         			continue;
         		}else{
         			perror("error: need new direction after > operator.\n");
         			errorCode =1;
         			break;
         		}
         	}
         		
         	//redirecting stdin from a file
         	if(strcmp(parsedCommand,"<")==0)
         	{
        		parsedCommand = strtok_s(NULL, " \n", &nextToken);
         		if(parsedCommand!=NULL)
         		{
         			ReadHandle = CreateFile(parsedCommand, GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,&sa,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
         			if(ReadHandle==INVALID_HANDLE_VALUE)
         			{
         				perror("Error: could not open input file.\n");
         				errorCode = 1;
         				break;
         			}
         			si.hStdInput = ReadHandle;
         			//continues reading 
         			parsedCommand = strtok_s(NULL, " \n", &nextToken);
         			continue;
         		}else{
         			printf("error: need new direction after < operator.\n");
         			errorCode =1;
         			break;
         		}
           	}
         		//redirecting and appending stdout to a file. no piping out
         	if(strcmp(parsedCommand,">>")==0)
         	{
        		parsedCommand = strtok_s(NULL, " \n", &nextToken);
         		if(parsedCommand!=NULL)
         		{
         			WriteHandle = CreateFile(parsedCommand, FILE_APPEND_DATA,FILE_SHARE_READ|FILE_SHARE_WRITE,&sa,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
         			if(WriteHandle==INVALID_HANDLE_VALUE)
         			{
         				printf("Error: could not open output file.\n");
         				errorCode = 1;
         				break;
         			}
         			si.hStdOutput = WriteHandle;
         			//continues reading 
         			parsedCommand = strtok_s(NULL, " \n", &nextToken);
         			continue;
         		}else{
         			printf("error: need new direction after >> operator.\n");
         			errorCode =1;
         			break;
          		}
        	}
        		//redirecting stderr to a file.
        	if(strcmp(parsedCommand,"2>")==0)
        	{
        		parsedCommand = strtok_s(NULL, " \n", &nextToken);
        		if(parsedCommand!=NULL)
        		{
         			WriteHandle = CreateFile(parsedCommand, GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,&sa,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
         			if(WriteHandle==INVALID_HANDLE_VALUE)
         			{
         				printf("Error: could not open output file.\n");
         				errorCode = 1;
         				break;
       				}
         			si.hStdError = WriteHandle;
         			//continues reading 
         			parsedCommand = strtok_s(NULL, " \n", &nextToken);
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
        		parsedCommand = strtok_s(NULL, " \n", &nextToken);
         		if(parsedCommand!=NULL)
         		{
         			WriteHandle = CreateFile(parsedCommand, FILE_APPEND_DATA,FILE_SHARE_READ|FILE_SHARE_WRITE,&sa,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
         			if(WriteHandle==INVALID_HANDLE_VALUE)
         			{
         				printf("Error: could not open error output file.\n");
         				errorCode = 1;
         				break;
         			}
         			si.hStdError = WriteHandle;
         			//continues reading 
         			parsedCommand = strtok_s(NULL, " \n", &nextToken);
         			continue;
         		 }else{
         			printf("error: need new direction after 2>> operator.\n");
         			errorCode =1;
         			break;
         			
         		}
         	}
         	if(parsedCommand!=NULL)
         	{
         		if(strlen(firstInput)==0)
         			strcpy(firstInput,parsedCommand);
         		else
         			strcat(firstInput,parsedCommand);
         		strcat(firstInput," ");
         		parsedCommand = strtok_s(NULL, " \n", &nextToken);
         	}
        }
         
     	if(errorCode==1){
         	errorCode=0;
         	memset(&firstInput[0], 0, sizeof(firstInput));
         	continue;
        }

         //si reads, si2 writes
        if(pipeFlag==1)
        {
			if (!CreateProcess(NULL, secondInput,
				NULL,
				NULL,
				TRUE,
				0,
				NULL,
				NULL,
				&si,
				&pi))
			{
				fprintf(stderr, "Create Process 1 Failed\n");
				pipeFlag=0;
				continue;
			}
			if (!CreateProcess(NULL, firstInput,
				NULL,
				NULL,
				TRUE,
				0,
				NULL,
				NULL,
				&si2,
				&pi2))
			{
				fprintf(stderr, "Create Process 2 Failed\n");
				pipeFlag=0;
				continue;
			}
			
			WaitForSingleObject(pi.hProcess, INFINITE);
			printf ("parent:Child two Completed\n");
			
			
			WaitForSingleObject(pi2.hProcess, INFINITE);
			printf ("parent:Child one Completed\n");


			CloseHandle(WriteHandle);
			CloseHandle(ReadHandle);
			pipeFlag=0;

        }
         
         // Start the other process using commandFull as the string passed to the command line.
        else if (!CreateProcess(NULL, firstInput, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) { 
             printf("Error creating new process\n"); 
             errorCode=1;
        } 
        if(asyncFlag==0 && errorCode==0){ 
         //BUT WHAT IF, we start a new command before the first one is finished?
         //would it still use si's stuff or alter it in its process?
         //it shouldn't because it only references si and pi once for the data.
             // Wait for child process to close. if asyncFlag is set, this does not happen. 
             WaitForSingleObject(pi.hProcess, INFINITE); 
            
			 CloseHandle(ReadHandle);
			 CloseHandle(WriteHandle);
        }
		
	 	memset(&firstInput[0], 0, sizeof(firstInput));
		errorCode=0;
	 	asyncFlag=0;
     } 
     return 0; 
 }
 
/* int piping(VOID)
{

STARTUPINFO si;
PROCESS_INFORMATION pi;
STARTUPINFO si2;
PROCESS_INFORMATION pi2;
HANDLE ReadHandle, WriteHandle;
SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};


	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof (pi));
	ZeroMemory(&si2, sizeof(si2));
	si2.cb = sizeof(si2);
	ZeroMemory(&pi2, sizeof (pi2));

	if (!CreatePipe(&ReadHandle, &WriteHandle, &sa, 0)){
		fprintf(stderr, "Create Pipe Failed\n");
		return 1;
	}

	GetStartupInfo(&si);
	GetStartupInfo(&si2);


	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si.hStdInput = ReadHandle;
	si.dwFlags = STARTF_USESTDHANDLES;
	

	if (!CreateProcess(NULL, "C:\\Users\\mmurphy\\desktop\\client2.exe",
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&si,
		&pi))
	{
		fprintf(stderr, "Create Process 2 Failed\n");
		return -1;
	}

	si2.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si2.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si2.hStdOutput = WriteHandle;
	si2.dwFlags = STARTF_USESTDHANDLES;


	if (!CreateProcess(NULL, "C:\\Users\\mmurphy\\desktop\\client1.exe",
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&si2,
		&pi2))
	{
		fprintf(stderr, "Create Process 1 Failed\n");
		return -1;
	}

	WaitForSingleObject(pi2.hProcess, INFINITE);
	printf ("parent:Child one Completed\n");

	WaitForSingleObject(pi.hProcess, INFINITE);
	printf ("parent:Child two Completed\n");
	

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(pi2.hProcess);
	CloseHandle(pi2.hThread);
}*/

