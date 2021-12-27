#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "io.h"
#include "time.h"
#include "coloring.h"
int main(int argc,char *argv[]){
  // structure to account for the time
  struct rusage *resources= malloc(sizeof(struct rusage));
  // auxiliar struct to get algorithm information
  algorithm_time* algo_time= new_algorithm_time();
  FILE* fin = NULL,*fout=stdout;

  entryRead(argc,argv,&fin,&fout);// Open input file and set IMPLEMENTATION
  graph *g= getGraphFromFile(fin);
  if(DEBUG){
    fprintf(fout,"Max degree: %d\n",maxDegree(g));
    //printGraph(g);
    //degreeSort(g);
    //printGraph(g);
    time_count(resources,START,algo_time);
  }
  int aux;// getchar() auxiliar
  bool HaveImplementation=false;
  do{
    switch(IMPLEMENTATION){
    case 'b':
      fprintf(fout,"Colors: %d\n",coloringBranchnBound(g));
      HaveImplementation=true;
      break;
    case 'd':
      fprintf(fout,"Colors: %d\n",coloringDSatur(g));
      HaveImplementation=true;
      break;
    case 'r':
      fprintf(fout,"Colors: %d\n",coloringRLF(g));
      HaveImplementation=true;
      break;
    case 'a':
      fprintf(fout,"Branch and bound: %d\n",coloringBranchnBound(g));
      fprintf(fout,"DSatur: %d\n",coloringDSatur(g));
      fprintf(fout,"RLF: %d\n",coloringRLF(g));
      HaveImplementation=true;
      break;
    default:
      printf("Choose one implementation\n[b] Branch and bound\n[d] DSatur\n[r] RLF\n[a] All\n");
      IMPLEMENTATION = getchar();
      while ((aux = getchar()) != '\n' && aux != EOF);
    }
  }while(!HaveImplementation);
  if(DEBUG){
    time_count(resources,STOP,algo_time);
    printAlgorithmTime(algo_time,fout);
  }
  //free
  freeGraph(g);
  free_algorithm_time(algo_time);
  free(resources);
  fclose(fin);
  fclose(fout);
}
