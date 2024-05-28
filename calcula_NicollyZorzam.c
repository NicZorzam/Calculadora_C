/* INCLUDES: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* DEFINES: */
#define TRUE 1
#define FALSE 0

/* FUNÇÕES: */
void resolve_expressao(); 
int verifica_pilha_char(char *pilha_char);
int verifica_pilha_int(int *pilha_int);
void adiciona_numero();
int determina_numero(int index, int casas);
int tem_parenteses(char c);
int e_operador(char c);
int identifica_operador(char c);
void adiciona_operador();
int operacao(char x, int a, int b);
int faz_conta();
int verifica();
void printa_pilha_int (int *pilha_int);
void printa_pilha_char (char *pilha_char);


/* VARIÁVEIS GLOBAIS */
char expressao[1000];
int pilha_numeros[1000];
char pilha_operadores[1000];
int i_expressao = 0; /* indice expressão */
int i_p_numeros = 0; /* indice pilha de números */
int i_p_operadores = 0; /* indice pilha de operadores */
int quant = 0; /* quantidade total de elementos da expressão */


/* MAIN */
int main(void) {
  int t, z;
  char copy[1000];
  int copia = FALSE;
  int result;
  
  
  if(verifica_pilha_char(expressao)){
    printf("Erro de alocação de memória no vetor!");
    return 1;
  }
  
  
  if(verifica_pilha_int(pilha_numeros)){
    printf("Erro de alocação de memória no vetor!");
    return 1;
  }
  
  
  if(verifica_pilha_char(pilha_operadores)){
    printf("Erro de alocação de memória no vetor!");
    return 1;
  }

  if(verifica_pilha_char(copy)){
    printf("Erro de alocação de memória no vetor!");
    return 1;
  }

  printf("Por favor, digite a expressão desejada.\n");
  fgets(expressao, 1000, stdin);

  while(expressao[i_expressao] != '\0'){
    if(expressao[i_expressao] == ' '){ //adaptando para se tiver espaço
      copia = TRUE;
    }
    quant++;
    i_expressao++;
  }

  

  if(copia){
    t = 0;
    for(z = 0; z < quant; z++){
      if(expressao[z] == ' '){
        z++;
      }
      copy[t] = expressao[z];
      t++;
    }
    
    quant = 0;
    z = 0;
    t = 0;

    while(copy[z] != '\0'){
      quant++;
      z++;
    }
    
    for(z = 0; z < quant; z++){
      expressao[t] = copy[z];
      t++;
    }

    for(z = quant; z < 1000; z++){
      expressao[z] = '\0';
    }

    for(z = 0; z < quant; z++){
      copy[z] = '\0';
    }
  }
    
  quant--; // é necessário por causa do fgets
  printf("\nQuantidade de caracteres: %d\n", quant);

  i_expressao = 0;
  
  while(i_expressao < quant){
    resolve_expressao();
  }
  result = pilha_numeros[0];
  
  

  printf("\n\nRESULTADO: %d", result);
  return 0;
}


void resolve_expressao(){
    
    if(tem_parenteses(expressao[i_expressao])){
    }
      
    else if(e_operador(expressao[i_expressao])){
      adiciona_operador();
    }
    else{
      adiciona_numero(expressao, pilha_numeros, pilha_operadores);
    }
    do{
      faz_conta();
    } while(faz_conta());

    
  
}

int verifica_pilha_char(char *pilha_char){
  if (pilha_char == NULL){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

int verifica_pilha_int(int *pilha_int){
  if (pilha_int == NULL){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

void adiciona_numero(){
  
  int numero;
  int casas = 0; /* quantidade de casas do número */
  int index_num; /* indice que o número começa na expressão */
  int round = 0;
  
  while((!identifica_operador(expressao[i_expressao])) && (i_expressao < quant)){
    round++;
    casas++;
    i_expressao++;
  }
  
  index_num = i_expressao-casas;

  
  if((identifica_operador(expressao[index_num-1])) && (identifica_operador(expressao[index_num-2])) && (expressao[index_num-1] == '-')){
    numero = determina_numero(index_num, casas);
    numero=numero*(-1);
    pilha_operadores[i_p_operadores-1] = '\0';
    i_p_operadores--;
  }
  
  else if(((index_num-1) == 0) && (expressao[index_num-1] == '-')){
    numero = determina_numero(index_num, casas)*(-1);
    pilha_operadores[i_p_operadores-1] = '\0';
    i_p_operadores--;
  }
  else{
    
    numero = determina_numero(index_num, casas);
  }
  
  pilha_numeros[i_p_numeros] = numero;
  
  i_p_numeros++;
}

int determina_numero(int index, int casas){
  int m; 
  int n = 0;
  char string[casas];
  int numero;
  int fim = casas+index+1;
  
  for (m = index; m < fim; m++){
    string[n] = expressao[m];
    n++;
  }

  numero = atoi(string);
  return numero;
  
}

int tem_parenteses(char c){
  if (c == '('){
    adiciona_operador();
    return TRUE;
  }
  else if (c == ')'){
    if(expressao[i_expressao-3] != '('){
      while(pilha_operadores[i_p_operadores-1] != '('){
        faz_conta();
      }
      i_expressao++;
      pilha_operadores[i_p_operadores-1] = '\0';
      i_p_operadores--; // Tirar "(" da pilha
      return TRUE;
    }
    i_expressao++;
    pilha_operadores[i_p_operadores-1] = '\0';
    i_p_operadores--;
    return TRUE;
  }
  else{
    return FALSE;
  }
}

int e_operador(char c){
  if ((c == '+') || (c == '-') || (c == '*') || (c == '/')){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

int identifica_operador(char c){
  if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')')){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

void adiciona_operador(){
  pilha_operadores[i_p_operadores] = expressao[i_expressao];
  i_p_operadores++;
  i_expressao++;
}

int operacao(char x, int a, int b){
  int resultado;
  switch (x) {
    case '+':
      resultado = a+b;
      break;

    case '-':
      resultado = a-b;
      break;

    case '*':
      resultado = a*b;
      break;

    case '/':
      if(b == 0){
        printf("\nNão é possível dividir por 0!\n");
        exit(EXIT_FAILURE);
      }
      resultado = a/b;
      break;

    default:
    resultado = FALSE;
  }

  return resultado;
}

int faz_conta(){
  int result;
  int a, b;
  char c;

  if((verifica()) && (i_p_numeros >= 2) && (i_p_operadores >= 1) && (i_expressao <= quant)){
      c = pilha_operadores[(i_p_operadores-1)];
      a = pilha_numeros[i_p_numeros-2];
      b = pilha_numeros[i_p_numeros-1];
      result = operacao(c, a, b);
      pilha_numeros[i_p_numeros-2] = result;
      i_p_numeros--;
      pilha_operadores[i_p_operadores-1] = '\0';
      i_p_operadores--;
      return TRUE;
  }
  else{
    return FALSE;
  }
}

int verifica(){

  if(i_expressao == quant){
    return TRUE; // acabou a expressão
  }

  if(pilha_operadores[i_p_operadores-1] == '('){
    return FALSE;
  }
  
  if(expressao[i_expressao] == ')'){
    return TRUE;
  }
  
  if (((expressao[i_expressao-1] == '*') || (expressao[i_expressao-1] == '/')) && ((expressao[i_expressao] == '-'))){ 
    return FALSE;
  }
  
  if((expressao[i_expressao] == '+') || (expressao[i_expressao] == '-')) {
    return TRUE;
  }
    
  if (((pilha_operadores[i_p_operadores-1] == '*') || (pilha_operadores[i_p_operadores-1] == '/')) && ((expressao[i_expressao] == '+') || (expressao[i_expressao] == '-') || (expressao[i_expressao] == '*') || (expressao[i_expressao] == '/'))){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

void printa_pilha_int (int *pilha_int){
  printf("\n printando pilha");
  for (int a = 0; a < quant; a++){
    printf("\n %d = %d", a, pilha_int[a]);
  }
}

void printa_pilha_char (char *pilha_char){
  printf("\n printando pilha");
  for (int a = 0; a < quant; a++){
    printf("\n %d = %c", a, pilha_char[a]);
  }
}