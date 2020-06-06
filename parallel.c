#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

int array_size, total_edges;

struct node_info // Δημιουργουμε το struct που περιεχει τους κομβους και πληροφορίες για αυτους.
{
  int id;
  int in_edges;
};

double get_time(void) // Ο high resolution timer.
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + 1e-6 * tv.tv_usec;
}

int* Kahn_Algorithm(int threads,int *L,  struct node_info nodes[array_size], bool *matrix); // Δηλωση του Αλγοριθμου του Kahn.


//                   ███    ███  █████  ██ ███    ██
//                   ████  ████ ██   ██ ██ ████   ██
//                   ██ ████ ██ ███████ ██ ██ ██  ██
//                   ██  ██  ██ ██   ██ ██ ██  ██ ██
//                   ██      ██ ██   ██ ██ ██   ████


int main(int argc, char **argv)
{
  static char data[50];
  double t1,t2;
  FILE *fp = fopen("dag.txt", "r");

  if(argv[1] == NULL) // Ελεγχος για την υπαρξη του argument που αφορά το πληθος των cores.
  {
    perror("You have to declare the number of threads!\n");
    exit(EXIT_FAILURE);
  }

  if(fp == NULL) // Ελεγχος υπαρξης του αρχειου.
  {
    perror("Error while opening the file!\n");
    exit(EXIT_FAILURE);
  }

  fscanf(fp, "%d %d %d", &array_size, &array_size, &total_edges); // Διαβασμα της πρωτης γραμμης του αρχειου και αρχικοποιηση του array_size και total_edges.
  printf("Array size: %d x %d with %d edges\n",array_size,array_size,total_edges);
 
  struct node_info *nodes = (struct node_info *)malloc(array_size* sizeof(struct node_info));
  
  for(int i=0; i<array_size; i++) // Κανουμε initialize το struct και καθορίζουμε τα id.
  {
    nodes[i].id = i+1;
    nodes[i].in_edges = 0;
  }

  // Αρχικοποιουμε δυναμικα τους παρακατω πινακες για να μπορουμε να δουλεψουμε σε πολυ μεγαλα γραφηματα.
  bool *matrix = (bool *)malloc(array_size *array_size * sizeof(bool));
  int *L = (int *)malloc(array_size * sizeof(int));
  int *temp1 = (int *)malloc(total_edges * sizeof(int));
  int *temp2 = (int *)malloc(total_edges * sizeof(int));

  // Αρχικοποιουμε το μητρωο γειτνιασης και μετραμε τις εισερχομενες ακμες
  // Καθε κομβου διαβαζοντας τις πληροφορίες απο το αρχειο.  
  for(int i=0; i<total_edges; i++)
  {
    fgets(data, sizeof(data), fp);
    fscanf(fp, "%d %d", &temp1[i],&temp2[i]);
    matrix[(temp1[i] - 1 )* array_size + ( temp2[i] - 1 )] = 1;
    nodes[temp2[i] - 1 ].in_edges++;
  }


  t1=get_time();
  L = Kahn_Algorithm(atoi(argv[1]),L, nodes, matrix);
  t2=get_time();


  printf("Successful!\nThe Topological sort is: \n");
  for(int i=0; i<array_size; i++)
  {
    if(i%30 == 0) printf("\n"); 
    printf("%d ",L[i]);
  } 

  printf("\n\nThe algorithm took %lf seconds to complete.\n", t2-t1);

  fclose(fp);

  return 0;
}


//                   ██   ██  █████  ██   ██ ███    ██
//                   ██  ██  ██   ██ ██   ██ ████   ██
//                   █████   ███████ ███████ ██ ██  ██
//                   ██  ██  ██   ██ ██   ██ ██  ██ ██
//                   ██   ██ ██   ██ ██   ██ ██   ████


int* Kahn_Algorithm(int threads,int *L,  struct node_info nodes[array_size], bool *matrix)
{
  int *S=(int *)malloc(array_size * (sizeof(int)));
  int counter=0,i=0;

  #pragma omp parallel num_threads(threads) shared(i,counter,array_size,matrix,L,S)
  { 
    #pragma omp for reduction(+:S[:array_size])
    for(int i=0; i<array_size; i++)
    {
      if(nodes[i].in_edges == 0)
      {
        #pragma omp critical
        {
          S[counter]=nodes[i].id;
          counter++; // Μετραει τα στοιχεια του S.
        }
      }
    }

    #pragma omp single
    {
      for(int k=0; k<array_size; k++)
      {
        int n=S[k];
        L[i]=n;
        counter--,i++; // Ο counter μετραει τα στοιχεια στην S και το i την θεση που πρεπει να αποθηκευτουν τα στοιχεια στην L.

        #pragma omp taskloop
        for (int j=0; j<array_size; j++)
        {
          if( matrix[ (n-1) * array_size + j] == 1 )
          {
            matrix[ (n-1) * array_size + j] = false; // Στο μητρωο σβηνουμε τις εξερχομενες ακμες του στοιχειου που πηραμε απο τον πινακα S.
            nodes[j].in_edges--; // Και ενημερωνουμε το struct για τον αριθμο των εισερχομενων ακμων.
            if(nodes[j].in_edges == 0) // Αν καποιος κομβος δεν εχει εισερχομενες ακμες τον βαζουμε στον S.
            {
              #pragma omp critical
              {
                S[counter+i]=nodes[j].id; // Η θεση counter+i ειναι παντα η αμεσως επομενη αδεια θεση του S οποτε δεν υπαρχουν κενες θεσεις μεταξυ των στοιχειων.
                counter++;
              }
            }
          }
        }
      }
    }
  }


  if( L[array_size-1]==0 || L[array_size]!=0 ) // Για να μην υπαρχει κυκλος πρεπει το μεγεθος του πινακα L να είναι ισο με το array_size.
  {
    perror("The graph contains one or more cycles!\n");
    exit(EXIT_FAILURE);
  }

  else
  {
    return L;
  }
}
