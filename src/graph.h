#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>
#define INVALID -1
typedef struct graph graph;
typedef struct vertex{
  int label,degree;
}vertex;
typedef bool weightType;
graph* newGraph(int v_qnt);
void freeGraph(graph* g);
weightType getEdge(graph* g,int v1,int v2);
int getVQnt(graph* g);
void insertEdge(graph* g,int v1,int v2);
int maxDegree(graph *g);
void degreeSort(graph *g);
void falseVector(bool *v,int n);
vertex higherDegree(vertex *v,int n);
void cleanVertexList(vertex *v,int n);
#endif
