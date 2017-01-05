
#include<cstdlib>

/*
	-Write a copy program similar to cp in Bash.  
	-two commandline arguments. 
-It should then try to open the file named by the first command-line argument. 
-If successful, it should try to create a file with the name given in the second command-line argument, but
without clobbering (deleting) any existing file by that name. 
-If again successful, it should loop through the contents of the first file, 
writing them to the second file. 
-Finally, it should close both files and print out the total number of bytes copied.
*/
/*OpenFile, CreateFile, ReadFile,WriteFile, CloseFile
	Your code should use a buffer size of 1024 bytes
	Test each version of your program with both a binary file and a text file and both a file under
	1 KB and one over 1 KB.
*/
int main (int argcnt,char *argvec[])
{
	if(OpenFile(argvec[1])
	
}
