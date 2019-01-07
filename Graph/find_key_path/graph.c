#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void CreateGraph(vex_node* Graph, int vex_number, int arc_number) {
	int begin, end, weight;
	char ch;
	edge_node* p;
	//��ʼ��
	for (int i = 0; i<vex_number; i++) {
		Graph[i].in_degree = 0; 
		Graph[i].first_edge = NULL;
	}
	printf("���������ͼ�еĸ��������ֵ:\n");
	for (int i = 0; i < vex_number; i++) {
		fflush(stdin);
		scanf("%c", &ch);
		Graph[i].data = ch;
	}
	printf("����ͼ�л�����ʼ�㼰Ȩֵ����ʽ����� �յ� Ȩֵ��\n");
	for (int i = 0; i < arc_number; i++) {
		fflush(stdin);
		scanf("%d%d%d", &begin, &end, &weight);
		p = (edge_node*)malloc(sizeof(edge_node));
		p->adjvex = end - 1;
		p->w = weight;
		Graph[end - 1].in_degree++; //�л�ָ��ö��㣬��ö������+1
		p->next_edge = Graph[begin - 1].first_edge;
		Graph[begin - 1].first_edge = p;
	}
}


int find_key_path(vex_node* Graph, int vex_number, int arc_number) {
	int total_time = 0;
	int m = 0; //?
	int  t = 0; //t Ϊsv���±�
	char sv[100]; //��¼�ؼ�·���϶�������� have bug������Ҫ�޸�Ϊ֧�ֶ����ؼ�·����������ֻһ��
	int front, rear; //��ͷ�Ͷ�β
	int *topology_queue; //���˶���
	int *vl, *ve, *el, *ee;
	int j = 0, k = 0; //��ʱ�±�
	front = rear = -1;
	topology_queue = (int*)malloc(vex_number * sizeof(int));

	vl = (int*)malloc(vex_number * sizeof(int)); //�����������ʱ��
	ve = (int*)malloc(vex_number * sizeof(int)); //��������緢��ʱ��

	el = (int*)malloc(arc_number * sizeof(int)); //���ʼ������ʱ��
	ee = (int*)malloc(arc_number * sizeof(int)); //���ʼ������ʱ��

	edge_node* p;

	for (int i = 0; i < vex_number; i++)
		ve[i] = 0;
	//����һ�����Ϊ1�Ķ����±�ŵ����˶�����
	for (int i = 0; i < vex_number; i++) {
		if (Graph[i].in_degree == 0) //�����ǰ��������Ϊ0
			topology_queue[++rear] = i;
		//m++; //ѭ��������m = �������
	}
	while (front != rear) {//������˶���û��
		front++;
		j = topology_queue[front]; //��ǰ��������Ķ��㣨���Ϊ0��
		m++; //���Ϊ0�Ķ������
		p = Graph[j].first_edge; //pָ��ǰ��������Ķ�����ڽӱ�
		while (p) { 
			k = p->adjvex; //kΪ�ڽӱ��е�ǰ��������Ķ����ڶ��������е��±�
			Graph[k].in_degree--;
			//�����һ���������򶥵����翪ʼʱ�� + �ʱ�� > ��һ���������򶥵�����翪ʼʱ��
			//�������һ���������򶥵�����翪ʼʱ��
			if (ve[j] + p->w >ve[k]) 
				ve[k] = ve[j] + p->w;

			if (Graph[k].in_degree == 0) //����ڽӱ��еĵ�ǰ�ڵ����-1 = 0��˵���ö��������һ��Ҫ��������Ķ���
				topology_queue[++rear] = k;
			p = p->next_edge;
		}	
}
	if (m < vex_number) { //���mС�ڶ�����Ŀ����˵���л�·
		printf("\nĿ��ͼ�а�����·������\n");
		return 0;
	}

	total_time = ve[vex_number - 1]; //��ʱ�伴���һ��Դ������緢��ʱ��

	//vl[i] = total_time - �ö�������������һ������͸ö���֮��Ļʱ��
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

	printf("| ��� | �յ� | ���翪ʼʱ�� | ��ٿ�ʼʱ�� | �Ƿ�Ϊ�ؼ�·�� \n");
	for (int j = 0, i = 0; j < vex_number; j++) {
		p = Graph[j].first_edge;
		while (p) {
			k = p->adjvex;
			ee[++i] = ve[j];
			el[i] = vl[k] - p->w;
			printf("| %4c | %4c | %12d | %12d |", Graph[j].data, Graph[k].data, ee[i], el[i]);
			if (el[i] == ee[i]) {
				printf(" �� ");
				sv[t++] = Graph[j].data; 
			}
			printf("\n");
			p = p->next_edge;
		}
	}
	printf("�ؼ�·���ڵ�Ϊ��");
	sv[t] = Graph[vex_number - 1].data;
	for (int i = 0; i <= t; i++) { 
		printf("%c", sv[i]);
		if (sv[i] != Graph[vex_number - 1].data)
			printf("--->");
	}
	printf("\n");
	printf("�ؼ�·������Ϊ��%d����λʱ��\n", total_time);
	return 1;
}
