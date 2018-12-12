#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"CLinkList.h"

void LinkTableInit(PNode *pphead){
  assert(pphead);
  *pphead = NULL;
}

void LinkTablePushBack(PNode *pphead, DataType data){
  assert(pphead);
  if(*pphead == NULL){
    *pphead = BuyNewNode(data);
  }else{
    PNode str = *pphead;
    while(str->_next != NULL){
      str = str->_next;
    }
    str->_next = BuyNewNode(data);
  }
}

void LinkTablePopBack(PNode *pphead){
  assert(pphead);
  if(*pphead == NULL){
    free(*pphead);
    *pphead = NULL;
  }else{
    PNode str = *pphead;
    PNode str_pre = NULL;
    while(str->_next != NULL){
      str_pre = str;
      str = str->_next;
    }
    free(str);
    str_pre->_next = NULL;
  }
}

void LinkTablePushFront(PNode *pphead, DataType data){
  assert(pphead);
  if(*pphead == NULL){
    *pphead = BuyNewNode(data);
  }else{
    PNode str = BuyNewNode(data);
    str->_next = *pphead;
    *pphead = str;
  }
}

void LinkTablePopFront(PNode *pphead){
  assert(pphead);
  if(*pphead == NULL){
    return;
  }else{
    PNode str = *pphead;
    *pphead = (*pphead)->_next;
    free(str);
  }
}

PNode Find(PNode head, DataType data){
  PNode str = head;
  if(str == NULL){
    return NULL;
  } 
  while(str){
    if(str->_data == data){
      return str;
    }
    str = str->_next;
  }
  return NULL;
}

void LinkTableErase(PNode *pphead, PNode pos){
  assert(pphead);
  assert(pos);
  if(*pphead == NULL){
    return;
  }
  PNode str = *pphead;
  PNode str_pre = NULL;
  while(str){
    if(str == pos){
      if(str == *pphead){
        free(str);
        *pphead = NULL;
      }else{
        str_pre->_next = str->_next;
        free(str);
      }
    }
    str_pre = str;
    str = str->_next;
  }
}

unsigned int LinkSize(PNode head){
  size_t count = 0;
  PNode str = head;
  while(str){
    str = str->_next;
    count++;
  }
  return count;
}

int Empty(PNode head){
  return head == NULL;
}

void LinkTableDestroy(PNode *pphead){
  assert(pphead);
  if(*pphead == NULL){
    free(*pphead);
    *pphead = NULL;
  }else{
    while(!Empty(*pphead)){
      LinkTablePopFront(pphead); 
    }
  }
}

PNode BuyNewNode(DataType data){
  PNode str = (PNode)malloc(sizeof(Node));
  if(str == NULL){
    return NULL;
  }
  str->_data = data;
  str->_next = NULL;
  str->_random = NULL;
  return str;
}


void LinkTablePrint(PNode head){
  assert(head);
  PNode str = head;
  while(str){
    printf("%d ",str->_data);
    str = str->_next;
  }
  printf("\n");
}


