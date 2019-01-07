#pragma once

//------------�����ڽӱ�------------

//����ڵ�
typedef struct node{
	int  adjvex; //�ڽӵ��ڶ��������е��±�
	int  w; //Ȩ��
	struct node *next_edge; //ָ����һ���ڽӵ��ָ��
}edge_node;

//����߼� 
typedef struct{
	char     data; //���������
	int      in_degree; //���
	edge_node  *first_edge; //ָ���ڽӵ��ָ��
}vex_node;

//------------�����ڽӱ�------------

//------------�ӿں���------------

//����ͼ�ĺ���
//����˵����ͼ������ĸ������ߵĸ���
void CreateGraph(vex_node* Graph, int vex_number, int arc_number);

//Ѱ�ҹؼ�·���ĺ���
//����˵����ͼ������ĸ������ߵĸ���
int find_key_path(vex_node* Graph, int vex_number, int arc_number);

//------------�ӿں���------------
