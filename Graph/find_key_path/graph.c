#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void CreateGraph(vex_node* Graph, int vex_number, int arc_number) {
	int begin, end, weight;
	char ch;
	edge_node* p;
	//初始化
	for (int i = 0; i<vex_number; i++) {
		Graph[i].in_degree = 0; 
		Graph[i].first_edge = NULL;
	}
	printf("请输入这个图中的各个顶点的值:\n");
	for (int i = 0; i < vex_number; i++) {
		fflush(stdin);
		scanf("%c", &ch);
		Graph[i].data = ch;
	}
	printf("输入图中弧的起始点及权值（格式：起点 终点 权值）\n");
	for (int i = 0; i < arc_number; i++) {
		fflush(stdin);
		scanf("%d%d%d", &begin, &end, &weight);
		p = (edge_node*)malloc(sizeof(edge_node));
		p->adjvex = end - 1;
		p->w = weight;
		Graph[end - 1].in_degree++; //有弧指向该顶点，则该顶点入度+1
		p->next_edge = Graph[begin - 1].first_edge;
		Graph[begin - 1].first_edge = p;
	}
}


int find_key_path(vex_node* Graph, int vex_number, int arc_number) {
	int total_time = 0;
	int m = 0; //?
	int  t = 0; //t 为sv的下标
	char sv[100]; //记录关键路径上顶点的数据 have bug：这里要修改为支持多条关键路径，而不是只一条
	int front, rear; //队头和队尾
	int *topology_queue; //拓扑队列
	int *vl, *ve, *el, *ee;
	int j = 0, k = 0; //临时下标
	front = rear = -1;
	topology_queue = (int*)malloc(vex_number * sizeof(int));

	vl = (int*)malloc(vex_number * sizeof(int)); //顶点的最晚发生时间
	ve = (int*)malloc(vex_number * sizeof(int)); //顶点的最早发生时间

	el = (int*)malloc(arc_number * sizeof(int)); //活动开始的最晚时间
	ee = (int*)malloc(arc_number * sizeof(int)); //活动开始的最早时间

	edge_node* p;

	for (int i = 0; i < vex_number; i++)
		ve[i] = 0;
	//将第一个入度为1的顶点下标放到拓扑队列中
	for (int i = 0; i < vex_number; i++) {
		if (Graph[i].in_degree == 0) //如果当前顶点的入度为0
			topology_queue[++rear] = i;
		//m++; //循环结束后m = 顶点个数
	}
	while (front != rear) {//如果拓扑队列没满
		front++;
		j = topology_queue[front]; //当前拓扑排序的顶点（入度为0）
		m++; //入度为0的顶点个数
		p = Graph[j].first_edge; //p指向当前拓扑排序的顶点的邻接表
		while (p) { 
			k = p->adjvex; //k为邻接表中当前拓扑排序的顶点在顶级链表中的下标
			Graph[k].in_degree--;
			//如果上一个拓扑排序顶点最早开始时间 + 活动时间 > 下一个拓扑排序顶点的最早开始时间
			//则更新下一个拓扑排序顶点的最早开始时间
			if (ve[j] + p->w >ve[k]) 
				ve[k] = ve[j] + p->w;

			if (Graph[k].in_degree == 0) //如果邻接表中的当前节点入度-1 = 0，说明该顶点就是下一个要拓扑排序的顶点
				topology_queue[++rear] = k;
			p = p->next_edge;
		}	
}
	if (m < vex_number) { //如果m小于顶点数目，则说明有回路
		printf("\n目标图中包含回路！！！\n");
		return 0;
	}

	total_time = ve[vex_number - 1]; //总时间即最后一个源点的最早发生时间

	//vl[i] = total_time - 该顶点拓扑序列上一个顶点和该顶点之间的活动时间
	for (int i = 0; i < vex_number; i++)
		vl[i] = total_time; 
	for (int i = vex_number - 2; i >= 0; i--) {
		j = topology_queue[i];
		p = Graph[j].first_edge;
		while (p) {
			k = p->adjvex;
			if ((vl[k] - p->w) < vl[j])
				vl[j] = vl[k] - p->w;
			p = p->next_edge;
		}
	}

	printf("| 起点 | 终点 | 最早开始时间 | 最迟开始时间 | 是否为关键路径 \n");
	for (int j = 0, i = 0; j < vex_number; j++) {
		p = Graph[j].first_edge;
		while (p) {
			k = p->adjvex;
			ee[++i] = ve[j];
			el[i] = vl[k] - p->w;
			printf("| %4c | %4c | %12d | %12d |", Graph[j].data, Graph[k].data, ee[i], el[i]);
			if (el[i] == ee[i]) {
				printf(" 是 ");
				sv[t++] = Graph[j].data; 
			}
			printf("\n");
			p = p->next_edge;
		}
	}
	printf("关键路径节点为：");
	sv[t] = Graph[vex_number - 1].data;
	for (int i = 0; i <= t; i++) { 
		printf("%c", sv[i]);
		if (sv[i] != Graph[vex_number - 1].data)
			printf("--->");
	}
	printf("\n");
	printf("关键路径长度为：%d个单位时间\n", total_time);
	return 1;
}
