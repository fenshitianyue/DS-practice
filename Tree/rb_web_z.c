#include <stdio.h>
#include <stdlib.h>
#include "rb_web_z.h"

void rb_tree_left_rotate(rbt_root* T, rb_tree* x){
  rb_tree* y = x->_right;
  x->_right = y->_left;
  if(x->_right != T->_nil){
    x->_right->_p = x;
  }
  y->_p = x->_p;
  if(y->_p == T->_nil){
    T->_root = y;
  }else if(y->_key > y->_p->_key){
    y->_p->_left = y;
  }else{
    y->_p->_right = y;
  }
  y->_left = x;
  x->_p = y;
}

void rb_tree_right_rotate(rbt_root* T, rb_tree* x){
  rb_tree* y = x->_left;
  x->_left = y->_right;
  if(T->_nil != x->_left){
    x->_left->_p = x;
  }
  y->_p = x->_p;
  if(y->_p == T->_nil){
    T->_root = y;
  }else if(y->_key < y->_p->_key){
    y->_p->_left = y;
  }else{
    y->_p->_right = y;
  }
  y->_right = x;
  x->_p = y;
}

rb_tree* rbt_findMin(rbt_root* T, rb_tree* t){
  if(t == T->_nil){
    return T->_nil;
  }
  while(t->_left != T->_nil){
    t = t->_left;
  }
  return t;
}

rbt_root* rb_tree_init(void){
  rbt_root* T;
  T = (rbt_root*)malloc(sizeof(rbt_root));
  T->_nil = (rb_tree*)malloc(sizeof(rb_tree));
  T->_nil->_color = BLACK;
  T->_nil->_left = T->_nil->_right = NULL;
  T->_root = T->_nil;
  return T;
}

void rb_insert_fixup(rbt_root* T, rb_tree* x){
  while(x->_p->_color == RED){
    if(x->_p == x->_p->_p->_left){
      rb_tree* uncle = x->_p->_p->_right;  
      if(uncle->_color == RED){
        x->_p->_color = BLACK;
        uncle->_color = BLACK;
        x->_p->_p->_color = RED;
        x = x->_p->_p;
      }else{
        if(x == x->_p->_right){
          x = x->_p;
          rb_tree_left_rotate(T, x);
        }else{
          x->_p->_color = BLACK;
          x->_p->_p->_color = RED;
          rb_tree_right_rotate(T, x->_p->_p);
        }
      }
    }else{
      rb_tree* uncle = x->_p->_p->_left;
      if(uncle->_color == RED){
        x->_p->_color = BLACK;
        uncle->_color = BLACK;
        x->_p->_p->_color = RED;
        x = x->_p->_p;
      }else{
        if(x == x->_p->_left){
          x = x->_p;
          rb_tree_right_rotate(T, x);
        }else{
          x->_p->_color = BLACK;
          x->_p->_p->_color = RED;
          rb_tree_left_rotate(T, x->_p->_p);
        }
      }
    }
  }  
  T->_root->_color = BLACK;
}

void rb_tree_insert(rbt_root** T, int k){
  rb_tree* x, *p;
  p = x = (*T)->_root;
  while(x != (*T)->_nil){
    p = x;
    if(k < x->_key){
      x = x->_left;
    }else if(k > x->_key){
      x = x->_right;
    }else{
      printf("\n%d had exist!\n", k);
      return;
    }
  } 
  x = (rb_tree*)malloc(sizeof(rb_tree));
  x->_key = k;
  x->_color = RED;
  x->_left = x->_right = (*T)->_nil;
  x->_p = p;
  if((*T)->_root == (*T)->_nil){
    (*T)->_root = x;
  }else if(k < p->_key){
    p->_left = x;
  }else{
    p->_right = x;
  }
  rb_insert_fixup((*T), x);
}



