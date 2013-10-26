#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


//apenas a funcao do programa (pros outros, apenas essa parte é diferente, o resto é igual)



int main(int argc, char *argv[]){

	FILE *fp;	
	FILE *saida;
	//abre arquivo pra leitura;
	fp = fopen(argv[1], "r");
	if (!fp) printf ("Erro na abertura do arquivo.");
	
	saida = fopen("Distances.txt", "w");

 int tam;
 int i;
 char aux;

 	//fprintf(saida,"tempos:");
	
		fscanf(fp,"%d\n", &tam);
		char *vetorx;
		char *vetory;
   vetorx = (char*) malloc (tam*sizeof(char));
		vetory = (char*) malloc (tam*sizeof(char));


  for (i=0;i<tam;i++){
  	fscanf(fp,"%c\n", &aux);
  	//vai colocando os valores no vetor
		vetorx[i] = aux;
		fscanf(fp,"%c\n", &aux);
  	//vai colocando os valores no vetor
		vetory[i] = aux;
		fscanf(fp,"\n");	
			
	}
	
	 for (i=0;i<tam;i++){
			fprintf(saida,"%c ",vetorx[i]);
			printf("%c ",vetorx[i]);
	}
	//fprintf(saida,"\n");
	for (i=0;i<tam;i++){
			fprintf(saida,"%c ",vetory[i]);
			printf("%c ",vetory[i]);
	}



	printf("\n");

	free(vetorx);
	free(vetory);


	fclose(fp);
	fclose(saida);
	return 0;
}
