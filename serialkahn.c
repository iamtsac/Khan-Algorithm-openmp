#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int array_size;

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

void push (struct queue *q,struct node_info *newData){ //vazei sto telos ths ouras to neo data
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

  while( ( fgets(data, 500, fp))) //read until we reach end of line
 {
     fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges);
     printf("Array size: %d x %d with %d edges\n",array_size,array_size,total_edges);
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

  bool matrix[array_size][array_size]; // array of edges between nodes
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
    if(feof(fp))
    break;
    matrix[temp1 - 1][temp2 - 1] = true; // initializing edges between nodes
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

int count =0;
struct queue s,l;

init(&s);

for(int i=0; i< array_size; i++){
  if(nodes[i].in_edges == 0)
  push(&s,&nodes[i]);
}

init(&l);

//l=kahnAlgorithm(&nodes,matrix[array_size][array_size],s,l);



/*struct node_info  *nodeItem;
nodeItem = NULL;*/

//while(s.size > 0){
//  nodeItem = pop(&s);
//  push(&l,*nodeItem);
//  printf("%d\n",nodeItem->id);
//  for (int j =0; j<array_size; j++)
//    if( matrix[nodeItem->id-1][j] ){
//      matrix[nodeItem->id-1][j] = false;
//      nodes[j].in_edges--;
//      if(nodes[j].in_edges<=0){
//        push(&s,nodes[j]);
//      }
//    }
//    count++;




fclose(fp);
return 0;
}

struct queue kahnAlgorithm(struct node_info *nodes, bool matrix[array_size][array_size], struct queue *S,struct queue *L){ 

    int count=0;
    int* temp=malloc(array_size *sizeof(int));
    while(S->size > 0){
        struct node_info *n=pop(S);
        push(L,n);

        for (int i=0; i<array_size; i++) {

            if(matrix[n->id-1][i]==1){

                count++; 
                matrix[n->id+1][i]=0;
                nodes[i].in_edges--;
                nodes[n->id+1].out_edges--;
                temp[count-1]=nodes[i].id;

            }
            temp[count]=-1;

            for(int j=0; j<array_size; j++) {

                if(temp[j]==-1) break;
                else {
                 if(nodes[j].in_edges==0){

                     push(S,&nodes[j]);
                 }
                } 
            }
        }
    }
    free(temp);
    return *L;
}


