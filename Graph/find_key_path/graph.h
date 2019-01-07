#pragma once

//------------定义邻接表------------

//定义节点
typedef struct node{
	int  adjvex; //邻接点在顶级链表中的下标
	int  w; //权重
	struct node *next_edge; //指向下一个邻接点的指针
}edge_node;

//定义边集 
typedef struct{
	char     data; //顶点的数据
	int      in_degree; //入度
	edge_node  *first_edge; //指向邻接点的指针
}vex_node;

//------------定义邻接表------------

//------------接口函数------------

//创建图的函数
//参数说明：图，顶点的个数，边的个数
void CreateGraph(vex_node* Graph, int vex_number, int arc_number);

//寻找关键路径的函数
//参数说明：图，顶点的个数，边的个数
int find_key_path(vex_node* Graph, int vex_number, int arc_number);

//------------接口函数------------
