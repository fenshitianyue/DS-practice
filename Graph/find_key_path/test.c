#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#pragma warning(disable: 4996)

//��������
int main() {
	int vex_number, arc_number;
	printf("����ͼ�еĽڵ���:");
	scanf("%d", &vex_number);
	printf("����ͼ�еĻ���:");
	scanf("%d", &arc_number);

	vex_node* Graph = (vex_node*)malloc(vex_number * sizeof(vex_node));

	CreateGraph(Graph, vex_number, arc_number);
	find_key_path(Graph, vex_number, arc_number);

	system("pause");
	return 0;
}


