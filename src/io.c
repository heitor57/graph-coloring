#include <getopt.h>
#include <stdlib.h>
#include "io.h"
bool DEBUG = false;
bool CHECKSOLUTION = false;
char IMPLEMENTATION = ' ';
void printUsage(){
  printf("graph-coloring -i <entry file> -o <out file> -d (DEBUG) -c (CHECK SOLUTION) -p <Implementations>\n"
    "Possible implementations\n"
    "-p b(Branch and bound) d(DSatur) r(RLF)\n"
    "-p a(All)\n"
    "Examples: graph-coloring -i in.txt -o out.txt -d -p d\n"
    "graph-coloring -i in.txt -o out.txt\n"
    "graph-coloring -i in.txt\n");
  exit(ENOENT);
}

void entryRead(int argc, char* argv[],FILE** fin,FILE** fout){
  int option;
  if(argc < 2)
  {
    printUsage();
  }
  while((option = getopt(argc,argv,"i:o:dp:c")) != -1){
    switch(option){
    case 'i':
      if(!(*fin = fopen(optarg,"r"))){
	error("Input file open error.");
	exit(ENOENT);
      }
      break;
    case 'o':
      if(!(*fout = fopen(optarg,"w"))){
	error("Output file open error.");
	exit(ENOENT);
      }
      break;
    case 'd':
      DEBUG=true;
      break;
    case 'p':
      IMPLEMENTATION= optarg[0];
      break;
    case 'c':
      CHECKSOLUTION=true;
      break;
    }
  }
}

graph* getGraphFromFile(FILE *fin){
  int v_qnt;
  fscanf(fin,"%d\n",&v_qnt);
  graph* g = newGraph(v_qnt);
  int v1,v2;
  while(!feof(fin)){
    fscanf(fin,"%d %d\n",&v1,&v2);
    if(v1 == v2){
      fprintf(stderr,"Not allowed self loop, but the program will continue not including this config. (edge %d %d)\n",v1,v2);
    }else{
      insertEdge(g,v1,v2);
    }
  }
  rewind(fin);
  return g;
}

void printAlgorithmTime(const algorithm_time *algo_time,FILE* f){
  fprintf(f,"User time %.6fs, System time %.6fs, Total Time %.6fs\n",get_utime(algo_time), get_stime(algo_time), get_total_time(algo_time));
}

void printGraph(graph *g){
  int i,j,n=getVQnt(g);
  //first line print
  printf("+---+");
  for(i=0;i<n-1;i++)
    printf("---+");
  printf("\n");
  //first line print
  for(i =0;i<n;i++){
    // Values print
    for(j = 0;j<n;j++)
      printf("| %d ",getEdge(g,i,j));
    // Values print
    // Separating bar print
    printf("|\n+---+");
    for(j=0;j<n-1;j++)
      printf("---+");
    printf("\n");
    // Separating bar print
  }
  printf("\n\n");
}
