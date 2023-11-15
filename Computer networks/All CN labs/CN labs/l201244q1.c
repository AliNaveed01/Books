// L201244 Naveed ALi Computer Network Lab 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *ptr;  // file pointer which will point to the file
	char buffer[255];// character array which is used to store the data which is read from the file
	ptr = fopen("input.txt","r"); // open the file in read mode
	
	int i =0;
	for(i=0;i<2;i++){
		fgets(buffer,255,(FILE*)ptr);
		printf("%s", buffer);	
	
	}
	//closes the file
	fclose(ptr);
}

