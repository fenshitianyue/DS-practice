//用邻接表实现图
#include <stdio.h>
//head

#define VERTEX_MAX 20 //图中最多包含的顶点数
typedef enum{FALSE, TRUE} Bool;

struct ArcNode{
  int adjvex; //该弧所指向的顶点的位置
  ArcNode* _next; //指向下一条弧的指针
  //int weight; //边上的权重
};

typedef struct VNode{
  char vertex; //顶点信息
  ArcNode* _first_arc; //指向第一条依附该顶点的弧
}AdjList[VERTEX_MAX];

struct ALGraph{
  AdjList _adjList;
  int _vex_num; //图的顶点数
  int _arc_num; //图的弧数
};

//test
//---------------------------------------
//测试用例
int main(){

  return 0;
}
