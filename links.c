/*Este arquivo implementa as funcoes em links.h
Encontra-se anexo a plataforma hemps no caminho hemps/hemps8.5/software/modules
*/

#include <stdio.h>
#include <stdlib.h>

#include "links.h"


//inicializa pesos dos links com 0
//parametros: x, tamanho mpsoc em x
//parametros: y, tamanho mpsoc em y

void iniciarLinks(int x, int y){
	for(int i=0; i<x; i++){
		for(int j=0; j<y; j++){
	    		if(i<x-1){
		    		linkD[i][j]=0;
		    		linkE[i][j]=0;
		 	}
		 	if(j<y-1){
		    		linkC[i][j]=0;
		    		linkB[i][j]=0;
		 	}
	      	}
	}
}

//print do LinkD, links com direcao a direita
//parametros: x, tamanho mpsoc em x
//parametros: y, tamanho mpsoc em y
void printLinkD(int x, int y){

	for(int i=0; i<ROTX-1; i++){
		for(int j=0; j<ROTY; j++){

			printf("Peso do LinkD %dX%d: %d\n", i, j, linkD[i][j]);
		}
		printf("\n");
	}
}

//print do LinkE, links com direcao a esquerda
//parametros: x, tamanho mpsoc em x
//parametros: y, tamanho mpsoc em y
void printLinkE(int x, int y){

	for(int i=0; i<ROTX-1; i++){
		for(int j=0; j<ROTY; j++){

			printf("Peso do LinkE %dX%d: %d\n", i, j, linkE[i][j]);
		}
		printf("\n");
	}
}

//print do LinkC, links com direcao pra cima
//parametros: x, tamanho mpsoc em x
//parametros: y, tamanho mpsoc em y
void printLinkC(int x, int y){

	for(int i=0; i<ROTX; i++){
		for(int j=0; j<ROTY-1; j++){

			printf("Peso do LinkC %dX%d: %d\n", i, j, linkC[i][j]);
		}
		printf("\n");
	}
}

//print do LinkB, links com direcao pra baixo
//parametros: x, tamanho mpsoc em x
//parametros: y, tamanho mpsoc em y
void printLinkB(int x, int y){

	for(int i=0; i<ROTX; i++){
		for(int j=0; j<ROTY-1; j++){

			printf("Peso do LinkB %dX%d: %d\n", i, j, linkB[i][j]);
		}
		printf("\n");
	}
}


//adiciona pesos nos links
//parametros: xM, x da tarefa mestre
//parametros: yM, y da tarefa mestre
//parametros: xS, x da tarefa escrava
//parametros: yS, y da tarefa escrava

void adicionarPeso(int xM, int yM, int xS, int yS, int peso){
	
	if( xM < xS ){  //se o mestre esta a esquerda do escravo
		for(int i=xM; i<=xS; i++){

			if( i < xS){
				linkD[i][yM] = linkD[i][yM] + peso;
			} 		
		
			if( yM > yS ){  //se o mestre esta acima do escravo
				for(int j=yM-1; j>=yS; j--){
			
					if( i == xS ){
						 
						linkB[i][j] = linkB[i][j] + peso;
					}
				}
			}
			if( yM < yS ){  //se o mestre esta abaixo do escravo
				for(int j=yM; j<yS; j++){
			
					if( i == xS ){
						 
						linkC[i][j] = linkC[i][j] + peso;
					}
				}
			}
			
		}
	}
	if( xM > xS ){  //se o mestre esta a direita do escravo
		for(int i=xM-1; i>=xS; i--){          //ver aqui xM-1, tava dando erro

			if( i >= xS){                                  
				linkE[i][yM] = linkE[i][yM] + peso;
			} 		
		
			if( yM > yS ){  //se o mestre esta acima do escravo
				for(int j=yM-1; j>=yS; j--){
			
					if( i == xS ){
						 
						linkB[i][j] = linkB[i][j] + peso;
					}
				}
			}
			if( yM < yS ){  //se o mestre esta abaixo do escravo
				for(int j=yM; j<yS; j++){
			
					if( i == xS ){
						 
						linkC[i][j] = linkC[i][j] + peso;
					}
				}
			}
			
		}
	}
	if( xM == xS ){  //se o mestre esta no mesmo x do escravo, podendo estar acima ou embaixo
		

		if( yM > yS ){  //se o mestre esta acima do escravo
			for(int j=yM-1; j>=yS; j--){
					 
				linkB[xM][j] = linkB[xM][j] + peso;
			}
		}
		if( yM < yS ){  //se o mestre esta abaixo do escravo
			for(int j=yM; j<yS; j++){
						 
				linkC[xM][j] = linkC[xM][j] + peso;
			}
		}
			
		
	}
}


//remove pesos dos links
//parametros: xM, x da tarefa mestre
//parametros: yM, y da tarefa mestre
//parametros: xS, x da tarefa escrava
//parametros: yS, y da tarefa escrava

void removerPeso(int xM, int yM, int xS, int yS, int peso){
	
	if( xM < xS ){
		for(int i=xM; i<=xS; i++){

			if( i < xS){
				linkD[i][yM] = linkD[i][yM] - peso;
			} 		
		
			if( yM > yS ){
				for(int j=yM-1; j>=yS; j--){
			
					if( i == xS ){
						 
						linkB[i][j] = linkB[i][j] - peso;
					}
				}
			}
			if( yM < yS ){
				for(int j=yM; j<yS; j++){
			
					if( i == xS ){
						 
						linkC[i][j] = linkC[i][j] - peso;
					}
				}
			}
			
		}
	}
	if( xM > xS ){
		for(int i=xM-1; i>=xS; i--){

			if( i >= xS){
				linkE[i][yM] = linkE[i][yM] - peso;
			} 		
		
			if( yM > yS ){
				for(int j=yM-1; j>=yS; j--){
			
					if( i == xS ){
						 
						linkB[i][j] = linkB[i][j] - peso;
					}
				}
			}
			if( yM < yS ){
				for(int j=yM; j<yS; j++){
			
					if( i == xS ){
						 
						linkC[i][j] = linkC[i][j] - peso;
					}
				}
			}
			
		}
	}
	if( xM == xS ){  //se o mestre esta no mesmo x do escravo, podendo estar acima ou embaixo
		

		if( yM > yS ){  //se o mestre esta acima do escravo
			for(int j=yM-1; j>=yS; j--){
					 
				linkB[xM][j] = linkB[xM][j] - peso;
			}
		}
		if( yM < yS ){  //se o mestre esta abaixo do escravo
			for(int j=yM; j<yS; j++){
						 
				linkC[xM][j] = linkC[xM][j] - peso;
			}
		}
			
		
	}
}

//calcula o peso do caminho de um processador mestre a um processador escravo
//parametros: xM, x do processador mestre
//parametros: yM, y do processador mestre
//parametros: xS, x do processador escravo
//parametros: yS, y do processador escravo
//retona o peso do caminho

int calcularPeso(int xM, int yM, int xS, int yS){

	int pesoCaminho=0;	

	if( xM < xS ){
		for(int i=xM; i<=xS; i++){

			if( i < xS){
				pesoCaminho = pesoCaminho + linkD[i][yM];
			} 		
		
			if( yM > yS ){
				for(int j=yM-1; j>=yS; j--){
			
					if( i == xS ){
						 
						pesoCaminho = pesoCaminho + linkB[i][j];
					}
				}
			}
			if( yM < yS ){
				for(int j=yM; j<yS; j++){
			
					if( i == xS ){
						 
						pesoCaminho = pesoCaminho + linkC[i][j];
					}
				}
			}
			
		}
	}
	if( xM > xS ){
		for(int i=xM-1; i>=xS; i--){

			if( i >= xS){
				pesoCaminho = pesoCaminho + linkE[i][yM];
			} 		
		
			if( yM > yS ){
				for(int j=yM-1; j>=yS; j--){
			
					if( i == xS ){
						 
						pesoCaminho = pesoCaminho + linkB[i][j];
					}
				}
			}
			if( yM < yS ){
				for(int j=yM; j<yS; j++){
			
					if( i == xS ){
						 
						pesoCaminho = pesoCaminho + linkC[i][j];
					}
				}
			}
			
		}
	}
	if( xM == xS ){  //se o mestre esta no mesmo x do escravo, podendo estar acima ou embaixo
		

		if( yM > yS ){  //se o mestre esta acima do escravo
			for(int j=yM-1; j>=yS; j--){
					 
				pesoCaminho = pesoCaminho + linkB[xM][j];
			}
		}
		if( yM < yS ){  //se o mestre esta abaixo do escravo
			for(int j=yM; j<yS; j++){
						 
				pesoCaminho = pesoCaminho + linkC[xM][j];
			}
		}
			
		
	}
	return pesoCaminho;

}


//funcao principal para testes
/*int main(){

	iniciarLinks(ROTX, ROTY);
	adicionarPeso(1, 2, 1, 3, 50);
	adicionarPeso(0, 2, 3, 1, 10);
	adicionarPeso(3, 3, 3, 0, 30);
	adicionarPeso(1, 1, 3, 2, 65);
	
	int p = calcularPeso(3,3,3,0);
	printf("\nPeso do caminho: %d\n\n",p);

	printLinkD(ROTX, ROTY);
	printLinkE(ROTX, ROTY);
	printLinkC(ROTX, ROTY);
	printLinkB(ROTX, ROTY);
	
}
*/



