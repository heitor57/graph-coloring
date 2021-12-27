#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "io.h"


struct graph{
  int v_qnt;// vertexes
  weightType **adj;// table of edges
};

void cleanVertexList(vertex *v,int n){
  for(int i=0;i<n;i++){
    v[i].label=INVALID;
    v[i].degree=0;
  }
}

void falseVector(bool *v,int n){
  for(int i=0 ;i<n;i++)
    v[i]=false;
}

graph* newGraph(int v_qnt){
  graph *g = malloc(sizeof(graph));
  g->v_qnt = v_qnt;
  g->adj= malloc(v_qnt*sizeof(weightType*));
  for(int i=0;i<v_qnt;i++)
    g->adj[i]= calloc(v_qnt,sizeof(weightType));
  return g;
}

void freeGraph(graph* g){
  for(int i=0;i<g->v_qnt;i++)
    free(g->adj[i]);
  free(g->adj);
  free(g);
}

weightType getEdge(graph* g,int v1,int v2){
  return g->adj[v1][v2];
}

int getVQnt(graph* g){
  return g->v_qnt;
}

void insertEdge(graph* g,int v1,int v2){
  g->adj[v1][v2] = true;
  g->adj[v2][v1] = true;//symmetry
}

vertex higherDegree(vertex *v,int n){
  vertex vmax= {.label=INVALID,.degree=INVALID};
  for(int i=0;i<n;i++)
    if(v[i].label != INVALID && v[i].degree>vmax.degree){
      vmax.degree = v[i].degree;
      vmax.label = v[i].label;
    }
  return vmax;
}

// maxDegree of a graph, results analysis
int maxDegree(graph *g){
  int i,j,maxDegree=0,tempDegree;
  for(i = 0;i<g->v_qnt;i++){
    tempDegree=0;
    for(j = 0;j<g->v_qnt;j++)
      if(g->adj[i][j])// could be tempDegree+=g->adj[i][j]
	tempDegree++;
    if(tempDegree>maxDegree)
      maxDegree=tempDegree;
  }
  return maxDegree;
}


// only for test, O(n^3) because of memcpy with graph
void degreeSort(graph *g){
  vertex *vertexList = calloc(g->v_qnt,sizeof(vertex)),
    *aux=malloc(sizeof(vertex));
  int i,j;

  // calculate degree of all vertices
  for(i = 0;i<g->v_qnt;i++){
    vertexList[i].label = i;
    for(j = 0;j<g->v_qnt;j++){
      if(g->adj[i][j] == 1)
	vertexList[i].degree++;
    }
  }

  weightType *Vadj=malloc(g->v_qnt*sizeof(weightType));
  int end = g->v_qnt-1;
  bool exit = false;
  while(!exit){
    exit=true;
    for(i=0; i<end; i++){
      if(vertexList[i+1].degree<vertexList[i].degree){
	memcpy(aux,vertexList+i+1,sizeof(vertex));
	memcpy(vertexList+i+1,vertexList+i,sizeof(vertex));
	memcpy(vertexList+i,aux,sizeof(vertex));
	memcpy(aux,g->adj[i+1],sizeof(weightType)*g->v_qnt);
	memcpy(g->adj[i+1],g->adj[i],sizeof(weightType)*g->v_qnt);
	memcpy(g->adj[i],aux,sizeof(weightType)*g->v_qnt);
	exit=false;
      }
    }
    end--;
  }
  free(Vadj);
  free(aux);
  free(vertexList);
}
