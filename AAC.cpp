#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VECTOR_LENGHT 100


struct no{
  int data;
  struct no* left;
  struct no* right;
};

void addRandomNumbers(int *vector, int lenght){
  const int MIN_RANGE = 1;
  const int MAX_RANGE = lenght * 10;

  for (int i = 0; i < lenght; i++){
    srand(time(0));
    a: int num = (rand() % MAX_RANGE) + MIN_RANGE;

    for (int j = 0; j < i; j++){
      if(vector[j] == num)
        goto a;
    }

    vector[i] = num;
  }
}
void printVector(const int *const vector, int lenght){
  printf("[ ");
  for (int i = 0; i < lenght; i++){
    printf("%d", vector[i]);
    if(i < lenght - 1) 
      printf(", ");
  }
  printf(" ] \n");
}

void copy(const int *const originalVector, int *copyVector, int lenght){
  for (int i = 0; i < lenght; i++)
    copyVector[i] = originalVector[i];
}
void swap(int *firstPosition, int *secondPosition){
  int temporaryPosition = *firstPosition;

  *firstPosition = *secondPosition;
  *secondPosition = temporaryPosition;
}

void bubbleSort(const int *const vector, int *vectorCopy, int lenght ){
  copy(vector, vectorCopy, lenght);

  for (int i = 0; i < lenght - 1; i++)
    for (int j = 0; j < lenght - i - 1; j++)
      if (vectorCopy[j] > vectorCopy[j + 1])
        swap(&vectorCopy[j], &vectorCopy[j + 1]);
}
void selectionSort(const int *const vector, int *vectorCopy, int lenght){
  int aux;

  copy(vector, vectorCopy, lenght);

  for (int i = 0; i < lenght - 1; i++){
    aux = i;

    for (int j = i + 1; j < lenght; j++)
      if (vectorCopy[j] < vectorCopy[aux])
        aux = j;

    swap(&vectorCopy[aux], &vectorCopy[i]);
  }
}
void insertionSort(const int *const vector, int *vectorCopy, int lenght){
  int aux, j;

  copy(vector, vectorCopy, lenght);

  for (int i = 1; i < lenght; i++){
    aux = vectorCopy[i];
    j = i - 1;

    while (j >= 0 && vectorCopy[j] > aux){
      vectorCopy[j + 1] = vectorCopy[j];
      j = j - 1;
    }

    vectorCopy[j + 1] = aux;
  }
}

void countTime(
  double *msecElapsed,
  const int *const vector, 
  int *vectorCopy, 
  int lenght, 
  void (*doFunction)(const int* const, int*, int)
){
  clock_t startTime = clock();
  doFunction(vector, vectorCopy, lenght);
  clock_t stopTime = clock();
  *msecElapsed = 
    ((double)stopTime - (double)startTime)/((double)CLOCKS_PER_SEC) * 1000;
}


struct no *insert(struct no *node, int data){
  if(node == NULL){
    struct no *newNode = (struct no *)malloc(sizeof(struct no));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;

    node = newNode;
  }else{
    if(data < node->data)
      node->left = insert(node->left, data);
    else
      node->right = insert(node->right, data);
  }

  return node;
}

void traversePreOrder(struct no *node){
  if(node != NULL){
    printf("%d ", node->data);
    traversePreOrder(node->left);
    traversePreOrder(node->right);
  }
}

int main(){
  int vector[VECTOR_LENGHT] = {0};

  addRandomNumbers(vector, VECTOR_LENGHT);
  printf("\nVetor desordenado: \n");
  printVector(vector, VECTOR_LENGHT);

  int vectorCopy[VECTOR_LENGHT] = {0};
  double msecElapsed;

  countTime(&msecElapsed, vector, vectorCopy, VECTOR_LENGHT, bubbleSort);
  printf("\nBubble-Sorting: \n");
  printVector(vectorCopy, VECTOR_LENGHT);
  printf("Tempo total: %fs\n", msecElapsed);

  copy(vector, vectorCopy, VECTOR_LENGHT);

  countTime(&msecElapsed, vector, vectorCopy, VECTOR_LENGHT, selectionSort);
  printf("\nSelection-Sorting: \n");
  printVector(vectorCopy, VECTOR_LENGHT);
  printf("Tempo total: %fs\n", msecElapsed);

  copy(vector, vectorCopy, VECTOR_LENGHT);

  countTime(&msecElapsed, vector, vectorCopy, VECTOR_LENGHT, insertionSort);
  printf("\nVetor ordenado via insertion-sorting: \n");
  printVector(vectorCopy, VECTOR_LENGHT);
  printf("Tempo total: %fs\n\n", msecElapsed);

  struct no *node = NULL;
  for (int i = 0; i < VECTOR_LENGHT; i++)
    node = insert(node, vector[i]);

  printf("\nPercurso em pre-ordem: \n");
  traversePreOrder(node);

  printf("\n");

  return 0;
}
