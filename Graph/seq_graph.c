#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
#define VRType int 
#define InfoType char
#define VertexType int

typedef enum{DG, DN, UDG, UDN} GraphKind;

typedef struct {
  VRType adj;
  InfoType* info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
  VertexType vexs[MAX_VERTEX_NUM];
  AdjMatrix arcs;
  int vec_num;
  int arc_num;
  GraphKind kind;
} Graph;

int main() {
  
  return 0;
}
