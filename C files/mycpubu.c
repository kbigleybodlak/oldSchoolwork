#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//first file gets copied to second file name.
void main (int argc, char *argv[])
{
 
	char str[1024]; //buffer
	/*nbytesread/written are where Read and Write operations 
	  will store number of bytes written/read.
	  totalbytes is the value of the total bytes transferred.
	*/
	int nbytesread, nbyteswritten, totalbytes=0;
	finput is input file handle, foutuput for output file handle.
	//HANDLE finput, foutput;

	//checks number of arguments.
	if(argc!=3)
	{
		printf("error:needs two arguments.\n");
		return;
	}
	
	//CreateFile tries to open source.
	finput=CreateFile(argv[1],GENERIC_READ,0,
	NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
(GetLastError()!=ERROR_FILE_NOT_FOUND)
	if((finput=open(argv[1],)<1)
	{
		/*creating the file and aborting if destination file already 
		  exists 
		*/
		foutput=CreateFile(argv[2],GENERIC_WRITE,0,
		NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
		if(GetLastError()!=ERROR_FILE_EXISTS)
		{
			//Reads 1KB at a time and writes it into output.
			//If more than 1KB to copy, it loops the read/write.
			while(nbytesread=Read(finput,str,1024))
			totalbytes+=Write(argv[2],str,nbytesread);
			
			printf("%d bytes copied.\n",totalbytes);
			close(finput);
			close(foutput);
			return;
		} 	
		//If source file cannot be read.
		printf("error:destination file already exists.");
		close(finput);
		return;
		
	//destination file already exists error.
	}	
	printf("error:The source file could not be read.");
	return;
}