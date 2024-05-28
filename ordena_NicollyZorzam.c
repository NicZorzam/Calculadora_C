/* Nicolly Zorzam Moura - DRE: 121037550*/

#define TRUE 1
#define FALSE 0

  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

  
void bubble_sort(int *V, int quant_elem);
void merge_sort(int *V, int inicio, int fim);
void merge(int *V, int inicio, int meio, int fim);
void quick_sort(int *V, int inicio, int fim);
int particiona(int *V, int inicio, int fim);
void troca_posicao(int *V, int i, int j);
void printa_vetor(int *V, int tam);


int main(int argc, char *argv[]) {
  clock_t t; //variavel para armazenar o tempo 
  
  if ((argc < 3) || (argc > 4)) {
    printf ("Por favor, digite todos os argumentos necessários para o programa\n");
    return 1;
  }

  int quant_elem;
  int inicio;
  int fim;
  int encontrado = FALSE;
  
  for (int i = 1; i < 3; i++){
    if (strcmp((argv[i]), "-n") == 0){
      quant_elem = atoi(argv[i+1]);
    }

    if(quant_elem == 0){
        printf("Entrada do tamanho do vetor errada.");
        return 1;
    }
  }

  int *V = malloc(quant_elem * sizeof(int));
  if (V == NULL){
    printf("Erro de alocação de memória no vetor!");
    return 1;
  }
  
  srand(time(NULL));
  
  for (int i = 0; i < quant_elem; i++){
    V[i] = rand() % 100;
  }
  
  printf("Vetor gerado (desordenado):\n");
  printa_vetor(V, quant_elem);

  printf("\n\n");
  
  inicio = 0;
  fim = quant_elem-1;
  
  if (argc == 3){
    t = clock(); // armazena o tempo
    bubble_sort(V, quant_elem);
    t = clock() - t; //tempo final - tempo final
    printf("Vetor ordenado por bubble sort:\n");
  } else if (argc == 4){
    for (int i = 0; i < 4; i++){
      if (encontrado){
        break;
      }
        
      else if (strcmp((argv[i]), "-m") == 0){
        t = clock(); // armazena o tempo
        merge_sort(V, inicio, fim);
        t = clock() - t; //tempo final - tempo final
        printf("Vetor ordenado por merge sort:\n");
        encontrado = TRUE;
      }

      else if (strcmp((argv[i]), "-q") == 0){
        t = clock(); // armazena o tempo
        quick_sort(V, inicio, fim);
        t = clock() - t; //tempo final - tempo final
        printf("Vetor ordenado por quick sort:\n");
        encontrado = TRUE;
      }
    }

    if(!encontrado){
        printf("Entrada de ordenação não encontrada");
        return 1;
    }
    
    }

  printa_vetor(V, quant_elem);
  
  printf("\n\nTempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC/1000)));
  
  return 0;
}

void bubble_sort(int *V, int quant_elem){
  int i = 0;
  int Trocou = TRUE;

  while(i < (quant_elem-1) && (Trocou)){
    Trocou = FALSE;

    for (int j = 0; j < (quant_elem - i - 1); j++){
      if (V[j] > V[j+1]){
        troca_posicao(V, j, j+1);
        Trocou = TRUE;
      }
    }
    i++;
  }
}

void merge_sort(int *V, int inicio, int fim){
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        
        int meio2 = meio + 1;
 
        merge_sort(V, inicio, meio);
        merge_sort(V, meio2, fim);
        merge(V, inicio, meio, fim);
    }
}

void merge(int *V, int inicio, int meio, int fim){
    int i, j, k;
    
    int parte1 = meio - inicio + 1;
    int parte2 = fim - meio;
    /* alocando memória para os vetores auxiliares*/
    int *V1 = malloc(parte1 * sizeof(int));
    if (V1 == NULL){
        printf("Erro de alocação de memória no vetor!");
        return;
    }
  
    int *V2 = malloc(parte2 * sizeof(int));
    if (V2 == NULL){
        printf("Erro de alocação de memória no vetor!");
        return;
    }
    
    i = 0;
    j = 0;
    
    while (i < parte1){
        V1[i] = V[inicio + i];
        i++;
    }
    
    while (j < parte2){
        V2[j] = V[meio + 1 + j];
        j++;
    }
    
    i = 0; 
    j = 0; 
    k = inicio;
    
    while ((i < parte1) && (j < parte2)) {
        if (V1[i] <= V2[j]) {
            V[k] = V1[i];
            i++;
            k++;
        }
        else {
            V[k] = V2[j];
            j++;
            k++;
        }
        
    }

    while (i < parte1) {
        V[k] = V1[i];
        i++;
        k++;
    }
 
    while (j < parte2) {
        V[k] = V2[j];
        j++;
        k++;
    }
  
  free(V1);
  free(V2);
}

void quick_sort(int *V, int inicio, int fim){
    if(inicio < fim) {
        int pospivot = particiona(V, inicio, fim);
        quick_sort(V, inicio, pospivot - 1);
        quick_sort(V, pospivot + 1, fim);
    }
}

int particiona(int *V, int inicio, int fim){
    int i, j;
    int k;
    int posicao;
    int pivot;
    double d;
    
    //gerando posicao aleatoria para pivot
    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (fim - inicio + 1);
    posicao = inicio + k;
    
    //adicionando o pivot aleatorio no fim
    troca_posicao(V, posicao, fim);
    
    pivot = V[fim];
    i = inicio - 1;
    j = inicio;
    
    while(j < fim){
        if (V[j] <= pivot){
            i += 1;
            troca_posicao(V, i, j);
        }
        j++;
    }
    
    troca_posicao(V, i + 1, fim);
    
    return i + 1;
}

void troca_posicao(int *V, int i, int j){
    int temp = V[i];
    V[i] = V[j];
    V[j] = temp;
}

void printa_vetor(int *V, int tam){
  for (int i = 0; i < tam; i++){
    printf("%d ", V[i]);
  }
}