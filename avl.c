#include <stdio.h>
#include <stdlib.h>

//定义平衡因子数
#define LH 1
#define EH 0
#define RH -1
typedef int ElemType;
typedef enum { FALSE, TRUE } Bool;

//定义二叉搜索树
typedef struct BSTNode{
  ElemType _data;
  int _bf; //balance flag
  struct BSTNode* _lchild, *_rchild;
}*BSTree, BSTNode;

//对根节点做右旋处理
void R_Rotate(BSTree* p){
  BSTree lc = (*p)->_lchild; //保存旧根节点的左子树
  (*p)->_lchild = lc->_rchild; //将旧根节点的左子树的右子树赋给旧根节点的左子树
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

void LeftBalance(BSTree* T){
  BSTree lc, rc;
  lc = (*T)->_lchild;
  switch(lc->_bf){
    case LH:
      (*T)->_bf = lc->_bf = EH;
      R_Rotate(T);
      break;
    case RH:
      rc = lc->_rchild;
      switch(rc->_bf){
        case LH:
          (*T)->_bf = RH;
          lc->_bf = EH;
          break;
        case EH:
          (*T)->_bf = lc->_bf = EH;
          break;
        case RH:
          (*T)->_bf = EH;
          lc->_bf = LH;
          break;
      }
      rc->_bf = EH;
      L_Rotate(&(*T)->_lchild);
      R_Rotate(T);
      break;
  }
}

void RightBalance(BSTree* T){
  BSTree lc, rc;
  lc = (*T)->_rchild;
  switch(lc->_bf){
    case RH:
      (*T)->_bf = lc->_bf = EH;
      L_Rotate(T);
      break;
    case LH:
      rc = lc->_lchild;
      switch(rc->_bf){
        case LH:
          (*T)->_bf = EH;
          lc->_bf = RH;
          break;
        case EH:
          (*T)->_bf = lc->_bf = EH;
          break;
        case RH:
          (*T)->_bf = EH;
          lc->_bf = LH;
          break;
      }
      rc->_bf = EH;
      R_Rotate(&(*T)->_rchild);
      L_Rotate(T);
      break;
  }
}

int InsertAVL(BSTree* T, ElemType e, bool* taller){
  if(NULL == *T){
    *T = (BSTree)malloc(sizeof(BSTNode));
    (*T)->_bf = EH;
    (*T)->_data = e;
    (*T)->_lchild = NULL;
    (*T)->_rchild = NULL;
    *taller = TRUE;
  } else if (e == (*T)->_data){
    *taller = FALSE;
    return 0;
  } else if (e < (*T)->_data){
    if(!InsertAVL(&(*T)->_lchild, e, taller)){
      return 0;
    } 
    if(*taller){
      switch((*T)->_bf){
        case LH:
          LeftBalance(T);
          *taller = FALSE;
          break;
        case EH:
          (*T)->_bf = LH;
          *taller = TRUE;
          break;
        case RH:
          (*T)->_bf = EH;
          *taller = FALSE;
          break;
      }
    } 
  } else {
    if(!InsertAVL(&(*T)->_rchild, e, taller)){
      return 0;
    }
    if(*taller){
      switch((*T)->_bf){
        case LH:
          (*T)->_bf = EH;
          *taller = FALSE;
          break;
        case EH:
          (*T)->_bf = RH;
          *taller = TRUE;
          break;
        case RH:
          RightBalance(T);
          *taller = FALSE;
          break;
      }//switch
    }//if
  }//else
  return 1;
}

bool FindNode(BSTree root, ElemType e, BSTree* pos){
  BSTree pt = root;
  *pos = NULL;
  while(pt){
    if(e == pt->_data){
      (*pos) = pt;
      return TRUE;
    } else if(e < pt->_data) {
      pt = pt->_lchild;
    } else {
      pt = pt->_rchild;
    }
  }
  return FALSE;
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

//test
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
