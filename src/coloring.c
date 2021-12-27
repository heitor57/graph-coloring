#include <stdlib.h>
#include <string.h>
#include "coloring.h"
#include "io.h"

int min(int a, int b) {
  return a<b?a:b;
}

void computeDegree(graph *g,vertex* vertexList){
  int i,j;
  for(i = 0;i<getVQnt(g);i++){
    vertexList[i].label = i;
    for(j = 0;j<getVQnt(g);j++){
      if(getEdge(g,i,j) == 1)
	vertexList[i].degree++;
    }
  }
}

bool checkSolution(graph *g,int *colors){
  for(int i=0;i<getVQnt(g);i++){
    for(int j=0;j<getVQnt(g);j++){
      if(getEdge(g,i,j) && colors[i] == colors[j]){
	return false;
      }
    }
  }
  return true;
}

void bubbleSortV(vertex* vertexList,int n){
  vertex *aux=malloc(sizeof(vertex));
  int end = n-1,i;
  bool exit = false;
  while(!exit){
    exit=true;
    for(i=0; i<end; i++){
      if(vertexList[i+1].degree<vertexList[i].degree){
	memcpy(aux,vertexList+i+1,sizeof(vertex));
	memcpy(vertexList+i+1,vertexList+i,sizeof(vertex));
	memcpy(vertexList+i,aux,sizeof(vertex));
	exit=false;
      }
    }
    end--;
  }
  free(aux);
}

int colorsUsed(int *colors,int n){
  bool hasColor[n];
  int i,count=0;
  for(i=0;i<n;i++)
    hasColor[i]=false;
  for(i=0;i<n;i++)
    if(colors[i] > 0)
      hasColor[colors[i]-1]= true; 
  for(i=0;i<n;i++)
    if(hasColor[i])
      count++;
  return count;
}

bool adjNotSameColor(graph *g, int *colors,int color,int vertex){
  for(int i = 0;i<getVQnt(g);i++)
    if(getEdge(g,vertex,i) == true && color == colors[i])
      return false;
  return true;
}

int coloringBranchnBound(graph *g){
  int *colors = calloc(getVQnt(g),sizeof(int));
  int *colors_count = calloc(getVQnt(g),sizeof(int));
  int *max_color = malloc(sizeof(int));
  *max_color = min(coloringDSatur(g),coloringRLF(g));
  coloringBranchnBoundR(g,colors,colors_count,max_color,0,0);
  int result = *max_color;
  free(colors_count);
  free(colors);
  free(max_color);
  return result;
}

int coloringBranchnBoundR(graph *g,int *colors,int *colors_count,int *max_color,int vertex,int colorsUsed){
  int result;
  if(*max_color<=colorsUsed)
    return *max_color;
  for(int c = 1; c<=getVQnt(g); c++){
    if(adjNotSameColor(g,colors,c,vertex)){
      colors[vertex] = c;	/* color vertex 'vertex' with c */
      if(c > colorsUsed)	/* update number of colors used */
	colorsUsed = c;
      if(vertex+1 < getVQnt(g)){	/* check if is the last vertex */
	result=coloringBranchnBoundR(g,colors,colors_count,max_color,vertex+1,colorsUsed);
	if(result != 0 && result<*max_color)
	  *max_color=result;
      }else
	return colorsUsed;
    }
  }
  return *max_color;
}

int coloringDSatur(graph *g){
  int *saturation=calloc(getVQnt(g),sizeof(int)),
    *colors=calloc(getVQnt(g),sizeof(int));// colors
  vertex *vertexList = calloc(getVQnt(g),sizeof(vertex));
  int i,j;
  computeDegree(g,vertexList);
  // bubble sort in vertexes by degree, small first
  bubbleSortV(vertexList,getVQnt(g));
  // set color to vertex with max degree
  colors[vertexList[getVQnt(g)-1].label]=1;
  // update saturation
  for(i=0; i<getVQnt(g); i++)
    if(i != vertexList[getVQnt(g)-1].label && getEdge(g,vertexList[getVQnt(g)-1].label,vertexList[i].label)){
      saturation[i]++;
    }
  /* for(i=0; i<getVQnt(g); i++) */
  /*   if (DEBUG) printf("%d %d\n",vertexList[i].degree,saturation[i]); */
  bool *adjHasColor=malloc(getVQnt(g)*sizeof(bool));
  int maxSat,vertexLabel,normalVertexLabel;
  // while not readed all vertexes
  for(i=0; i<getVQnt(g); i++){
    maxSat=-1;
    /* get vertex with higher saturation and the higher degree secondarily */
    /* consequence of the ordination */
    for(j=0; j<getVQnt(g); j++){
      if(saturation[j] >= maxSat){
	maxSat = saturation[j];
	vertexLabel = j;
	normalVertexLabel = vertexList[vertexLabel].label;
      }
    }
    falseVector(adjHasColor,getVQnt(g));
    // adj colors vector
    for(j=0;j<getVQnt(g);j++)
      if(colors[j] > 0 && getEdge(g,normalVertexLabel,j))
	adjHasColor[colors[j]-1]= true; 
    // color the vertex
    for(j=0;j<getVQnt(g);j++)
      if(!adjHasColor[j]){
	colors[normalVertexLabel] = j+1;
	break;
      }
    // update saturation
    for(j=0; j<getVQnt(g); j++)
      if(saturation[j] != INVALID &&//INVALID then j is removed
	 j != normalVertexLabel &&
	 getEdge(g,normalVertexLabel,vertexList[j].label))
	saturation[j]++;
      
    saturation[vertexLabel]=INVALID;// remove vertex
  }
  int result=colorsUsed(colors,getVQnt(g));
  
  if(CHECKSOLUTION) printf("%s\n",checkSolution(g,colors)?"Correct solution":"Incorrect solution");
// compute degree
  free(adjHasColor);
  free(vertexList);
  free(saturation);
  free(colors);
  return result;
}

int coloringRLF(graph *g){
  /* graph* gind= memcpy(g,0,sizeof(vertex)); */
  int *colors = calloc(getVQnt(g),sizeof(int)),i,j;
  vertex *vertexList = calloc(getVQnt(g),sizeof(vertex)),
    *U1 = malloc(getVQnt(g)*sizeof(vertex)),
    *U2 = malloc(getVQnt(g)*sizeof(vertex));
  // calculate degree of all vertices
  computeDegree(g,vertexList);

  vertex ChosenVertex;
  int c=1,remainingVertex = getVQnt(g);
  while(remainingVertex>0)
  {
    // vertice with higher degree
    ChosenVertex=higherDegree(vertexList,getVQnt(g));
    cleanVertexList(U1,getVQnt(g));
    cleanVertexList(U2,getVQnt(g));
    // define the U1 and U2 sets
    for(i=0;i<getVQnt(g);i++)
      if(vertexList[i].label!=INVALID){
	if(!getEdge(g,ChosenVertex.label,i)){
	  U1[i].label=i;
	}else{
	  U2[i].label=i;
	}
      }
    // degree of U1 ref to U2 vertices
    for(i=0;i<getVQnt(g);i++)
      if(U1[i].label!=INVALID)
	for(j=0;j<getVQnt(g);j++)
	  if(U2[j].label!=INVALID && getEdge(g,U1[i].label,U2[j].label))
	    U1[i].degree++;
    bubbleSortV(U1,getVQnt(g));
    // color and remove vertices
    for(i=0;i<getVQnt(g);i++)
      if(U1[i].label!=INVALID){
	// check if a adj vertice will going to be the same color and remove
	for(j=0;j<getVQnt(g);j++)
	  if(U1[j].label!=INVALID && getEdge(g,U1[i].label,U1[j].label)){
	    U2[U1[j].label].label=U1[j].label;
	    U1[j].label = INVALID;
	    // could be updated the degree here but it cost
	  }
	colors[U1[i].label]=c;//color U1[i].label
	vertexList[U1[i].label].label = INVALID;//remove U1[i].label
	vertexList[U1[i].label].degree = INVALID;
	remainingVertex--;
	// loop to decrement the degree of adjacent vertices of removed vertice
	for(j=0;j<getVQnt(g);j++)
	  if(vertexList[j].label!=INVALID && getEdge(g,U1[i].label,vertexList[j].label))
	    vertexList[j].degree--;
      }
    c++;
  }
  if(CHECKSOLUTION) printf("%s\n",checkSolution(g,colors)?"Correct solution":"Incorrect solution");
  free(U1);
  free(U2);
  free(colors);
  free(vertexList);
  return c-1;
}
