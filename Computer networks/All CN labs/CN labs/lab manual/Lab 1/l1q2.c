#include<stdio.h>

int main()
{
FILE *fp;// file pointer, this will point to the file, FILE is a data type which is defined in stdio.h
char buff[255]; //
fp = fopen("input.txt", "r");
FILE * fp1; 
fp1 = fopen("output.txt","w+");
char buff2[100];
int k = 0; // k will be used 1st time to store the data in buff2
for(int i = 0; i < 2; i++) //
{
fgets(buff, 255, (FILE*)fp);
int j = 0; // 
while(buff[j] != '\0')
{
if(buff[j] >= '0' && buff[j] <= '9')
{
buff2[k] = buff[j];
k++;
}
j++;
}
}
fputs(buff2,fp1);
fclose(fp);
fclose(fp1);

}
