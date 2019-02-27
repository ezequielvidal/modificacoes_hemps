/*Este arquivo apenas mostra de forma mais rapida a estrutura do codigo das heuristicas.
Estes codigos estão implementados dentro do mpsoc hemps no arquivo resource_manager.c(hemps/hemps8.5/software/modules), 
que foi modificado para receber as heuristicas. O código usa variaveis ja criadas na hemps, e para entender melhor o código
deve-se fazer um estudo bem detalhado da mesma.
Mais detalhes sobre as heuristicas estao nos artigos anexados ao repositorio no github
**Cabe ressaltar que estas heurísticas originais são de autoria de Ewerson Carvalho(ewerson.carvalho@gmail.com), e que 
aparecem aqui já adaptadas às variáveis e particularidades da plataforma HeMPS.*/

//ARQUIVO DEMONSTRATIVO


// heuristica FF - mapeia tarefa para o primeiro EP livre

int ff(int task_id){
	int proc_address;
	int canditate_proc = -1;
	for(int i=0; i<MAX_CLUSTER_SLAVES; i++){
		proc_address = get_proc_address(i);
		if (get_proc_free_pages(proc_address) > 0){
			canditate_proc = proc_address;
			if (canditate_proc != -1){
				puts("Task mapping for task "), puts(itoa(task_id)); puts(" maped at proc "); puts(itoh(canditate_proc)); puts("\n");
				return canditate_proc;
			}
			putsv("WARNING: no resources available in cluster to map task ", task_id);
			return -1;
		}
	}
}


// heuristica NN - mapeia a tarefa para o primeiro EP livre em um caminho circular a tarefa mestre, ou seja, a primeira mapeada

int nn(int task_id, int x_Taskmestre, int y_Taskmestre){

	int proc_address;
	int canditate_proc = -1;
	int ROTX=XCLUSTER;   //X E Y DO CLUSTER, ARQUIVO kernel_pkg.h da HeMPS, em cada aplicacao, (hemps/hemps8.5/testcases/example/include)
	int ROTY=YCLUSTER;
	int begin, end;
   	int primeiravez;
   	int esquerda, direita;
   	int XMASTER, YMASTER;
   	int z;
   	int tam;
   	int vetX[2][2*ROTX];
   	int vetY[2][2*ROTX];
   	int *sX;
   	int *sY;
   	int pt;
   	int *tX;
   	int *tY;
   	int *aX;
   	int *aY;
   	int tmpX, tmpY;

	XMASTER = x_Taskmestre;
   	YMASTER = y_Taskmestre;
   	vetX[0][0] = XMASTER;
   	vetY[0][0] = YMASTER;
   	sX = &vetX[0][0];
   	sY = &vetY[0][0];
   	tX = &vetX[1][0];
   	tY = &vetY[1][0];
   	primeiravez=1;
   	esquerda = 1;
   	direita = 1;;
   	tam = 0;
   	begin=1;
   	end=1;
	
	while(1){
	      	// inicial, somente o endereço do mestre está na fila
		if(primeiravez){
			primeiravez=0;
		 	pt=0;
			if(sX[0]>0){           //verifica se tem alguem na esquerda
		    		tX[pt] = sX[0]-1;
		    		tY[pt] = sY[0];
		    		pt++;
			}
			else{
				esquerda = 0;
			}
			if(sY[0]<ROTY-1){     //verifica se tem alguem acima
		    		tX[pt] = sX[0];
		    		tY[pt] = sY[0]+1;
		    		pt++;
			}
			if(sY[0]>0){          //verifica se tem alguem abaixo
		    		tX[pt] = sX[0];
		    		tY[pt] = sY[0]-1;
		    		pt++;
		 	}
		 	if(sX[0]<ROTX-1){     //verifica se tem alguem a direita
		    		tX[pt] = sX[0]+1;
		    		tY[pt] = sY[0];
		    		pt++;
		 	}
		 	else{
		    		direita = 0;
		 	}
	      	}
	      	//senão
	      	else{
		 	// primeiro
		 	pt=0;
		 	if(esquerda){                //verifica se tem alguem na esquerda
		    		if(sX[0]>0){
		       			tX[pt] = sX[0]-1;tY[pt] = sY[0]; pt++;
		    		}
		    		else{
		       		esquerda = 0;
		    		}
		    		if(sY[0]<ROTY-1){         //verifica se tem alguem acima
		       			tX[pt] = sX[0]; tY[pt] = sY[0]+1; pt++;
		    		}
		    		if(sY[0]>0){              //verifica se tem alguem abaixo
		       			tX[pt] = sX[0]; tY[pt] = sY[0]-1; pt++;
		    		}
			}

		 	// meio
		 	for(z=begin; z<tam-end; z++){
		    		if((sY[z]>YMASTER)&&(sY[z]<ROTY-1)){
		       			tX[pt] = sX[z]; tY[pt] = sY[z]+1; pt++;
		    		}
		    		else{
		       			if((sY[z]<YMASTER)&&(sY[z]>0)){
		          			tX[pt] = sX[z]; tY[pt] = sY[z]-1; pt++;
		       			}
		       			else{
		         			if(sY[z]==YMASTER){
		             				tX[pt] = sX[z]; tY[pt] = sY[z]-1; pt++;
		             				tX[pt] = sX[z]; tY[pt] = sY[z]+1; pt++;
		          			}
		       			}
		    		}
		 	}
		 	// ultimo
		 	if(direita){
		    		if(sY[tam-1]<ROTY-1){
		       			tX[pt] = sX[tam-1]; tY[pt] = sY[tam-1]+1; pt++;
		    		}
		    		if(sY[tam-1]>0){
		       			tX[pt] = sX[tam-1]; tY[pt] = sY[tam-1]-1; pt++;
		    		}
		    		if(sX[tam-1]<ROTX-1){
		       			tX[pt] = sX[tam-1]+1; tY[pt] = sY[tam-1]; pt++;
		    		}
		    		else{
		       			direita = 0;
		    		}
		 	}
	      	}
	      	begin = esquerda;
	      	end = direita;
	      	tam = pt;
	      	aX = tX;
	      	aY = tY;
	      	tX = sX;
	      	tY = sY;
	      	sX = aX;
	      	sY = aY;

	      	if(!tam){
			puts("ERRO SNN - Posicionador SNN não achou ninguém \n");
		 	return -1; //returna -1
	      	}
	      	for(z=0; z<tam; z++){
			tmpX = aX[z];
			tmpY = aY[z];
		    	proc_address = tmpX*256 + tmpY;//cria o endereço de processador
		    	if ( proc_address != 0  &&  get_proc_free_pages(proc_address) > 0){
				canditate_proc = proc_address;

				puts("Mapeam. para tarefa "), puts(itoa(task_id)); puts(" mapeada no processador "); puts(itoh(canditate_proc)); puts("\n");
				return canditate_proc; //retorna o endereço do processador selecionado
		 	}
	      	}
	}	
}

// heuristica PL - usa a mesma logica de FF, mapeia no primeiro livre. Porem, esta otimiza o peso de comunicacao nos canais

int pl(int task_id, int Xmestre, int Ymestre){    
	int proc_address;
	int canditate_proc = -1;
	int pesoTmp;
	int peso=999999;
	int x,y;
	
	for(int i=0; i<MAX_CLUSTER_SLAVES; i++){
		proc_address = get_proc_address(i);
		x = proc_address >> 8;
		y = proc_address & 0xFF;

		if (get_proc_free_pages(proc_address) > 0){
			pesoTmp = calcularPeso(Xmestre, Ymestre, x, y);
            		if(pesoTmp < peso){
               			peso = pesoTmp;
				canditate_proc = proc_address;
            		}
		}
	}	
	if (canditate_proc != -1){
		puts("Mappeam. tarefa "), puts(itoa(task_id)); puts(" maped no proc "); puts(itoh(canditate_proc)); puts("\n");
		return canditate_proc;
	}
	putsv("WARNING: no resources available in cluster to map task ", task_id);
	return -1;			
}


// heuristica BN - combina as estratégias das heuristicas NN e PL


int bn(int task_id, int x_Taskmestre, int y_Taskmestre){

	int proc_address;
	int canditate_proc = -1;
	int pesoTmp;
	int peso;
	int n_holps;
	int ROTX=XCLUSTER;   //X E Y DO CLUSTER, ESTAO NO ARQUIVO kernel_pkg.h da HeMPS
	int ROTY=YCLUSTER;
	int begin, end;
   	int primeiravez;
   	int esquerda, direita;
   	int XMASTER, YMASTER;
   	int z;
   	int tam;
   	int vetX[2][2*ROTX];
   	int vetY[2][2*ROTX];
   	int *sX;
   	int *sY;
   	int pt;
   	int *tX;
   	int *tY;
   	int *aX;
   	int *aY;
   	int tmpX, tmpY;

	XMASTER = x_Taskmestre;
   	YMASTER = y_Taskmestre;
   	vetX[0][0] = XMASTER;
   	vetY[0][0] = YMASTER;
   	sX = &vetX[0][0];
   	sY = &vetY[0][0];
   	tX = &vetX[1][0];
   	tY = &vetY[1][0];
   	primeiravez=1;
   	esquerda = 1;
   	direita = 1;;
   	tam = 0;
   	begin=1;
   	end=1;
	peso = 999999;
   	n_holps = 0;
	
	while(1){
	      	// inicial
		if(primeiravez){
			primeiravez=0;
		 	pt=0;
			if(sX[0]>0){           //verifica se tem alguem na esquerda
		    		tX[pt] = sX[0]-1;
		    		tY[pt] = sY[0];
		    		pt++;
			}
			else{
				esquerda = 0;
			}
			if(sY[0]<ROTY-1){     //verifica se tem alguem acima
		    		tX[pt] = sX[0];
		    		tY[pt] = sY[0]+1;
		    		pt++;
			}
			if(sY[0]>0){          //verifica se tem alguem abaixo
		    		tX[pt] = sX[0];
		    		tY[pt] = sY[0]-1;
		    		pt++;
		 	}
		 	if(sX[0]<ROTX-1){     //verifica se tem alguem a direita
		    		tX[pt] = sX[0]+1;
		    		tY[pt] = sY[0];
		    		pt++;
		 	}
		 	else{
		    		direita = 0;
		 	}
	      	}
	      	// senao
	      	else{
		 	// promeiro
		 	pt=0;
		 	if(esquerda){                //verifica se tem alguem na esquerda
		    		if(sX[0]>0){
		       			tX[pt] = sX[0]-1;tY[pt] = sY[0]; pt++;
		    		}
		    		else{
		       		esquerda = 0;
		    		}
		    		if(sY[0]<ROTY-1){         //verifica se tem alguem acima
		       			tX[pt] = sX[0]; tY[pt] = sY[0]+1; pt++;
		    		}
		    		if(sY[0]>0){              //verifica se tem alguem abaixo
		       			tX[pt] = sX[0]; tY[pt] = sY[0]-1; pt++;
		    		}
			}

		 	// meio
		 	for(z=begin; z<tam-end; z++){
		    		if((sY[z]>YMASTER)&&(sY[z]<ROTY-1)){
		       			tX[pt] = sX[z]; tY[pt] = sY[z]+1; pt++;
		    		}
		    		else{
		       			if((sY[z]<YMASTER)&&(sY[z]>0)){
		          			tX[pt] = sX[z]; tY[pt] = sY[z]-1; pt++;
		       			}
		       			else{
		         			if(sY[z]==YMASTER){
		             				tX[pt] = sX[z]; tY[pt] = sY[z]-1; pt++;
		             				tX[pt] = sX[z]; tY[pt] = sY[z]+1; pt++;
		          			}
		       			}
		    		}
		 	}

		 	// ultimo
		 	if(direita){
		    		if(sY[tam-1]<ROTY-1){
		       			tX[pt] = sX[tam-1]; tY[pt] = sY[tam-1]+1; pt++;
		    		}
		    		if(sY[tam-1]>0){
		       			tX[pt] = sX[tam-1]; tY[pt] = sY[tam-1]-1; pt++;
		    		}
		    		if(sX[tam-1]<ROTX-1){
		       			tX[pt] = sX[tam-1]+1; tY[pt] = sY[tam-1]; pt++;
		    		}
		    		else{
		       			direita = 0;
		    		}
		 	}
	      	}
	      	begin = esquerda;
	      	end = direita;
	      	tam = pt;
	      	aX = tX;
	      	aY = tY;
	      	tX = sX;
	      	tY = sY;
	      	sX = aX;
	      	sY = aY;

	      	if(!tam){
			puts("ERRO SNN - Posicionador SNN não achou ninguém \n");
		 	return -1; //retorna -1
	      	}
		n_holps++;
	      	for(z=0; z<tam; z++){
			tmpX = aX[z];
			tmpY = aY[z];
			proc_address = tmpX*256 + tmpY;//cria o endereço do processador
		    	if (proc_address != 0  &&  get_proc_free_pages(proc_address) > 0){
				pesoTmp = calcularPeso(x_Taskmestre, y_Taskmestre, tmpX, tmpY);
            			if(pesoTmp < peso){
               				peso = pesoTmp;
					canditate_proc = proc_address;
            			}
		 	}
	      	}
      		if((n_holps>1)&&(peso<99999)) break;		    	
	}
	puts("Mapeam. para tarefa "), puts(itoa(task_id)); puts(" mapeada no processador "); puts(itoh(canditate_proc)); puts("\n");
	return canditate_proc;
}
//-----------------------------------------------------------------------------------------------------------------------------------
//fim--------------------------------------------------------------------------------------------------------------------------------

