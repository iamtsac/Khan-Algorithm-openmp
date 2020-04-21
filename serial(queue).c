#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node_info{
int id;
int out_edges;
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

int front(struct queue *q){ //gyrnaei to prwto node info xwris na to petaksei
  return q->front->data->out_edges;
}

struct node_info * pop (struct queue *q){ //gyrnaei to prwto node_info kai to bgazei ektos ouras
  struct Node *tmp;
  q-> size--;
  tmp = q->front;
  q->front = q->front->next;
  //free(q);
  return tmp->data;
}

void push (struct queue *q,struct node_info newData){ //vazei sto telos ths ouras to neo data
  q->size++;
  if(q->front== NULL){
    q->front = (struct Node *) malloc(sizeof(struct Node));
    q->front->data = &newData;
    q->front->next= NULL;
    q->rear = q->front;
  }
  else{
    q->rear->next = (struct Node *) malloc(sizeof(struct Node));
    q->rear->next->data = &newData;
    q->rear->next->next = NULL;
    q->rear = q->rear->next;
  }
}


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

  while( fgets(data, 500, fp)) // until we reach end of 1st line
  {
    fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges);
    printf("Array size: %d",array_size);
    break;
  }

  struct node_info nodes[array_size]; // array of nodes
  struct queue q;
  init(&q); //create of queue

  for(int i=0; i<array_size; i++)
  {
    nodes[i].id = i+1;
    nodes[i].in_edges = 0;
    nodes[i].out_edges = 0;
  }

  int matrix[array_size][array_size]; // array of edges between nodes
  for(int i=0; i<array_size; i++)
  {
    for(int j=0; j<array_size; j++)
    {
      matrix[i][j]=0; // initializing all values of the array to be 0 (no relation/edges between nodes)
    }
  }


  while( ( fgets(data, 500, fp)) !=  NULL ) // until we reach EOF
  {
    fscanf(fp, "%d %d", &temp1, &temp2);
    matrix[temp1 - 1][temp2 - 1] = 1; // initializing edges between nodes
    nodes[temp1 - 1].out_edges++; // setting out-edges of the node
    nodes[temp2 - 1].in_edges++; // setting in-edges of the node
  }

  printf("Successfull parsing of data! Line count: %d\n",line_count);

  for(int i=0; i<array_size; i++) // printing matrix data
  {
    for(int j=0; j<array_size; j++)
    {
      printf("Node %d -> Node %d : %d\n",i+1,j+1,matrix[i][j]);
    }
    printf("\n\n\n");
  }

  printf("\n\n\n");
  for(int i=0; i<array_size; i++) // printing node data
  {
    printf("id: %d\tout_edges: %d\tin_edges: %d\n",nodes[i].id, nodes[i].out_edges, nodes[i].in_edges);
  }


//Topological Sort


  fclose(fp);
return 0;
}
