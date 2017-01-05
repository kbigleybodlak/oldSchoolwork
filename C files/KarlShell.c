// CSC 415 
// HW3 Win32 
 
 #include <stdio.h> 
 #include <windows.h> 
 #include <string.h> 
 

 #define BUFFERSIZE 1024 
 
 int main() { 
     int exit = 0; 
     char rawInput[BUFFERSIZE]; 
     char* commandFull = NULL; 
     char* nextToken = NULL; 
     int childID = 0; 
     int status = 0; 
 
 
     STARTUPINFO si; 
     PROCESS_INFORMATION pi; 
 
 
     ZeroMemory( &si, sizeof(si) ); 
     si.cb = sizeof(si); 
     ZeroMemory( &pi, sizeof(pi) ); 
     // Execution loop 
     while(1) { 
         printf("Myshell> "); 
         // Get user input 
         fgets(rawInput, BUFFERSIZE, stdin); 
         commandFull = strtok_s(rawInput, "\n", &nextToken); 
         // Interperet input 
         // `exit` command will quit the shell 
         if (strcmp(commandFull, "exit") == 0) { 
             return 0; 
         } 
         // Start the other process 
         if (!CreateProcess(NULL, commandFull, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) { 
             printf("Error creating new process\n"); 
         } 
         else { 
             // Wait for child process to close 
             WaitForSingleObject(pi.hProcess, INFINITE); 
         } 
     } 
     return 0; 
 }

