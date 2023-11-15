#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *ptr;// file pointer, this will point to the file,
    FILE *ptr2; // ptr2 for output file
    char buff[100];

    for(int i = 0 ; i < 100;i++)
    {
        buff[i] = '\0'; // initialize buff with null
    }
       
    ptr=fopen("input.txt","r"); // open input file in read mode
    ptr2 = fopen("output2.txt", "w+"); // open output file in write mode
    
    while(fscanf(ptr, "%s", buff)==1)
    {
        int i = 0;
        int check = 1;
        while(buff[i] != '\0')
        {
            if(buff[i] > 'A' && buff[i] < 'z')
            {
                check = 0;
            }
            i++;
        }
        if(check == 1)
        {
            fprintf(ptr2, "%s\n", buff);
        }
    }
    fclose(ptr);
    fclose(ptr2);
    return 0;
}