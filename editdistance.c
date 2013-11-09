#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

int valor_i_kill;
//acha a resposta certa percorrendo a matrix de custo
//T[i][j] = min 
//---- acho que essa parte ele só explica o que é T[i,j] não é codigo---
int minimo_custo(char x[], char y[],int i,int j,int m,int n,int* T[m],int Cc,int Cr,int Cd,int Ci,int Ct,int Ck){
	int del=4444, ins=4444,cop=4444, rep=4444,twid=4444,kil=4444;
	char aux;
	int k;
del = T[i - 1][j] + Cd;//Custo delete
ins = T[i][j - 1] + Ci;//custo insert

	if (x[i]==y[j]){
			cop = T[i - 1][j - 1] + Cc;//Custo copy
	}
	if (x[i] != y[j]){
			rep = T[i - 1][j - 1] + Cr;//Custo replace
		}
	if ((i>=2) && (j >= 2) && (x[i] == y[j-1]) && (x[i-1] == y[j])){
			twid = T[i - 2][j - 2] + Ct; //Custo twiddle
	}
	if ((i == m) && (j == n)){
			aux = T[0][n];		
			for (k=1;k<m;k++){
					if ( T[k][n]<aux){
							aux = T[k][n];			
						}
			}
			kil = T[k][n] + Ck;//Custo kill
	}
	//retorna o menor custo NAO SEI FAZER MELHOR
	if ((cop<=ins)&&(cop<=del)&&(cop<=rep)&&(cop<=twid)&&(cop<=kil)) return cop;
	if ((ins<=del)&&(ins<=cop)&&(ins<=rep)&&(ins<=twid)&&(ins<=kil)) return ins;
	if ((rep<=ins)&&(rep<=cop)&&(rep<=del)&&(rep<=twid)&&(rep<=kil)) return rep;
	if ((del<=ins)&&(del<=cop)&&(del<=rep)&&(del<=twid)&&(del<=kil)) return del;
	if ((twid<=ins)&&(twid<=cop)&&(twid<=rep)&&(twid<=del)&&(twid<=kil)) return twid;	
	if ((kil<=ins)&&(kil<=cop)&&(kil<=rep)&&(kil<=twid)&&(kil<=del)) return kil;
	return 0;
}

void seq_op(int i, int j, char vetory[],char* op[i],int m,int valor_i_kill){
	//o ultimo elemento da matriz não tem operador
	int aux_i, aux_j;
if (i == 0 && j == 0) 		return;
if ((op[i][j] == 'c') || (op[i][j] == 'r')){
		aux_i = i - 1;
		aux_j = j - 1;
}else if (op[i][j] == 't'){
		aux_i = i - 2;
		aux_j = j - 2;
} else if (op[i][j] == 'd'){
		aux_i = i - 1;
		aux_j = j;
} else if (op[i][j] == 'i'){
		aux_i = i;
		aux_j = j - 1;
} else if(op[i][j]=='k'){

		aux_i = valor_i_kill;
		aux_j = j;
}
	seq_op(aux_i,aux_j,vetory,op,m,valor_i_kill);

	if (op[i][j] == 'c') printf("%d %d Copy %c\n", i, j, vetory[j-1]);
	if (op[i][j] == 'r') printf("%d %d Replace %c\n", i, j, vetory[j-1]);
	if (op[i][j] == 't') printf("%d %d Twiddle %c%c\n", i, j, vetory[j-2],vetory[j-1]);
	if (op[i][j] == 'd') printf("%d %d Delete _\n", i, j);
	if (op[i][j] == 'i') printf("%d %d Insert %c\n", i, j, vetory[j-1]);
	if (op[i][j] == 'k') printf("%d %d Kill *\n", i, j);
}


void edit_distances(char x[], char y[], int m, int n,int Cc,int Cr,int Cd,int Ci,int Ct,int Ck,int* T[m],char* op[m],int valor_i_kill){
	int i;
	int j;
	//coloca custo de delete em todas as colunas 0
	for(i=1;i<m+1;i++){
			T[i][0] = Cd*i ;//Custo delete
			op[i][0] = 'd';
	}
	//coloca custo de insert em todas as linhas 0
	for(j=1;j<n+1;j++){
			T[0][j] = Ci*j;//Custo insert
			op[0][j] = 'i';
	}
	//T[0][0]=0;
	//valor_i_kill = m;
	//op[0][0]=' ';
		//percorre a matriz de custo 
	for(i=1;i<m+1;i++){
			for (j=1;j<n+1;j++){
					
					T[i][j] = minimo_custo(x, y,i,j,m,n,T,Cc,Cr,Cd,Ci,Ct,Ck);
					
					if (x[i-1] == y[j-1]){//se as letras forem iguais copia
							//T[i][j] = Cc;//T[i-1][j-1];//Custo copy
							op[i][j] = 'c';
					}else //se o custo de troca for menor
					if ((x[i-1] != y[j-1]) && ((T[i-1][j-1] + Cr) == T[i][j])){//Custo replace
							//T[i][j] = Cr;// +T[i-1][j-1];//Custo replace
							op[i][j] = 'r';//REPLACE(by y[j]);
					}else		
					//	
					if (( i >= 2) && (j >= 2) && (x[i] == y[j-1]) && 
					(x[i-1] == y[j]) && ((T[i-2][j-2] + Ct) == T[i][j])){//Custo twiddle
							//T[i][j] = Ct;//+T[i-2][j-2];//Custo twiddle
							op[i][j] = 't';
					}else
					//				
					if ((T[i-1][j] + Cd) == T[i][j]){
							//T[i][j] = Cd;//+T[i-1][j] ;//Custo delete
							op[i][j] = 'd';
					}else
					if (T[i][j-1] + Ci == T[i][j]){
							//T[i][j] = Ci;//+T[i][j-1];//Custo insert
							op[i][j] = 'i';//INSERT(y[j]);
					}

			}
	}		
	for(i=0;i<m;i++){
			if (T[i][n] + Ck < T[m][n]){
					T[m][n] = Ck+T[i][n];//Custo
					op[m][n] = 'k';//KILL(i);
					valor_i_kill = i;
			}
			
	}
	return;// T and op;
}

//apenas a funcao do programa (pros outros, apenas essa parte é diferente, o resto é igual)

		 
int main(int argc, char *argv[]){

	
	FILE *fp;	
	FILE *saida;
	//abre arquivo pra leitura;
	fp = fopen(argv[1], "r");
	if (!fp) printf ("Erro na abertura do arquivo.");
	
	saida = fopen("Distances.txt", "w");
	//int valor_i_kill;
 int m, n;
 int i,j;
	int Cc, Cr, Cd, Ci, Ct, Ck;
 char aux;

		//le do arquivo de entrada o tamanho das palavras
	
		fscanf(fp,"%d %d\n", &m, &n);
		//cria os vetores de palavras
		char *x;
		char *y;
   x = (char*) malloc ((m+1)*sizeof(char));
		y = (char*) malloc ((n+1)*sizeof(char));

		//cria as matrizes de custo e de operações
	 	int **T;
		char **op;
   T = malloc ((m+1)*sizeof(int*));
   for (i=0;i<m+1;i++){
				T[i] = (int*) malloc ((n+1)*sizeof(int));
		}
		op = malloc ((m+1)*sizeof(char*));
   for (i=0;i<m+1;i++){
				op[i] = (char*) malloc ((n+1)*sizeof(char));
		}

	//le o arquivo colocando nos vetores as palavras correspondentes
  for (i=0;i<m;i++){
  	fscanf(fp,"%c", &aux);
  	//vai colocando os valores no vetor
		x[i] = aux;
	}
	fscanf(fp,"\n");
	for (i=0;i<n;i++){
		fscanf(fp,"%c", &aux);
  	//vai colocando os valores no vetor
		y[i] = aux;
	}
		fscanf(fp,"\n");
		
		//Le do arquivo os custos de cada operação
		fscanf(fp,"%d %d %d %d %d %d\n", &Cc, &Cr, &Cd, &Ci, &Ct, &Ck);	
	
	//Começa a bomba!!!
	edit_distances(x,y,m,n,Cc,Cr,Cd,Ci,Ct,Ck,T,op, 	valor_i_kill);

	seq_op(m,n,y,op,m,valor_i_kill);
	
	
			for(i=1;i<m+1;i++){
					for (j=1;j<n+1;j++){	
							printf("%2c ", op[i][j]);
						}
						printf("\n");
					}
						printf("\n\n\n");
			for(i=0;i<m;i++){
					for (j=0;j<n;j++){	
							printf("%2d ", T[i][j]);
						}
						printf("\n");
					}
	
	//libera espaço na memória
	free(x);
	free(y);
	free(T);
	free(op);

	//fecha os arquivos abertos
	fclose(fp);
	fclose(saida);
	return 0;
}


