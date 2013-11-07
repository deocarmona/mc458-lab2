#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


//Programa que gera os testes aleatórios

int main(int argc, char *argv[]){

	FILE *saida;
	//abre arquivo pra leitura;

 int m, n;
 int i,j;
 int S, c;
 int Cc, Cr, Cd, Ci, Ct, Ck;
 char aux;

	char *vetorx;
	char *vetory;
	
	//Para cada combinação de parametros ele executa uma vez
for (c=1;c<4;c++){
		if (c==1) {
			S =0;
			Cc=1, Cr=1, Cd=1, Ci=1, Ct=1, Ck=1;
		}
		else if(c==2){
			S =0;
			Cc=2, Cr=2, Cd=1, Ci=3, Ct=1, Ck=1;
		}else{
			S =0;
			Cc=3, Cr=5, Cd=2, Ci=3, Ct=2, Ck=1;
			
		}
		//faz para diferentes valores de entradas
while(S<5000){
	 char str1[] = "Saida/ins.";
 	 char str2[] = ".txt";
	 char S1[5];
 		char c1[5];
		S = S + 50;
		
		//-----arrumando o nome do arquivo de saida-----//
		sprintf(S1, "%d", S);
		sprintf(c1, "%d", c);  
		strcat(str1, S1);
		strcat(str1, ".");
		strcat(str1, c1);
		strcat(str1,str2);
		saida = fopen(str1, "w");
		
		//----------------------------------------------//
		
for (j=0;j<5;j++){
	//criando os pares (m,n)
	m = rand()%S;
	n = S - m;
	vetorx = (char*) malloc (m*sizeof(char));
	vetory = (char*) malloc (n*sizeof(char));
		
  for (i=0;i<m;i++){
  	aux = (char) (97 + rand()%26);
  	//vai colocando os valores no vetor
		vetorx[i] = aux;
	}

	for (i=0;i<n;i++){
		aux = (char) (97 + rand()%26);
  	//vai colocando os valores no vetor
		vetory[i] = aux;
	}

	fprintf(saida,"%d %d\n",m,n);
	
	// Testando se a leitura está correta
	 for (i=0;i<m;i++){
			fprintf(saida,"%c",vetorx[i]);
			printf("%c",vetorx[i]);
	}
	printf("\n");
	fprintf(saida,"\n");
	for (i=0;i<n;i++){
			fprintf(saida,"%c",vetory[i]);
			printf("%c",vetory[i]);
	}

	printf("\n");
	printf("%d %d %d %d %d %d", Cc, Cr, Cd, Ci, Ct, Ck);
	printf("\n");
	
	fprintf(saida,"\n");	
	fprintf(saida,"%d %d %d %d %d %d", Cc, Cr, Cd, Ci, Ct, Ck);
	fprintf(saida,"\n");

	free(vetorx);
	free(vetory);


}
	fclose(saida);
}
}
	return 0;
	
}
