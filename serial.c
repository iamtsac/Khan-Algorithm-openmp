#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node_info{
int id;
int out_edges;
int in_edges;
}node;


int main(void)
{
  int array_size, total_edges, temp1, temp2, line_count = 0;
  char data[500], temp;
  FILE *fp = fopen("data.txt", "r");
  if(fp == NULL)
  {
    perror("Error while opening the file!\n");
    exit(EXIT_FAILURE);
  }

  while( ( fgets(data, 500, fp)) !=  NULL ) //until we reach EOF
  {

    if( line_count == 0 ) //do this if 1st line
    {
      fscanf(fp, "%c %d %d", &temp, &array_size, &total_edges);
      printf("Array size: %d\n",array_size);
    }
    else //do this for all other lines
    {
      fscanf(fp, "%d %d", &temp1, &temp2);
      printf("Temp1: %d\tTemp2: %d\n",temp1,temp2);
    }
    line_count++;
  }

  printf("Successfull parsing of data! Line count: %d\n",line_count);

  fclose(fp);
return 0;
}
