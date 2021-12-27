/* Sintaxe:

   <programa_executavel> <numero de grafos> <total de vertices> <total de arestas> <fout>

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[ ]){
  srand(time(NULL));
if(argc != 5){
  printf("Parametros incorretos. Use os parametros: "
	 "<numero de grafos> <total de vertices> <total de arestas> <fout>\n");
  return -1;
}

/*usage: m arestas, n vertices, ng grafos */
/* i,j,k,aux1 e aux2 sao variaveis auxiliares */
/* max Ã© o tamanho max do vetor */

FILE* fp;
fp = fopen(argv[4], "w");

int m,n,ng,i,j,max,k,aux1,aux2;

ng=atoi(argv[1]);
n=atoi(argv[2]);
m=atoi(argv[3]);
//scanf("%d %d %d",&ng,&n,&m);
max=n*(n-1)/2;
if (m>max) {
  m = max;
  fprintf(stderr,
	  "Numero de arestas superior ao maximo permitido, atribuido %d.\n",
	  max);
}
printf("%d %d %d\n",ng,n,m);

int vetor_i[max+1];
int vetor_j[max+1];

k=0;
for(i=0;i<n-1;i++){

	for(j=i+1;j<n && j!=i;j++){ // A aresta (i,j) Ã© guardada na posicao vetor_i[k] e vetor_j[k]
		vetor_i[k]=i;
		vetor_j[k]=j;
		k++;
	}
}



for(k=0;k<ng;k++){ // fornece ng grafos
    j=0;

    for (i=0;i<max;i++) {
	    j=rand()%max;       // j deve receber um inteiro aleatÃ³rio do conjunto de i a w-1.

	    aux1=vetor_i[i];          //Permutacao dos elementos
	    vetor_i[i]=vetor_i[j];
	    vetor_i[j]=aux1;

	    aux2=vetor_j[i];
	    vetor_j[i]=vetor_j[j];
	    vetor_j[j]=aux2;
    }
    fprintf(fp, "%d\n", n);
    for(i=0;i<m;i++){
	    fprintf(fp, "%d %d\n",vetor_i[i],vetor_j[i]);
    }
    printf("\n");
}
fclose(fp);
return 0;
}
