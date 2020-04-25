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
  FILE *fp = fopen("testcase.txt", "r");

  if(fp == NULL)
  {
    perror("Error while opening the file!\n");
    exit(EXIT_FAILURE);
  }

  while( ( fgets(data, 500, fp))) //read until we reach end of line 
  {
      fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges);
      printf("Array size: %d x %d with %d edges\n",array_size,array_size,total_edges);
      break;
  }

  int matrix[array_size][array_size];
  for(int i=0; i<array_size; i++)
  {
    for(int j=0; j<array_size; j++)
    {
      matrix[i][j]=0;
    }
  }


  while( ( fgets(data, 500, fp)) !=  NULL ) //until we reach EOF
  {
      fscanf(fp, "%d %d", &temp1, &temp2);
      matrix[temp1 - 1][temp2 - 1] = 1;
      printf("Temp1: %d\tTemp2: %d\n",temp1,temp2);
  }

  printf("Successfull parsing of data! Line count: %d\n",line_count);

  for(int i=0; i<array_size; i++)
  {
    for(int j=0; j<array_size; j++)
    {
      printf("Node %d -> Node %d : %d\n",i+1,j+1,matrix[i][j]);
    }
  }

  fclose(fp);
return 0;
}
