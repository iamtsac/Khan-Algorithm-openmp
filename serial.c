#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <omp.h>

int array_size, total_edges;

//Creating the structs
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

void init(struct queue *q){ //dhmiourgei thn oura
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

//Push And Pop
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

struct queue Kahn_Algorithm(struct queue *L, struct queue *S, struct node_info nodes[array_size], bool *matrix)
{
    for (int i = 1; i > 0; i++) {
      struct node_info *n = pop(S);
      push(L,n);
      for (int i=0; i<array_size; i++)
      {
        if( matrix[ ( n->id - 1 ) * array_size + i] == 1 )
        {
          matrix[ ( n->id - 1 ) * array_size + i] = false;
          nodes[i].in_edges--;
          if(nodes[i].in_edges == 0)
          push(S,&nodes[i]);
        }
      }
      if(S->size == 0) i=-1;
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

  static char data[500];
  double t1,t2;
  struct node_info  *nodeItem;
  struct queue  S, L; 
  FILE *fp = fopen("dag.txt", "r");

  if(fp == NULL)
  {
    perror("Error while opening the file!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges);
  printf("Array size: %d x %d with %d edges\n",array_size,array_size,total_edges);
 
  struct node_info *nodes=(struct node_info *)malloc(array_size* sizeof(struct node_info));

  t1=gettime();

  for(int i=0; i<array_size; i++)
  {
    nodes[i].id = i+1;
    nodes[i].in_edges = 0;
  }

  bool *matrix = (bool *)malloc(array_size *array_size * sizeof(bool)); 
  int* temp1 = (int *)malloc(total_edges * sizeof(int)); 
  int* temp2 = (int *)malloc(total_edges * sizeof(int)); 

  
  for (int i = 0; i <total_edges-1; i++) {
     fgets(data, 500, fp);
     fscanf(fp, "%d %d", &temp1[i],&temp2[i]);
     matrix[(temp1[i] - 1 )* array_size + ( temp2[i] - 1 )] = 1;
     nodes[temp2[i] - 1 ].in_edges++; // setting in-edges of the node 
  } 

  init(&S);

  for(int i=0; i< array_size; i++)
  {

    if(nodes[i].in_edges == 0)
    push(&S, &nodes[i]);

  }

  init(&L);

  L = Kahn_Algorithm(&L, &S, nodes, matrix);



  for(int i=0; i<array_size; i++)
  {

  nodeItem = pop(&L);
  printf("%d ",nodeItem->id);

  }

  t2=gettime();
  printf("\n"); 
  printf("time %lf  \n",t2-t1);

  fclose(fp);

  return 0;
} 

