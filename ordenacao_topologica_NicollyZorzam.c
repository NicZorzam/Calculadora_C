/* Trecho do código (leitura das adjacências) tirado de sample code topo.c do Classroom da turma de ED 2021/1 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _tno{
    int chave;
    struct _tno *prox;
} tno;

void inicializacao(int *ordenacao, int *grau_vertices, tno **adjacencias, int vertices);
void leitura_adjacencias(tno **adjacencias, int *grau_vertices, int vertices);
void insere(tno** ptlista, int x);
int adiciona_prim_vert(int *ordenacao, int *grau_vertices, int vertices);
void adiciona_outros_verts(tno **adjacencias, int *ordenacao, int *grau_vertices, int vertices, int pos);
void imprimir_e_free(tno **adjacencias, int *ordenacao, int vertices);
void printa_vetor(int *vetor, int vertices);

int main(){
  int i;
  int pos;
  int *grau_vertices;
  int *ordenacao;
  int vertices, arestas;
  tno **adjacencias;
    
    
  scanf("%d %d\n", &vertices, &arestas);

  adjacencias = (tno**) malloc((vertices)*(sizeof(tno*)));
  grau_vertices = (int*) malloc((vertices)*(sizeof(int)));
  ordenacao = (int*) malloc((vertices)*(sizeof(int)));

  inicializacao(ordenacao, grau_vertices, adjacencias, vertices);
  
  leitura_adjacencias(adjacencias, grau_vertices, vertices);
 
  pos = adiciona_prim_vert(ordenacao, grau_vertices, vertices);

  adiciona_outros_verts(adjacencias, ordenacao, grau_vertices, vertices, pos);

  printf("Ordenação topológica:\n");
  imprimir_e_free(adjacencias, ordenacao, vertices);  

  free(grau_vertices);
  free(ordenacao);
  free(adjacencias);
  
  return 0;
}


void inicializacao(int *ordenacao, int *grau_vertices, tno **adjacencias, int vertices){
  int i;
  
  for (i = 0; i < vertices; i++){
    ordenacao[i] = 0;
    grau_vertices[i] = 0;
    adjacencias[i] = NULL;
  }
}

void leitura_adjacencias(tno **adjacencias, int *grau_vertices, int vertices){
  /* Trecho retirado do código sample code topo.c */
  int i;
  int pos;
  int numLido;
  int numChars;
  char *linha = NULL;
  size_t tamLinha = 0;
  
  for(int i = 0; i < vertices; i++){
    getline(&linha,&tamLinha,stdin);
    pos = 0;
    numLido = 0;

    while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0) {
      pos += numChars;
      numLido--; /* Diminui para "encaixar" no intervalo de 0 (inclusive) a vertice (exclusive); */
      if(strlen(linha) != 0){
        insere(&adjacencias[i], numLido); 
        grau_vertices[numLido]++;    
      }
    }
  }
}

void insere(tno** ptlista, int x){
    tno *novo;
    novo = (tno*) malloc(sizeof(tno));
    if (novo != NULL){
        novo->chave = x;
        novo->prox = (*ptlista);
        (*ptlista) = novo;
    }
}

int adiciona_prim_vert(int *ordenacao, int *grau_vertices, int vertices){
  int i;
  int pos;
  int menor = grau_vertices[1];
  
  for(i = 0; i < vertices; i++){
        if (grau_vertices[i] < menor){
            menor = grau_vertices[i];
        }
  }
  
  pos = 0;
  for (i = 0; i < vertices; i++){
    if(grau_vertices[i] == menor){
      ordenacao[pos] = i;
      pos++;
    }
  }

  return pos;
}

void adiciona_outros_verts(tno **adjacencias, int *ordenacao, int *grau_vertices, int vertices, int pos){
  int i;
  
  for(i = 0; i < vertices; i++){
    tno *pt;
    pt = adjacencias[ordenacao[i]];
    
    while(pt != NULL){
      grau_vertices[pt->chave]--;
      
      if(grau_vertices[pt->chave] == 0){
        ordenacao[pos] = pt->chave;
        pos++;
      }
      
      pt = pt->prox;
    }
  }
}

void imprimir_e_free(tno **adjacencias, int *ordenacao, int vertices){
  int i;
  int num;
  
  for(i = 0; i < vertices; i++){
    num = (ordenacao[i]+1); /* Adicionando a unidade retirada de cada adjacencia lida */
    printf("%d ", num);
    
    tno *pt = adjacencias[i];
    
    while(pt != NULL){
      pt = pt->prox;
      free(adjacencias[i]);
      adjacencias[i] = pt;
    }
  }
}

void printa_vetor(int *vetor, int vertices){
  int i;
  printf("\nVai printar\n");
  for(i = 0; i < vertices; i++){
    printf("%d ", vetor[i]);
  }
    printf("\nFim\n");
}