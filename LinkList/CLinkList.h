#pragma once 

#define DataType int

typedef struct LinkNode{
  DataType _data;
  struct LinkNode *_next;
  struct LinkNode *_random;
}Node, *PNode;


void LinkTableInit(PNode *pphead);
void LinkTablePushBack(PNode *pphead, DataType data);
void LinkTablePopBack(PNode *pphead);
void LinkTablePushFront(PNode *pphead, DataType data);
void LinkTablePopFront(PNode *pphead);
PNode Find(PNode head, DataType data);
void LinkTableErase(PNode *pphead, PNode pos);
unsigned int LinkSize(PNode head);
int Empty(PNode head);
void LinkTableDestroy(PNode *pphead);
PNode BuyNewNode(DataType data);

void LinkTablePrint(PNode head);



