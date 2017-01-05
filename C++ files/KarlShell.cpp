
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#define BUFFER_SIZE 1024

/*make a shell that runs on top of the existing shell.
  its got to take up to three CLArgs.
  and remember when it senses exit, its gotta quit.
*/

void _tmain(int argc, char *argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
	
	if(!CreateProcess(NULL,
		argv[1],
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi)
	)
	{
		printf("CreateProcess failed (%d).\n", GetLastError() );
		return;
	}
	//wait for child to finish.
	WaitForSingleObject( pi.hProcess, INFINITE );
	
	// Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

}

