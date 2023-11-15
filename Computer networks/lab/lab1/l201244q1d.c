#include <stdio.h>

int main()
{
    // pointers to files
    FILE *ptr;
    FILE *ptr2;

    // buffers to store strings
    char buff[100];
    char buff2[100];
    int i = 0;
    
    // initialize buff with null
    for (i=0; i < 100; i++)
    {
        buff[i] = '\0';
    }
    for (i=0; i < 100; i++)
    {
        buff2[i] = '\0';
    }

    //now open the files

    ptr2 = fopen("output3.txt", "w+");
    ptr = fopen("input.txt", "r");

    // read from input file and write to output file
    while(fscanf(ptr, "%s", buff)==1)
    {
        int i = 0; 
        int check = 1; // check if the string contains vowels
        while(buff[i] != '\0')
        {
            if(buff[i] == 'A' || buff[i] == 'E' || buff[i] == 'I' || buff[i] == 'O' || buff[i] == 'U' || buff[i] == 'a' || buff[i] == 'e' || buff[i] == 'i' || buff[i] == 'o' || buff[i] == 'u')
            {
                check = 0;
            }
            i++;
        }
        if (check == 0)
        {
            // we will invert the string and write it to the output file
            int j = 0;
            int len = 0;
            while(buff[len] != '\0')
            {
                len++;
            }
            // now we have the length of the string
            // we will invert the string
            for (j = 0; j < len; j++)
            {
                buff2[j] = buff[len - j - 1];
            }
            fprintf(ptr2, "%s\n", buff2);

        }

    }

    fclose(ptr);
    fclose(ptr2);
    return 0;
}