// l201244 Naveed Ali Computer Networks Lab q1 part b
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	FILE *ptr;// pointer to the file
	char buffer[255];// character array for storing data in the 
	ptr = fopen("input.txt","r");

	// for writing in the file
	FILE *ptr2;
	char buffer2[255];
	ptr2 = fopen("output.txt","w+");
	
	int index = 0; //index of buffer 2
	int i;
	for (i=0;i<2;i++)
	{
		fgets(buffer,255,(FILE*)ptr);
		int count; // for traversing into the buffer
		while(buffer[count] != '\0')
		{
			if(buffer[count]>= '0' && buffer[count]<= '9')
			{
				buffer2[index] = buffer[count];
				index++; // will add only the numbers	
			}	
		count++;
	
		}
	}
	fputs(buffer2,ptr2);
	fclose(ptr);
	fclose(ptr2);
}
