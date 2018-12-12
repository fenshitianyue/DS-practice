#include<stdio.h>
//#include<stdlib.h>
//#include<assert.h>
#include"CLinkList.h"


int main(){
  PNode head;
  LinkTableInit(&head);
  LinkTablePushBack(&head, 1);
  LinkTablePushBack(&head, 2);
  LinkTablePushBack(&head, 3);
  LinkTablePushBack(&head, 4);
  LinkTablePushBack(&head, 5);
  LinkTablePushBack(&head, 6);
  LinkTablePrint(head);
  return 0;
}
