#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

int array_size, total_edges;

struct node_info
{
  int id;
  int in_edges;
};

double get_time(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + 1e-6 * tv.tv_usec;
}

int* Kahn_Algorithm(int *L,  struct node_info nodes[array_size], bool *matrix);

/*
███    ███  █████  ██ ███    ██
████  ████ ██   ██ ██ ████   ██
██ ████ ██ ███████ ██ ██ ██  ██
██  ██  ██ ██   ██ ██ ██  ██ ██
██      ██ ██   ██ ██ ██   ████
*/
int main(int argc, char **argv)
{
  static char data[50];
  double t1,t2;
  FILE *fp = fopen("dag.txt", "r");

  if(argv[1] == NULL)
  {
    perror("You have to declare the number of threads!\n");
    exit(EXIT_FAILURE);
  }

  if(fp == NULL)
  {
    perror("Error while opening the file!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges);
  printf("Array size: %d x %d with %d edges\n",array_size,array_size,total_edges);
 
  struct node_info *nodes = (struct node_info *)malloc(array_size* sizeof(struct node_info));
  
  for(int i=0; i<array_size; i++)
  {
    nodes[i].id = i+1;
    nodes[i].in_edges = 0;
  }

  bool *matrix = (bool *)malloc(array_size *array_size * sizeof(bool));
  int *L = (int *)malloc(array_size * sizeof(int));
  int *temp1 = (int *)malloc(total_edges * sizeof(int));
  int *temp2 = (int *)malloc(total_edges * sizeof(int));

  for(int i=0; i<total_edges; i++)
  {
    fgets(data, sizeof(data), fp);
    fscanf(fp, "%d %d", &temp1[i],&temp2[i]);
    matrix[(temp1[i] - 1 )* array_size + ( temp2[i] - 1 )] = 1;
    nodes[temp2[i] - 1 ].in_edges++;
  }

  free(temp1); free(temp2);

  t1=get_time();
  L = Kahn_Algorithm(L, nodes, matrix);
  t2=get_time();

  free(nodes); free(marix);

  printf("Successful!\nThe Topological sort is: \n");
  for(int i=0; i<array_size; i++)
  if(i%30 == 0)
    printf("\n");
  printf("%d ",L[i]);

  free(L);

  printf("\n\nThe algorithm took %lf seconds to complete.\n", t2-t1);

  fclose(fp);

  return 0;
}

/*
██   ██  █████  ██   ██ ███    ██
██  ██  ██   ██ ██   ██ ████   ██
█████   ███████ ███████ ██ ██  ██
██  ██  ██   ██ ██   ██ ██  ██ ██
██   ██ ██   ██ ██   ██ ██   ████
*/
int* Kahn_Algorithm(int *L,  struct node_info nodes[array_size], bool *matrix)
{
  int *S=(int *)malloc(array_size * (sizeof(int)));
  int counter=0,i=0;

  #pragma omp parallel num_threads(argv[1]) shared(i,counter,array_size,matrix,L,S)
  {

    #pragma omp for reduction(+:S[:array_size])
    for(int i=0; i<array_size; i++)
    {
      if(nodes[i].in_edges == 0)
      {
        #pragma omp critical
        {
          S[counter]=nodes[i].id;
          counter++;
        }
      }
    }

    #pragma omp single
    {
      for(int k=0; k<array_size; k++)
      {
        int n=S[i];
        L[i]=n;
        counter--,i++;
        if(counter<0) counter=0;

        #pragma omp taskloop
        for (int j=0; j<array_size; j++)
        {
          if( matrix[ (n-1) * array_size + j] == 1 )
          {
            matrix[ (n-1) * array_size + j] = false;
            nodes[j].in_edges--;
            if(nodes[j].in_edges == 0)
            {
              S[counter+i]=nodes[j].id;
              #pragma omp critical
              counter++;
            }
          }
        }
      }
    }
  }

  free(S);

  if(L[array_size-1]==0)
  {
    perror("The graph contains one or more cycles!\n");
    exit(EXIT_FAILURE);
  }

  else
  {
    return L;
  }
}