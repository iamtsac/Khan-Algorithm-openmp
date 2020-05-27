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

struct queue{
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
    q->front->data = newData;
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
}

struct queue Kahn_Algorithm(struct queue *L,  struct node_info nodes[array_size], bool *matrix);


double gettime(void) {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec + 1e-6 * tv.tv_usec;
}


/* 
███    ███  █████  ██ ███    ██ 
████  ████ ██   ██ ██ ████   ██ 
██ ████ ██ ███████ ██ ██ ██  ██ 
██  ██  ██ ██   ██ ██ ██  ██ ██ 
██      ██ ██   ██ ██ ██   ████                                   
*/

int main(void) {

  int iter ; 
  static char data[50];
  double t1,t2;
  struct node_info  *nodeItem;
  struct queue   L; 
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
     
       for( iter=0; iter<total_edges-1; iter++){ 

     fgets(data, 50, fp); 
     fscanf(fp, "%d %d", &temp1[iter],&temp2[iter]); 
     matrix[(temp1[iter] - 1 )* array_size + ( temp2[iter] - 1 )] = 1;
     nodes[temp2[iter] - 1 ].in_edges++; // setting in-edges of the node 
      }
  
  

  //init(&S);


  init(&L);

  t1=gettime();
  L = Kahn_Algorithm(&L,  nodes, matrix); 
  t2=gettime();


  for(int i=0; i<array_size; i++)
  {
    nodeItem = pop(&L);
    //printf("%d ",nodeItem->id);
  }

  printf("\n"); 
  printf("time %lf  \n",t2-t1);

  fclose(fp);

  return 0;
}

struct queue Kahn_Algorithm(struct queue *L,  struct node_info nodes[array_size], bool *matrix)
{
#pragma omp parallel num_threads(4) shared(matrix,nodes,L,array_size) 
  {
    struct queue S;
    init(&S);
  for(int i=0; i< array_size; i++)
  {

    if(nodes[i].in_edges == 0)
    #pragma omp critical
    push(&S, &nodes[i]);

  }
    int tid = omp_get_thread_num();
     printf("Hello world from omp thread %d\n", tid);
         
    for (int i = 1; i > 0; i++) 
    {
      struct node_info *n = pop(&S);
      printf("%d \n",n->id);
#pragma omp critical
      push(L,n);
      for (int i=0; i<array_size; i++)
      {
        if( matrix[ ( n->id - 1 ) * array_size + i] == 1 )
        {
          matrix[ ( n->id - 1 ) * array_size + i] = false;
          nodes[i].in_edges--;
          if(nodes[i].in_edges == 0)
            push(&S,&nodes[i]);

        }
      }
   //   if(S->size == 0) i=-1;
    }
   } 

    if(L->size < array_size)
    {
     perror("The graph contains one or more cycles!\n");
     exit(EXIT_FAILURE);
    }

    else
    {
      printf("Successful!\nThe Topological sort is: ");
      return *L;
    }

}
