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

/*struct queue{
  struct Node *front;
  struct Node *rear;
  unsigned int size;
};

void init(struct queue *q){ // creating queue
  q->front = NULL;
  q->rear = NULL;
  q->size = 0;
}

int front(struct queue *q){ // gyrnaei to prwto node info xwris na to petaksei
  return q->front->data->id;
}

struct node_info * pop (struct queue *q){ // gyrnaei to prwto node_info kai to bgazei ektos ouras
  struct Node *tmp;
  q-> size--;
  tmp = q->front;
  q->front = q->front->next;
  return tmp->data;
}

void push (struct queue *q,struct node_info *newData){ // vazei sto telos ths ouras to neo data
  q->size++;
  if(q->front==NULL){
    q->front = (struct Node *) malloc(sizeof(struct Node));
    q->front->data = (struct node_info *) malloc(sizeof(struct node_info));
    q->front->data = newData->id;
    q->front->next= NULL;
    q->rear = q->front;
  }
  else{
    q->rear->next = (struct Node *) malloc(sizeof(struct Node));
    q->rear->next->data = (struct node_info *) malloc(sizeof(struct node_info));
    q->rear->next->data = newData;
    q->rear->next->next = NULL;
    q->rear = q->rear->next;
  }
}*/

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
  //struct node_info  *nodeItem;
  int nodeItem;
  //struct queue L; 
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
     nodes[temp2[iter] - 1 ].in_edges++; // setting in-edges of the node 
      }

       for (int i = 0; i < array_size; ++i) {
         printf("\n");
         for (int j = 0; j < array_size; ++j) { 
         printf("%d ",matrix[i * array_size + j]);
         }
       }
int *Larray=(int *)malloc(array_size * (sizeof(int)));

//  init(&L);

  t1=gettime();
  Larray = Kahn_Algorithm(Larray,  nodes, matrix); 
  t2=gettime();

  for(int i=0; i<array_size; i++)
  {
    //nodeItem = Larray[i];
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
  
  for(int i=0; i< array_size; i++)
  {
    if(nodes[i].in_edges == 0)
    { 
      Sarray[i]=nodes[i].id;
      printf("id in S=%d in_edges=%d nodesid=%d\n",Sarray[i],nodes[i].in_edges,nodes[i].id);
      counter++;
    } 
  }  
      while(counter > 0)
      { 
        int n=Sarray[i];
        Larray[i]=n;
        counter --;
        i++;
          for (int j=0; j<array_size; j++)
          {
            if( matrix[ ( n - 1 ) * array_size + j] == 1 )
            {
              matrix[ ( n - 1 ) * array_size + j] = false;
              nodes[j].in_edges--;
              if(nodes[j].in_edges == 0){
                Sarray[counter+i]=nodes[j].id;
                counter++;
             }   
            } 
          }
      }

      //for (int i = 0; i < array_size; ++i) { 
      //printf("%d \n ",Sarray[i]);
      //}
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
