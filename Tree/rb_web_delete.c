
void rbTree_transplant(RBT_Root* T, RB_TREE* u, RB_TREE* v){
    if(u->p == T->nil){
        T->root = v;
    }else if(u == u->p->left){
        u->p->left=v;
    }else{
        u->p->right=v;
    }
    v->p = u->p;
}
void RB_Delete_Fixup(RBT_Root**T,RB_TREE*x){
    while(x != (*T)->root && x->color == BLACK){
        if(x == x->p->left){
            RB_TREE* w = x->p->right;
            //第 1 种情况：兄弟结点是红色的
            if(RED == w->color){
                w->color = BLACK;
                w->p->color = RED;
                rbTree_left_rotate((*T),x->p);
                w = x->p->right;
            }
            //第2种情况：兄弟是黑色的，并且兄弟的两个儿子都是黑色的。
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->p;
            }
            //第3种情况
            if(w->left->color == RED && w->right->color == BLACK){
                w->left->color = BLACK;
                w->color = RED;
                rbTree_right_rotate((*T),w);
                w = x->p->right;
            }
            //第4种情况
            if (w->right->color == RED) {
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                rbTree_left_rotate((*T),x->p);
                x = (*T)->root;
            }
        }else{
            RB_TREE* w = x->p->left;
            //第 1 种情况
            if(w->color == RED){
                w->color = BLACK;
                x->p->color = RED;
                rbTree_right_rotate((*T),x->p);
                w = x->p->left;
            }
            //第 2 种情况
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->p;
            }
            //第 3 种情况
            if(w->left->color == BLACK && w->right->color == RED){
                w->color = RED;
                w->right->color = BLACK;
                w = x->p->left;
            }
            //第 4 种情况
            if (w->right->color == BLACK){
                w->color=w->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rbTree_right_rotate((*T),x->p);
                x = (*T)->root;
            }
        }
    }
    x->color = BLACK;//最终将根结点的颜色设为黑色
}
void rbTree_delete(RBT_Root* *T, int k){
    if(NULL == (*T)->root){
        return ;
    }
    //找到要被删除的结点
    RB_TREE * toDelete = (*T)->root;
    RB_TREE * x = NULL;
    //找到值为k的结点
    while(toDelete != (*T)->nil && toDelete->key != k){
        if(k<toDelete->key){
            toDelete = toDelete->left;
        }else if(k>toDelete->key){
            toDelete = toDelete->right;
        }
    }
    if(toDelete == (*T)->nil){
        printf("\n%d 不存在\n",k);
        return;
    }
    //如果两个孩子，就找到右子树中最小的结点，将之代替，然后直接删除该结点即可
    if(toDelete->left != (*T)->nil && toDelete->right != (*T)->nil){
        RB_TREE* alternative = rbt_findMin((*T), toDelete->right);
        k = toDelete->key = alternative->key;//这里只对值进行复制，并不复制颜色，以免破坏红黑树的性质
        toDelete = alternative;
    }
    //如果只有一个孩子结点（只有左孩子或只有右孩子），直接用孩子结点顶替该结点位置即可（没有孩子结点的也走此判断语句）。
    if(toDelete->left == (*T)->nil){
        x = toDelete->right;
        rbTree_transplant((*T),toDelete,toDelete->right);
    }else if(toDelete->right == (*T)->nil){
        x = toDelete->left;
        rbTree_transplant((*T),toDelete,toDelete->left);
    }
    //在删除该结点之前，需判断此结点的颜色：如果是红色，直接删除，不会破坏红黑树；若是黑色，删除后会破坏红黑树的第 5 条性质，需要对树做调整。
    if(toDelete->color == BLACK){
        RB_Delete_Fixup(T,x);
    }
    //最终可以彻底删除要删除的结点，释放其占用的空间
    free(toDelete);
}
