#include<stdio.h>

int main()
{
FILE *fp;
char buff[255];
fp = fopen("input.txt", "r");
for(int i = 0; i < 2; i++)
{
fgets(buff, 255, (FILE*)fp);
printf("%s", buff );
}
fclose(fp);

}
