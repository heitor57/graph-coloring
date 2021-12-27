#ifndef COLORING_H
#define COLORING_H
#include "graph.h"
int coloringBranchnBound(graph *g);
int coloringBranchnBoundR(graph *g,int *colors,int *colors_count,int *max_color,int vertex,int colorsUsed);
int coloringDSatur(graph *g);
int coloringRLF(graph *g);
#endif
