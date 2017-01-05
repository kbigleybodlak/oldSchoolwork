#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//first file name gets copied to second file name.
void main (int argc, char *argv[])
{
	char str[1024]; //buffer
	/*nbytesread/written are where Read and Write operations 
	  will store number of bytes written/read.
	  totalbytes is the value of the total bytes transferred.
	*/
	int nbytesread, nbyteswritten, totalbytes=0;
	//finput is input file descriptor, foutuput for output file descriptor.
	int finput, foutput;
	//checks number of arguments.
	if(argc!=3)
	{
	    printf("error:needs two arguments.\n");
	    return;
	}
	
	//open() tries to open source.
	finput=open(argv[1],O_RDONLY);
	if(finput>0){
	    /*creating the file and aborting if destination file already 
	      exists. 
	    */
	    foutput=open(argv[2],O_RDWR|O_CREAT);
	    if(foutput>0)
	    {
	        //Reads 1KB at a time and writes it into output.
	        //If more than 1KB to copy, it loops the read/write.
	        do{
	            nbytesread=read(finput,str,1024);
	            totalbytes+=write(foutput,str,nbytesread);
	        }while(nbytesread>0);
	        printf("%d bytes copied.\n",totalbytes);
	        close(finput);
	        close(foutput);
	        return;
	    } 	
	    //If source file cannot be read.
	    printf("error:destination file already exists.\n");
	    close(finput);
	    return;
		
	//destination file already exists error.
	}	
	printf("error:The source file could not be read.\n");
	return;
}
