#include <stdio.h>
#include <stdlib.h>

#define LH 1 /*H -> height*/
#define EH 0
#define RH -1

typedef int DataType;
typedef enum {FALSE, TRUE} Bool;

typedef struct BSTNode {
  DataType data;
  int bf;
  struct BSTNode* lchild, *rchild;
}* BSTree, BSTNode;

/* 对以p为根节点的二叉树做右旋处理 */
void R_Rotate(BSTree* p) {
  BSTree lc = (*p)->lchild; 
  (*p)->lchild = lc->rchild;
  lc->rchild = *p;
  *p = lc;
}

/* 对以p为根节点的二叉树做左旋处理 */
void L_Rotate(BSTree* p) {
  BSTree rc = (*p)->rchild;
  (*p)->rchild = rc->lchild;
  rc->rchild = *p;
  *p = rc;
}

/* 对以t为根节点的二叉树做左子树的平衡处理 */
void LeftBalance(BSTree* t) {
  BSTree lc = (*t)->lchild; 
  BSTree rc = NULL;
  /* 查看以t的左子树为根节点的子树失去平衡的原因：
   *  1.如果bf的值为1，说明新节点添加在左子树为根节点的左子树中，需要进行右旋处理
   *  2.如果bf的值为-1，说明新节点添加在左子树为根节点的右子树中，需要进行左-右双旋
   */
  switch(lc->bf) {
    case LH:
      (*t)->bf = lc->bf = EH;
      break;
    case RH:
      rc = lc->rchild;
      switch(rc->bf) {
        case LH:
          (*t)->bf = RH; /* 设置旋转前的根节点的平衡因子 */
          lc->bf = EH; /* 设置旋转前的根节点的左子树的平衡因子 */
          break;
        case EH:
          (*t)->bf = lc->bf = EH;
          break;
        case RH:
          (*t)->bf = EH; /* 设置旋转前的根节点的平衡因子 */
          lc->bf = LH; /* 设置旋转前的根节点的左子树的平衡因子 */
          break;
      }
      rc->bf = EH; /* 设置旋转后的根节点的平衡因子 */
      L_Rotate(&(*t)->lchild); /* 对旋转前的根节点的左子树做右旋处理 */
      R_Rotate(t); /* 对旋转前的根节点做右旋处理 */
      break;
  }
}

/* 对以t为根节点的二叉树做右子树的平衡处理,和左子树类似，做一个镜像处理 */

void RightBalance(BSTree* t) {
  BSTree rc = (*t)->rchild;
  BSTree lc = NULL;
  switch(rc->bf) {
    case RH:
      (*t)->bf = rc->bf = EH;
      L_Rotate(t);
      break;
    case LH:
      lc = rc->lchild;
      switch(lc->bf) {
        case LH:
          (*t)->bf = EH;
          rc->bf = RH;
          break;
        case EH:
          (*t)->bf = rc->bf = EH;
          break;
        case RH:
          (*t)->bf = EH;
          rc->bf = LH;
          break;
      }
      lc->bf = EH;
      R_Rotate(&(*t)->rchild);
      L_Rotate(t);
      break;
  }
}

/* 在以t为根节点的AVL树中查找数据域为e的节点，如果找到返回1；没找到返回0*/
Bool FindAvl(BSTree root, DataType e, BSTree* pos) {
  BSTree pt = root;
  *pos = NULL;
  while(pt) {
    if(e == pt->data) {
      *pos = pt;
      return TRUE;
    } else if(pt->data > e) {
      pt = pt->lchild;
    } else {
      pt = pt->rchild;
    }
  }
  return FALSE;
}

/* 中序遍历平衡二叉树 */
void InorderAvl(BSTree root) {
  if(root->lchild) 
    InorderAvl(root->lchild);
  printf("%d ", root->data);
  if(root->rchild)
    InorderAvl(root->rchild);
}

int InsertAvl(BSTree* t, DataType e, Bool* taller) {
  if(NULL == (*t)) {
    (*t) = (BSTree)malloc(sizeof(BSTNode));
    (*t)->bf = EH;
    (*t)->data = e;
    (*t)->lchild = NULL;
    (*t)->rchild = NULL;
    *taller = TRUE;
    /*return 0;*/
  } else if(e == (*t)->data) {
    *taller = FALSE;
    return 0; /*这里对插入重复节点做的处理是直接返回成功标标记，表示插入成功*/
  } else if(e < (*t)->data) { /*如果e小于根节点的数据域，则插入到根节点的左子树中*/
    /* 如果插入过程不会影响树本身的平衡，则结束插入过程 TODO*/ 
    if(!InsertAvl(&(*t)->lchild, e, taller)) {
      return 0;
    }
    /* 判断插入是否会导致整棵树的深度+1 */
    if(*taller) {
      switch((*t)->bf) {
        case LH:
          LeftBalance(t);
          *taller = FALSE;
          break;
        case EH:
          (*t)->bf = LH;
          *taller = TRUE;
          break;
        case RH:
          (*t)->bf = EH;
          *taller = FALSE;
          break;
      }
    }
  } else {
    if(!InsertAvl(&(*t)->rchild, e, taller)) {
      return 0;
    }
    if(*taller) {
      switch((*t)->bf) {
        case LH:
          (*t)->bf = EH;
          *taller = FALSE;
          break;
        case EH:
          (*t)->bf = RH;
          *taller = TRUE;
          break;
        case RH:
          RightBalance(t);
          *taller = FALSE;
          break;
      }
    }
  }
  return 1;
}

int main() {
  int arr[] = {1, 23, 45, 36, 98, 9, 4, 35, 23};
  BSTree root = NULL;
  Bool taller;
  for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
    InsertAvl(&root, arr[i], &taller);
  }

  InorderAvl(root);
  printf("\n");

  return 0;
}


