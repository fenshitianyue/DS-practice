#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void CreateGraph(vex_node* Graph, int vex_number, int arc_number) {
	int begin, end, weight;
	edge_node* p;
	//初始化
	for (int i = 0; i<vex_number; i++) {
		Graph[i].in_degree = 0;
		Graph[i].first_edge = NULL;
	}
	printf("请输入这个图中的各个顶点的值:\n");
	
	for (int i = 0; i < vex_number; i++) {
		fflush(stdin);
		scanf("%d", &Graph[i].data);
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
	int m = 0; //用于检测图中是否有环
	int  t = 0; //t 为path的下标
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
			printf("| %4d | %4d | %12d | %12d |", Graph[j].data, Graph[k].data, ee[i], el[i]);
			if (el[i] == ee[i]) {
				printf(" 是 ");
				//保存关键活动
				key_act[t].begin.vex = Graph[j].data;
				key_act[t].begin.visit = 0; //将访问位设置位未访问
				key_act[t].begin.flag = 0; //将访问位设置为无效
				key_act[t].end.vex = Graph[k].data;
				key_act[t].end.visit = 0;
				key_act[t].end.flag = 0;
				t++;
			}
			printf("\n");
			p = p->next_edge;
		}
	}
	//统计有几条关键路径TODO
	int time = check(key_act, t);
	repeat(key_act, t);	//设置分路节点类型
	int path[20] = { 0 };
	printf("关键路径有：\n");
	while (time){
		memset(path, 0, sizeof(path));
		int i = 0, j = 0;
		while (i != -1){
			path[j++] = key_act[i].begin.vex;
			int tmp = 0;
			tmp = find(key_act, t, key_act[i].end.vex);
			if (0 == key_act[tmp].begin.flag){ //如果不是分路节点，则按照正常流程来
				i = tmp;
			}
			else if (1 == key_act[tmp].begin.flag && 0 == key_act[tmp].begin.visit){ //如果是分路节点且没有被访问过，则访问它
				i = tmp;
				key_act[i].begin.visit = 1; //将分路节点设置为访问过
			}
			else {
				i = tmp-1; //special version
			}
		}
		path[j] = key_act[t - 1].end.vex;
		for (int i = 0; i <= j; i++) {
			printf("%d", path[i]);
			if (path[i] != path[j])
				printf("--->");
		}
		printf("\n");
		time--;
	}
	printf("\n");
	printf("关键路径长度为：%d个单位时间\n", total_time);
	return 1;
}

int find(key_activities array[], int size, int next){
	for (int i = 0; i < size; ++i){
		if (array[i].begin.vex == next)
			return i;
	}
	return -1;
}

//is special version
void repeat(key_activities array[], int size){
	for (int i = 0; i < size; ++i){
		char cur_node = array[i].begin.vex;
		for (int j = 0; j < size; ++j){
			if (i != j && array[j].begin.vex == cur_node){
				int index = find(array, size, array[j].end.vex); //找到枢纽节点指向节点的起始弧位置
				array[index].end.flag = 1; //is special version
				array[index].begin.flag = 1;
			}
		}
	}
	//将剩余没有设置flag位的支路节点设置flag位
	for (int i = 0; i < size; ++i){
		if (1 == array[i].end.flag){
			int index = find(array, size, array[i - 1].end.vex);
			array[i - 1].end.flag = 1;
			array[index].begin.flag = 1;
			break; //is special version
		}
	}
}

//is special version
int check(key_activities array[], int size){
	int n = 0; 
	for (int i = 0; i < size; ++i){
		char cur_node = array[i].begin.vex;
		for (int j = 0; j < size; ++j){
			if (i != j && array[j].begin.vex == cur_node){
				n++;
			}
		}
	}
	if (0 == n){
		return 1;
	}
	return n;
}
