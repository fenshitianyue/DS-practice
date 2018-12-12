#pragma once
#include <iostream>
using namespace std;

enum Colour
{
	RED,
	BLACK,
};

template<class K, class V>
struct RBTreeNode
{
	K _key;
	V _value;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	
	Colour _colour;

	RBTreeNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_colour(RED)
	{}
};

template<class K, class V>
struct RBTree
{
	typedef RBTreeNode<K ,V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_colour = BLACK;

			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key, value);
		cur->_colour = RED;
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		// 
		while (parent && parent->_colour == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				// 1.存在且为红
				// 2.不存在，存在且为黑
				if (uncle && uncle->_colour == RED)
				{
					parent->_colour = uncle->_colour = BLACK;
					grandfather->_colour = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(parent->_right == cur)
					{
						RotateL(parent);

						swap(cur, parent);
					}

					RotateR(grandfather);
					parent->_colour = BLACK;
					grandfather->_colour = RED;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_colour == RED)
				{
					parent->_colour = BLACK;
					uncle->_colour = BLACK;
					grandfather->_colour = RED;

					// 继续往上更新
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 不存在 / 存在且为黑
				{
					if(cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}

					RotateL(grandfather);
					parent->_colour = BLACK;
					grandfather->_colour = RED;
				}
			}
		}

		_root->_colour = BLACK;

		return true;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (_root == parent)
		{
			_root =  subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_right == parent)
			{
				ppNode->_right = subL;
			}
			else
			{
				ppNode->_left = subL;
			}

			subL->_parent = ppNode;
		}
	}


	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}

			subR->_parent = ppNode;
		}

	}

	void InOrder()
	{
		_InOrder(_root);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

private:
	Node* _root;
};

void TestRBTree()
{
	int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	RBTree<int, int> t;
	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		t.Insert(a[i], i);
	}
	t.InOrder();
}
