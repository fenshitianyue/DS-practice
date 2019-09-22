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
          break;
        case EH:
          break;
        case RH:
          break;
      }
      break;
      lc->bf = EH;
  }
}




