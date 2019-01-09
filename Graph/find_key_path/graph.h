#pragma once

//------------定义邻接表------------
#define MAX_DATA_LANGTH 20

//定义节点
typedef struct node{
	int  adjvex; //邻接点在顶级链表中的下标
	int  w; //权重
	struct node *next_edge; //指向下一个邻接点的指针
}edge_node;

//定义边集 
typedef struct{
	int     data; 
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


//------------定义关键活动结构------------
#define MAX_KEY_ACT 20

//封装关键路径节点类型
typedef struct {
	int vex;
	int visit; //0表示没有访问过，1表示访问过
	int flag; //0表示访问位无效，1表示访问位有效
}path_node;

//存放关键活动
typedef struct {
	path_node begin;
	path_node end;
}key_activities;

key_activities key_act[MAX_KEY_ACT]; //存储关键活动的数组

//------------定义关键活动结构------------

int find(key_activities array[], int size, int next);
void repeat(key_activities array[], int size);
int check(key_activities array[], int size);
