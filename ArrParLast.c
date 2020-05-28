#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

int array_size, total_edges;


struct node_info{
int id;
int in_edges;
};

struct Node{
  struct node_info *data;
  struct Node *next;
};


int* Kahn_Algorithm(int *L,  struct node_info nodes[array_size], bool *matrix);


double gettime(void) {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec + 1e-6 * tv.tv_usec;
}


int main(void) {

  int iter ; 
  static char data[500];
  double t1,t2;
  int nodeItem;
  FILE *fp = fopen("dag.txt", "r");

  if(fp == NULL)
  {
    perror("Error while opening the file!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges);
  printf("Array size: %d x %d with %d edges\n",array_size,array_size,total_edges);
 
  struct node_info *nodes=(struct node_info *)malloc(array_size* sizeof(struct node_info));


  for(int i=0; i<array_size; i++)
  {
    nodes[i].id = i+1;
    nodes[i].in_edges = 0;
  }

  bool *matrix = (bool *)malloc(array_size *array_size * sizeof(bool)); 
  int* temp1 = (int *)malloc(total_edges * sizeof(int)); 
  int* temp2 = (int *)malloc(total_edges * sizeof(int)); 
     
       for( iter=0; iter<total_edges; iter++){ 

     fgets(data, sizeof(data), fp); 
     fscanf(fp, "%d %d", &temp1[iter],&temp2[iter]); 
     matrix[(temp1[iter] - 1 )* array_size + ( temp2[iter] - 1 )] = 1;
     nodes[temp2[iter] - 1 ].in_edges++; 
      }


//printing dag.
 /*    for (int i = 0; i < array_size; ++i) {  
         printf("\n");
         for (int j = 0; j < array_size; ++j) { 
         printf("%d ",matrix[i * array_size + j]);
         }
       }
       */

int *Larray=(int *)malloc(array_size * (sizeof(int)));


  t1=gettime();
  Larray = Kahn_Algorithm(Larray,  nodes, matrix); 
  t2=gettime();

  for(int i=0; i<array_size; i++)
  {
    printf("%d ",Larray[i]);
  }

  printf("\n"); 
  printf("time %lf  \n",t2-t1);

  fclose(fp);

  return 0;
}

int* Kahn_Algorithm(int *Larray,  struct node_info nodes[array_size], bool *matrix)
{


  int *Sarray=(int *)malloc(array_size * (sizeof(int)));
  int counter=0,i=0;
  int k,j = 0;

    

#pragma omp parallel num_threads(4) shared(matrix, Larray, counter, i)
{// #pragma omp taskloop shared(matrix, Sarray, nodes) private(j)
   //{

    int tid = omp_get_thread_num();
    int start = tid*(array_size/omp_get_num_threads());
    int end;

    if(tid <  omp_get_num_threads()){
        end = (tid+1)*(array_size/omp_get_num_threads());
        printf("tid = %d  end = %d \n",tid , end);
    }

    else{
    end = array_size;
    }    

  #pragma omp for reduction(+:Sarray[:array_size]) 
    
        for(int i=0; i< array_size; i++)
        {
            if(nodes[i].in_edges == 0)
            { 
            #pragma omp critical
             Sarray[counter]=nodes[i].id;
             counter++;
            } 
        }
    
    #pragma omp single
    #pragma omp taskloop num_tasks(32)
        for(k = 0; k< array_size; k++)
        { 
                int n=Sarray[i];
                Larray[i]=n;
                counter --;
                i++;
            
                    for (j=0; j<array_size; j++)
                    {

                        if( matrix[ ( n - 1 ) * array_size + j] == 1 )
                        {
                            matrix[ ( n - 1 ) * array_size + j] = false;
                            nodes[j].in_edges--;
                            if(nodes[j].in_edges == 0)
                                {
                                    Sarray[counter+i]=nodes[j].id;
                                    counter++;

                                }
                        } 
                    }
        }  
}  
    if(i < array_size)
    {
        perror("The graph contains one or more cycles!\n");
        exit(EXIT_FAILURE);
    }

    else
    {
        printf("Successful!\nThe Topological sort is: ");
        return Larray;
    }

}