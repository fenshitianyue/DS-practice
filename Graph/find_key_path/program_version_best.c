#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 15  //最大顶点数量 
#define MAXM 30   //最大边数量 

typedef int VertexType; //顶点类型由用户自定义
typedef int EdgeType; //边上的权值类型由用户自定义

typedef struct EdgeNode{ //边表结点
	int adjvex;  //邻接点域，存储该顶点对应的下标
	EdgeType weight; //权值
	struct EdgeNode *next; //链域，指向下一个邻接点 
} EdgeNode;

typedef struct VertexNode{ //顶点表结点
	VertexType data; //顶点域，存储顶点信息
	char vex_name[20]; //顶点名称
	int in;   //存储顶点入度的数量 
	EdgeNode *firstEdge; //边表头指针
} VertexNode;

typedef struct{
	char name[20];
	int vex;
}vex_path;

char name_map[6][MAXN] = { 0 };

void CreateGraph(VertexNode *GL, int n, int m) {//把顶点和边信息读入到表示图的邻接表中 
	int i, u, v;
	EdgeNode *e;
	printf("请输入这个图中的各个顶点的值(按照增序输入，下限为1):\n");
	for (i = 0; i < n; ++i){
		fflush(stdin);
		scanf("%s", name_map[i]);
	}
	for (i = 0; i < n; i++) {//初始化图 
		GL[i].data = i;
		strncpy(GL[i].vex_name, name_map[i], sizeof(name_map[i]));
		GL[i].in = 0;
		GL[i].firstEdge = NULL;
	}

	printf("输入图中弧的起始点及权值（格式：起点 终点 权值）\n");
	for (i = 0; i<m; i++) {
		e = (EdgeNode*)malloc(sizeof(EdgeNode)); //采用头插法插入边表结点 
		if (!e) {
			puts("Graph init Error");
			exit(1);
		}
		scanf("%d%d%d", &u, &v, &e->weight); //弧首，弧尾，权值
		u -= 1;
		v -= 1;
		e->next = GL[u].firstEdge; 
		GL[u].firstEdge = e;
		e->adjvex = v;
		GL[v].in++;
	}
}

int TopoLogicalSort_DFS(int topo[], int Etv[], VertexNode *GL, int n) {//深度优先搜索获取拓扑序列 
	int i, u, v, top, count = 0;
	EdgeNode *e;
	int *Stack;

	Stack = (int*)malloc(sizeof(int)* n); //分配栈空间 
	if (!Stack) {
		puts("Stack Error");
		exit(1);
	}
	for (top = i = 0; i<n; i++) {//将入度为0的顶点入栈 
		Etv[i] = 0; //初始化各事件最早发生事件为0 
		if (GL[i].in == 0) {
			Stack[top++] = i;
		}
	}

	while (top > 0) {//采用深度优先搜索获取拓扑序列 
		u = Stack[--top];
		topo[count++] = u;

		for (e = GL[u].firstEdge; e != NULL; e = e->next) {//将u的邻接点入度减1，并将入度为0的顶点入栈 
			v = e->adjvex;
			if (--GL[v].in == 0)
				Stack[top++] = v;

			if (Etv[v] < Etv[u] + e->weight)//更新各顶点事件的最早发生时间 
				Etv[v] = Etv[u] + e->weight;
		}
	}

	free(Stack);

	return (count == n);//如果count小于顶点数，说明存在环 
}

void PrintPath(VertexNode *GL, int Etv[], int Ltv[], int path[], int top, int end) {//深度优先搜索输出关键路径 
	int i, u = path[top - 1];
	EdgeNode *e;

	if (u == end) {
		printf("%d(%s)", path[0] + 1, name_map[path[0]]); //输出关键路径 
		for (i = 1; i < top; i++) {
			printf("->%d(%s)", path[i] + 1, name_map[path[i]]);
		}
		printf("\n");
		return;
	}

	for (e = GL[u].firstEdge; e != NULL; e = e->next) {
		if (Etv[e->adjvex] == Ltv[e->adjvex]) {//关键事件
			path[top++] = e->adjvex; //入栈 
			PrintPath(GL, Etv, Ltv, path, top, end);
			top--; //退栈 
		}
	}
}

void CriticalPath(VertexNode *GL, int n) {//求关键路径 
	int i, u, v;
	EdgeNode *e;
	int topo[MAXN] = { 0 }, path[MAXN] = { 0 };
	int Etv[MAXN] = { 0 }, Ltv[MAXN] = { 0 };//存储事件的最早和最晚发生时间 

	if (!TopoLogicalSort_DFS(topo, Etv, GL, n)) {
		puts("不存在关键路径");
		return;
	}

	for (i = 0; i < n; i++) {
		Ltv[i] = Etv[n - 1]; //初始化各事件最晚发生事件为最后一个事件发生的时间 
	}

	for (i = n - 2; i >= 0; i--) {
		u = topo[i];
		for (e = GL[u].firstEdge; e != NULL; e = e->next) {
			v = e->adjvex;
			if (Ltv[u] > Ltv[v] - e->weight)//更新各顶点事件的最晚发生时间 
				Ltv[u] = Ltv[v] - e->weight;
		}
	}

	path[0] = topo[0];
	printf("关键路径长度为：%d个单位时间\n", Etv[n - 1]);
	printf("该图的关键路径如下：\n\n");
	PrintPath(GL, Etv, Ltv, path, 1, topo[n - 1]);
}


int main() {
	int m, n;
	VertexNode GL[MAXN];

	printf("请输入顶点数量和边数量:");
	scanf("%d%d", &n, &m);
	CreateGraph(GL, n, m);//把顶点和边信息读入到表示图的邻接表中 
	CriticalPath(GL, n);//求关键路径

	return 0;
}
