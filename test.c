
#include <stdio.h>
#include <stdlib.h>

int main() {

int lines;
int columns;
char ch;

FILE *fp;
char buff[255];


fp = fopen("testcase.txt","r");

if(!fp){
	printf("Something wrong");
	exit(1);
}

char data[100];
int i =0,j=0;;
int linesColumns[10]; 
while((ch = fgetc(fp)) != '\n'){
	if(ch == ' '){
		linesColumns[j] = atoi(data);
		i=0;
		j++;
		data[0]= '\0';}
	else{
		data[i] = ch;
		i++;}
}
for(int i=0; i<2; i++)
 printf("%d",linesColumns[i]);
 
  fclose(fp);
return 0;
}
