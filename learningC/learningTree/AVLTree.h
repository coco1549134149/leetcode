#pragma once
#include <stdio.h>
#include <iostream>
#include "commonFunc.h"
#include <stack>
using namespace std;
//AVLTree树节点定义
template <class K, class V>
struct AVLTreeNode
{
	K _key;
	V _val;

	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;    //平衡因子

	AVLTreeNode(const K& key, const V& val)
		:_key(key)
		, _val(val)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _bf(0)
	{}

};

//AVLTree类的定义
template <class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> AVLNode;
public:
	AVLTree()   //构造函数
		:_root(NULL)
	{}

	bool AVLInsert(K key, V val);    //插入节点

	void RotateL(AVLNode* parent);     //  左单旋
	void RotateR(AVLNode* parent);     //  右单旋
	void RotateLR(AVLNode* parent);    //  左右双旋
	void RotateRL(AVLNode* parent);    //  右左双旋

	bool _IsBalance(AVLNode* root, int& height)    //判断是否平衡
	{
		if (root == NULL)
		{
			height = 0;
			return true;
		}

		int leftHeight = 0;
		int rightHeight = 0;
		if (_IsBalance(root->_left, leftHeight)
			&& _IsBalance(root->_right, rightHeight))
		{
			if (rightHeight - leftHeight != root->_bf)
			{
				cout << "平衡因子异常" << root->_key << endl;
				return false;
			}

			height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
			return abs(leftHeight - rightHeight) < 2;
		}
		else
		{
			return false;
		}
	}

	bool IsBalance()
	{
		int height = 0;
		return _IsBalance(_root, height);
	}

	void _InOrder(AVLNode* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	AVLNode* _root;
};

template <class K, class V>
bool AVLTree<K, V>::AVLInsert(K key, V val)
{
	//1.根节点为空，直接插入
	if (_root == NULL)
	{
		_root = new AVLNode(key, val);
		return true;
	}
	//2.根节点不为空
	else
	{
		AVLNode* cur = _root;
		AVLNode* parent = NULL;
		//a)找到要插入节点的位置
		while (cur)
		{
			parent = cur;
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else
				return false;   //不允许出现重复元素的节点
		}
		//b)插入新节点
		cur = new AVLNode(key, val);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//c)插入完成后，调整平衡因子
		while (parent)
		{
			if (cur == parent->_left)//插入节点在左子树父节点bf--，反之++
				parent->_bf--;
			else
				parent->_bf++;

			//1)插入新节点后，parent->bf==0;说明高度没变，平衡，返回
			if (parent->_bf == 0)
				break;
			//2)插入节点后parent->_bf==-1||parent->_bf==1;说明子树高度改变，则继续向上调整
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			//3)插入节点后parent->_bf==-2||parent->_bf==2；说明已经不平衡，需要旋转
			else
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
						RotateL(parent);
					else// (cur->_bf == -1)
						RotateRL(parent);
				}
				else//parent->_bf == -2
				{
					if (cur->_bf == -1)
						RotateR(parent);
					else// (cur->_bf == 1)
						RotateLR(parent);
				}
				break;
			}

		}//end while (parent)
		return true;
	}
}

template <class K, class V>
void AVLTree<K, V>::RotateL(AVLNode* parent)
{
	AVLNode*subR = parent->_right;
	AVLNode*subRL = subR->_left;
	AVLNode*pParent = parent->_parent;

	parent->_right = subRL;
	if (subRL)
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
		if (pParent->_left = parent)
			pParent->_left = subR;
		else
			pParent->_right = subR;

		subR->_parent = pParent;
	}
	parent->_bf = subR->_bf = 0;
}

template <class K, class V>
void AVLTree<K, V>::RotateR(AVLNode* parent)
{
	AVLNode* subL = parent->_left;
	AVLNode* subLR = subL->_right;
	AVLNode* ppNode = parent->_parent;

	parent->_left = subLR;
	if (subLR)
		subLR->_parent = parent;

	subL->_right = parent;
	parent->_parent = subL;

	if (_root == parent)
	{
		_root = subL;
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

	subL->_bf = parent->_bf = 0;
}

template <class K, class V>
void AVLTree<K, V>::RotateLR(AVLNode* parent)
{
	AVLNode* subL = parent->_left;
	AVLNode* subLR = subL->_right;
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

template <class K, class V>
void AVLTree<K, V>::RotateRL(AVLNode* parent)
{
	AVLNode* subR = parent->_right;
	AVLNode* subRL = subR->_left;
	int bf = subRL->_bf;

	RotateR(parent->_right);
	RotateL(parent);

	if (bf == 0)
	{
		subRL->_bf = subR->_bf = parent->_bf = 0;
	}
	else if (bf == 1)
	{
		subR->_bf = 0;
		parent->_bf = -1;
		subRL->_bf = 0;
	}
	else if (bf == -1)
	{
		parent->_bf = 0;
		subR->_bf = 1;
		subRL->_bf = 0;
	}
	else
	{
		assert(false);
	}
}


void TestAVLtree() //测试代码
{
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	//{16, 3, 7, 11, 9, 26, 18, 14, 15};
	AVLTree<int, int> t;
	for (size_t i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		t.AVLInsert(a[i], i);
		cout << a[i] << ":" << t.IsBalance() << endl;
	}

	t.InOrder();
	cout << t.IsBalance() << endl;
}


//  二叉搜索树迭代器
class BSTIterator {
public:


	BSTIterator(TreeNode* root) {
		TreeNode* cur = root;
		while (cur != NULL)
		{
			stackNode.push(cur);
			cur = cur->left;
		}
	}

	/** @return the next smallest number */
	int next() {
		TreeNode* cur = stackNode.top();
		stackNode.pop();
		TreeNode* neNode = cur->right;
		while (neNode != NULL)
		{
			stackNode.push(neNode);
			neNode = neNode->left;
		}
		return cur->val;
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !stackNode.empty();
	}



private:
	stack<TreeNode*> stackNode;

};

TreeNode* insertIntoBST(TreeNode* root, int val) {
	TreeNode* pNode = root;

	while (pNode!=NULL)
	{
		if (pNode->val > val)
		{
			if (pNode->left)
			{
				pNode = pNode->left;
			}
			else
			{
				break;
			}
		}
		else if (pNode->val < val)
		{
			
			if (pNode->right)
			{
				pNode = pNode->right;
			}
			else
			{
				break;
			}
		}
		else
			return root;
	}

	TreeNode* p = new TreeNode(val);
	if (p->val>pNode->val)
	{
		pNode->right = p;
	}
	else 
	{
		pNode->left = p;
	}

	return root;


}

TreeNode* deleteNode(TreeNode* root, int key) {
	TreeNode* pNode = root;
	TreeNode* parent,p;

	while (pNode)
	{
		if (pNode->val == key) break;
		parent = pNode;
		if (pNode->val < key) pNode = pNode->right;
		else pNode = pNode->left;
	}
	//没有子节点
	if (pNode->left == NULL&&pNode->right == NULL)
	{
		if (parent->right->val == key)
		{
			parent->right = NULL;
		}
		else if(parent->left->val == key)
		{
			parent->left = NULL;
		}
		delete(pNode);
		return root;
	}
	//有一个子节点
	
	if (pNode->left == NULL&&pNode->right != NULL)
	{
		if (parent->right->val == key)
		{
			parent->right = pNode->right;

		}
		else if (parent->left->val == key)
		{
			parent->left = pNode->right;
		}
		delete(pNode);
		return root;
	}
	if (pNode->left != NULL&&pNode->right == NULL) 
	{
		if (parent->right->val == key)
		{
			parent->right = pNode->left;

		}
		else if (parent->left->val == key)
		{
			parent->left = pNode->left;
		}
		delete(pNode);
		return root;
	}

	//有多个子节点  就要选用中序遍历的后继或者前驱节点
	if (pNode->left != NULL&&pNode->right != NULL) 
	{

	}


}