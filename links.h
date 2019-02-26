/*Este arquivo descreve as funcoes que implementam os links de comunicacao
no mpsoc hemps. As funcoes detalhadas estao no arquivo links.c.
Encontra-se anexo a plataforma hemps no caminho hemps/hemps8.5/software/modules
*/

#ifndef  LINKS_H
#define  LINKS_H

#define ROTX 4
#define ROTY 4
#define N_TASKS 5

//links

int linkD[ROTX-1][ROTY];   //   para a DIREITA
int linkE[ROTX-1][ROTY];   //   para a ESQUERDA
int linkC[ROTX][ROTY-1];   //   para CIMA
int linkB[ROTX][ROTY-1];   //   para BAIXO

//funcoes 

void iniciarLinks(int, int); //funcao que inicializa os links com peso 0
void adicionarPeso(int, int, int, int, int); //adiciona peso de comunicacao nos links
void removerPeso(int, int, int, int, int); //remove peso de comunicacao nos links
int calcularPeso(int, int, int, int); //calcula o peso de comunicacao em um caminho de uma tarefa a outra

//funcoes para 'printar' pesos
void printLinkD(int, int);
void printLinkE(int, int);
void printLinkC(int, int);
void printLinkB(int, int);


#endif  /*LINKS_H*/
