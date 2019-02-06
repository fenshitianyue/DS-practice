#pragma once


typedef enum {RED, BLACK} color_type;
typedef struct rb_tree{
  int _key;
  struct rb_tree* _left;
  struct rb_tree* _right;
  struct rb_tree* _p;
  color_type _color;
}rb_tree;

typedef struct rbt_root{
  rb_tree* _root;
  rb_tree* _nil;
}rbt_root;

rbt_root* rb_tree_init(void);
void rb_tree_insert(rbt_root** T, int k);
void rb_tree_delete(rbt_root** T, int k);

void rb_tree_transplant(rbt_root* T, rb_tree* u, rb_tree* v);

void rb_tree_left_rotate(rbt_root* T, rb_tree* x);
void rb_tree_right_rotate(rbt_root* T, rb_tree* x);

void rb_tree_inPrint(rbt_root* T, rb_tree* t);
void rb_tree_prePrint(rbt_root* T, rb_tree* t);
void rb_tree_print(rbt_root* T);

rb_tree* rbt_findMin(rbt_root* T, rb_tree* t);

