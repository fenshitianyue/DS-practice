#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#pragma warning(disable: 4996)

//测试用例
int main() {
	int vex_number, arc_number;
	printf("输入图中的节点数:");
	scanf("%d", &vex_number);
	printf("输入图中的弧数:");
	scanf("%d", &arc_number);

	vex_node* Graph = (vex_node*)malloc(vex_number * sizeof(vex_node));

	CreateGraph(Graph, vex_number, arc_number);
	find_key_path(Graph, vex_number, arc_number);

	system("pause");
	return 0;
}


