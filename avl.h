#pragma once 
#include <iostream>
#include <assert.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode{
  K _key;
  V _value;
  AVLTreeNode<K, V>* _left;
  AVLTreeNode<K, V>* _right;
  AVLTreeNode<K, V>* _parent;
  int _bf;
  AVLTreeNode(const K& key, const V& value)
    :_left(NULL)
    ,_right(NULL)
    ,_parent(NULL)
    ,_key(key)
    ,_value(value)
    ,_bf(0)
  {}
};

template<class K, class V>
class AVLTree{
  typedef AVLTreeNode<K, V> Node;
private:
  Node* _root;
public:
  AVLTree()
    :_root(NULL)
  {}
  bool Insert(const K& key, const V& value){
    if(_root == NULL){
      _root = new Node(key, value);
      return true;
    }
    Node* parent = NULL;
    Node* cur = _root;
    while(cur){
      if(cur->_key > key){
        parent = cur;
        cur = cur->_left;
      }else if(cur->_key < key){
        parent = cur;
        cur = cur->_right;
      }else{
        return false;
      }
    }
    cur = new Node(key, value);
    if(parent->_key < key){
      parent->_right = cur;
      cur->_parent = parent;
    }else{
      parent->_left = cur;
      cur->_parent = parent;
    }
    //调平衡
    //1.更新平衡因子
    while(parent){
      if(cur == parent->_parent)
        parent->_bf++;
      else 
        parent->_bf--;
      if(parent->_bf == -1 || parent->_bf == 1){
        cur = parent;
        parent = parent->_parent;
      }else if(parent->_bf == 0){
        break;
      }
      else{
        if(parent->_bf == 2){
          if(cur->_bf == 1){
            RotateL(parent);
          }else{
            RotateRL(parent);
          }
        }else{
          if(cur->_bf == -1){
            RotateR(parent);
          }else{
            RotateLR(parent);
          }
        }
        break;
      }
    } 
    return true;
  } 
  void RotateR(Node* parent){
    Node* subL = parent->_left;
    Node* subLR = subL->_right;
    Node* ppNode = parent->_parent;
    parent->_left = subLR;
    if(subLR)
      subLR->_parent = parent;
    subL->_right = parent;
    parent->_parent = subL;
    if(_root == parent){
      _root = subL;
      subL->_parent = NULL;
    }else{
      if(ppNode->_right == parent){
        ppNode->_right = subL;
      }else{
        ppNode->_left = subL;
      }
      subL->_parent = ppNode;
    }
    subL->_bf = parent->_bf = 0;
  }        
  void RotateL(Node* parent){
    Node* subR = parent->_right;
    Node* subRL = subR->_left;
    Node* ppNode = parent->_parent;
    parent->_right = subRL;
    if(subRL)
      subRL->_parent = parent;
    subR->_left = parent;
    parent->_parent = subR;
    if(parent == _root){
      _root = subR;
      _root->_parent = NULL;
    }else{
      if(ppNode->_left == parent){
        ppNode->_left = subR;
      }else{
        ppNode->_right = subR;
      }
      subR->_parent = ppNode;
    }
    parent->_bf = subR->_bf = 0;
  }
  void RoteteRL(Node* parent){
    Node* subR = parent->_right;
    Node* subRL = subR->_left;
    int bf = subRL->_bf;
    RotateR(parent->_right);
    RotateL(parent);
    if(bf == 0){
      subRL->_bf = subR->_bf = parent->_bf = 0;
    }else if(bf == 1){
      subR->_bf = 0;
      parent->_bf = 1;
      subRL->_bf= 0;
    }else if(bf == -1){
      parent->_bf = 0;
      subR->_bf = 1;
      subRL->_bf = 0;
    }else{
      assert(false);
    }
  }
  void RotateLR(Node* parent)
  {
    Node* subL = parent->_left;
    Node* subLR = subL->_right;
    int bf = subLR->_bf;
    RotateL(parent->_left);
    RotateR(parent);
    if (bf == 0)
    {
      subLR->_bf = subL->_bf = parent->_bf = 0;
    }
    else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
      assert(false);
    }
  }
  bool _IsBalance(Node* root, int& height){
    if(root == NULL){
      height = 0;
      return true;
    }
    int leftHeight = 0;
    int rightHeight = 0;
    if(_IsBalance(root->_left, leftHeight)
        && _IsBalance(root->_right, rightHeight)){
      if(rightHeight - leftHeight != root->_bf){
        cout<<"error!!!!"<<root->_key<<endl;
        return false;
      }
      height = leftHeight > rightHeight ? leftHeight+1 : rightHeight + 1;
      return abs(leftHeight-rightHeight) < 2;
    }else{
      return false;
    }
  }
  bool _IsBalance(Node* root){
    int height = 0;
    return _IsBalance(root, height);
  }
};



























