#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <stdbool.h>
#include <ctype.h>
=======
#include <ctype.h>
#include <stdbool.h>

int array_size, total_edges;
>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2

struct node_info{
int id;
int out_edges;
int in_edges;
<<<<<<< HEAD
}node;
=======
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

struct queue Kahn_Algorithm(struct queue *L, struct queue *S, struct node_info nodes[array_size], bool matrix[array_size][array_size])
{

    while(S->size > 0){
      int count = 0;
      struct node_info *n = pop(S);
      push(L,n);
      for (int i=0; i<array_size; i++)
      {
        if( matrix[n->id - 1][i] == 1 )
        {
          matrix[n->id - 1][i] = false;
          nodes[i].in_edges--;
          nodes[n->id - 1].out_edges--;
          if(nodes[i].in_edges == 0)
          push(S,&nodes[i]);
        }
      }
      count++;
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


/****************************************************************/
/****************************************************************/
/***************************** ΜΑΙΝ *****************************/
/****************************************************************/
/****************************************************************/
>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2


int main(void)
{
<<<<<<< HEAD
  int array_size, total_edges, temp1, temp2, line_count = 0;
  char data[500], temp;
=======
  int temp1, temp2;
  char data[500];


>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2
  FILE *fp = fopen("data.txt", "r");
  if(fp == NULL)
  {
    perror("Error while opening the file!\n");
    exit(EXIT_FAILURE);
  }

<<<<<<< HEAD
  while( ( fgets(data, 500, fp)) !=  NULL ) // until we reach end of 1st line
  {
    fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges);
    break;
  }

  struct node_info nodes[array_size]; // array of nodes
=======
  while( (fgets(data, 500, fp))) //read until we reach end of line
 {
     fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges);
     printf("Array size: %d x %d with %d edges\n",array_size,array_size,total_edges);
     break;
 }

  struct node_info nodes[array_size]; // array of nodes
  struct queue q;
  init(&q); //create of queue

>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2
  for(int i=0; i<array_size; i++)
  {
    nodes[i].id = i+1;
    nodes[i].in_edges = 0;
    nodes[i].out_edges = 0;
  }

  bool matrix[array_size][array_size]; // array of edges between nodes
  for(int i=0; i<array_size; i++)
  {
    for(int j=0; j<array_size; j++)
    {
<<<<<<< HEAD
      matrix[i][j] = false; // initializing all values of the array to be 0 (no relation/edges between nodes)
=======
      matrix[i][j]=0; // initializing all values of the array to be 0 (no relation/edges between nodes)
>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2
    }
  }


<<<<<<< HEAD
  while( ( fgets(data, 500, fp)) !=  NULL ) // until we reach EOF
  {
    fscanf(fp, "%d %d", &temp1, &temp2);
    if (feof(fp)) {
    break;
    }
    matrix[temp1 - 1][temp2 - 1] = true; // initializing edges between nodes
    nodes[temp1 - 1].out_edges++; // setting out-edges of the node
    nodes[temp2 - 1].in_edges++; // setting in-edges of the node
=======
  while( (fgets(data, 500, fp)) !=  NULL ) // until we reach EOF
  {
    fscanf(fp, "%d %d", &temp1, &temp2);
    if(feof(fp))
    break;
    matrix[temp1 - 1][temp2 - 1] = true; // initializing edges between nodes
    nodes[temp1 - 1].out_edges++; // setting out-edges of the node
    nodes[temp2 - 1].in_edges++; // setting in-edges of the node

>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2
  }

  for(int i=0; i<array_size; i++) // printing matrix data
  {
<<<<<<< HEAD
    printf("Node %d :\n",i+1);
    for(int j=0; j<array_size; j++)
    {
      if(i != j)
      printf("-> Node %d : %d\n",j+1,matrix[i][j]);
=======
    for(int j=0; j<array_size; j++)
    {
      printf("Node %d -> Node %d : %d\n",i+1,j+1,matrix[i][j]);
>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2
    }
    printf("\n\n\n");
  }

<<<<<<< HEAD
=======
  printf("\n\n\n");
>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2
  for(int i=0; i<array_size; i++) // printing node data
  {
    printf("id: %d\tout_edges: %d\tin_edges: %d\n",nodes[i].id, nodes[i].out_edges, nodes[i].in_edges);
  }

<<<<<<< HEAD
  fclose(fp);

return 0;
}


=======
  struct queue S, L;

  init(&S);

  for(int i=0; i< array_size; i++)
  {
    if(nodes[i].in_edges == 0)
    push(&S, &nodes[i]);
  }

  init(&L);

  L = Kahn_Algorithm(&L, &S, nodes, matrix);

  struct node_info  *nodeItem;
  for(int i=0; i<array_size; i++){
  nodeItem = pop(&L);
  printf("%d ",nodeItem->id);
}
  printf("\n");

  fclose(fp);
return 0;
}
>>>>>>> a65c966bf5c42d123f801e0ba0926899ec58a5d2
