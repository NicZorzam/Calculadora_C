#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>

typedef struct _aresta {
  int vert1;
  int vert2;
  int peso; 
} aresta;

void bubble_sort_adaptado(aresta *lista_arestas, int arestas);
void print(aresta *lista_arestas, int arestas);

int main() {
  int i, j, temp;
  int cor_max;
  int vert1, vert2, peso;
  int soma_peso;
  int vertices;
  int arestas;
  int *lista_vertices;
  int *quant_arestas_cores;
  aresta *lista_arestas;
  
  scanf("%d %d", &vertices, &arestas);
  
  lista_arestas = (aresta*) malloc(arestas*sizeof(aresta));
  lista_vertices = (int*) calloc(vertices, sizeof(int));
  quant_arestas_cores = (int*) calloc((arestas/2) + 1, sizeof(int));

  
  for(i = 0; i < arestas; i++) {
    scanf("%d %d %d", &vert1, &vert2, &peso);
      lista_arestas[i].vert1 = vert1;
      lista_arestas[i].vert2 = vert2;
      lista_arestas[i].peso = peso;
  }
  bubble_sort_adaptado(lista_arestas, arestas);
  
  cor_max = 1;
  soma_peso = 0;
  
  for(i = 0; i < arestas; i++) {
    
    if(lista_vertices[lista_arestas[i].vert1 - 1] == 0 && lista_vertices[lista_arestas[i].vert2 - 1] == 0){/* Situação sem cor -> nova cor*/
      lista_vertices[lista_arestas[i].vert1 - 1] = cor_max;
      lista_vertices[lista_arestas[i].vert2 - 1] = cor_max;
      soma_peso += lista_arestas[i].peso;
      quant_arestas_cores[cor_max - 1]++;/* Adiciona uma unidade na lista, representando a aresta (agora tem uma aresta daquela cor */
      cor_max++;/* nova cor */
    }
    
    else if(lista_vertices[lista_arestas[i].vert1 - 1] == 0 && lista_vertices[lista_arestas[i].vert2 - 1] != 0){/* vert2 tem cor e vert1 não tem */
      lista_vertices[lista_arestas[i].vert1 - 1] = lista_vertices[lista_arestas[i].vert2 - 1];/* vert1 ganha a cor de vert2 */
      soma_peso += lista_arestas[i].peso;
      quant_arestas_cores[lista_vertices[lista_arestas[i].vert2 - 1] - 1]++;
    }
    
    else if(lista_vertices[lista_arestas[i].vert1 - 1] != 0 && lista_vertices[lista_arestas[i].vert2 - 1] == 0){/* vert1 tem cor e vert2 não tem */
      lista_vertices[lista_arestas[i].vert2 - 1] = lista_vertices[lista_arestas[i].vert1 - 1];/* vert2 ganha a cor de vert1 */
      soma_peso += lista_arestas[i].peso;
      quant_arestas_cores[lista_vertices[lista_arestas[i].vert1 - 1] - 1]++;
    }
      
    else if (lista_vertices[lista_arestas[i].vert1 - 1] == lista_vertices[lista_arestas[i].vert2 - 1]){  /*vert1 e vert2 têm a mesma cor 
       ignora (não faz nada) */
    }
      
    else{
      /* vert1 e vert2 têm cores diferentes */
      if(quant_arestas_cores[lista_vertices[lista_arestas[i].vert1 - 1] - 1] > quant_arestas_cores[lista_vertices[lista_arestas[i].vert2 - 1] - 1]) {
        /* quantidade de arestas da mesma cor que vert1 é maior que quantidade de arestas da mesma cor que vert2 (trocar todas as arestas com a cor de vert2 para vert1 - otimização) */
        temp = lista_vertices[lista_arestas[i].vert2 - 1];
        
        for(j = 0; j < arestas; j++){
          if(lista_vertices[j] == temp){
            lista_vertices[j] = lista_vertices[lista_arestas[i].vert1 - 1];
          }
        }
        quant_arestas_cores[lista_vertices[lista_arestas[i].vert1 - 1] - 1] += quant_arestas_cores[lista_vertices[lista_arestas[i].vert2 - 1] - 1] + 1;
      }
      
      else{
        /* quantidade de arestas da mesma cor que vert2 é maior (ou igual) que quantidade de arestas da mesma cor que vert1 (trocar todas as arestas com a cor de vert1 para vert2 - otimização) */
        temp = lista_vertices[lista_arestas[i].vert1 - 1];
        
        for(j = 0; j < arestas; j++) {
          if(lista_vertices[j] == temp) {
            lista_vertices[j] = lista_vertices[lista_arestas[i].vert2 - 1];
          }
        }
        
        quant_arestas_cores[lista_vertices[lista_arestas[i].vert2 - 1] - 1] += quant_arestas_cores[lista_vertices[lista_arestas[i].vert1 - 1] - 1] + 1;
      }
      
      soma_peso += lista_arestas[i].peso;
    }
  }
  printf("%d", soma_peso);
  
  free(lista_arestas);
  free(lista_vertices);
  free(quant_arestas_cores);
  return 0;
}

void bubble_sort_adaptado(aresta *lista_arestas, int arestas){
  int j, i = 0;
  int Trocou = TRUE;
  int temp;

  while(i < (arestas-1) && (Trocou)){
    Trocou = FALSE;

    for (j = 0; j < (arestas - i - 1); j++){
      if (lista_arestas[j].peso > lista_arestas[j+1].peso){
        
        temp = lista_arestas[j].vert1;
        lista_arestas[j].vert1 = lista_arestas[j+1].vert1;
        lista_arestas[j+1].vert1 = temp;

        temp = lista_arestas[j].vert2;
        lista_arestas[j].vert2 = lista_arestas[j+1].vert2;
        lista_arestas[j+1].vert2 = temp;

        temp = lista_arestas[j].peso;
        lista_arestas[j].peso = lista_arestas[j+1].peso;
        lista_arestas[j+1].peso = temp;

        Trocou = TRUE;
      }
    }
    i++;
  }
}

void print(aresta *lista_arestas, int arestas){
  int i;
  int vert1, vert2, peso;
  printf("\n");
  for (i = 0; i < arestas; i++){
    vert1 = lista_arestas[i].vert1;
    vert2 = lista_arestas[i].vert2;
    peso = lista_arestas[i].peso;
    printf("%d %d %d\n", vert1, vert2, peso);
  }
}


