#include <stdio.h>
#include <stdlib.h>

//定义平衡因子数
#define LH +1
#define EH 0
#define RH -1
typedef int ElemType;
typedef enum { false, true } bool;

//定义二叉搜索树
typedef struct BSTNode{
  ElemType _data;
  int _bf; //balance flag
  struct BSTNode* _lchild, *_rchild;
}*BSTree, BSTNode;

//对根节点做右旋处理
void R_Rotate(BSTree* p){
  BSTree lc = (*p)->_lchild;
  (*p)->_lchild = lc->_rchild;
  lc->_rchild = *p;
  *p = lc;
}

//对根节点做左旋处理
void L_Rotate(BSTree* p){
  BSTree rc = (*p)->_rchild; 
  (*p)->_rchild = rc->_lchild;
  rc->_lchild = *p;
  *p = rc;    
}

int InsertAVL(BSTree* T, ElemType e, bool* taller){

}

bool FindNode(BSTree root, ElemType e, BSTree* pos){

}

void InorderTra(BSTree root){
  if(root->_lchild){
    InorderTra(root->_lchild);
  }
  printf("%d ", root->_data);
  if(root->_rchild){
    InorderTra(root->_rchild);
  }
}

int main() {
  int array[] = {1, 43, 21, 89, 10, 9}; 
  BSTree root = NULL;
  BSTree pos = NULL;
  bool taller;
  for(size_t i = 0; i < sizeof(array) / sizeof(array[0]); ++i){
    InsertAVL(&root, array[i], &taller);
  }
  InorderTra(root);
  if(FindNode(root, 10, &pos)){
    printf("\n%d\n", pos->_data);
  } else {
    printf("\nNot find this node\n");
  }
  return 0;
}
