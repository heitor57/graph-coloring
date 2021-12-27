#ifndef IO_H
#define IO_H
#define ENOENT 2 /* No such file or directory */
#define SUCCESS 1
#define FAIL 0
#include <stdio.h>
#include <stdbool.h>
#include "time.h"
#include "graph.h"
#define error(str, ...) {\
  fprintf(stderr,(str), ##__VA_ARGS__);\
  fprintf(stderr,"\n");\
  }
extern bool DEBUG;
extern bool CHECKSOLUTION;
extern char IMPLEMENTATION;
void entryRead(int argc, char* argv[],FILE** fin,FILE** fout);
graph* getGraphFromFile(FILE *fin);
void printAlgorithmTime(const algorithm_time *algo_time,FILE* f);
void printGraph(graph *g);
#endif
