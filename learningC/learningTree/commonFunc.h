#pragma once
#include <vector>

using namespace std;

int add(int num1, int num2);
int substract(int num1, int num2);
int subtraction(int a, int b);
int multiply(int a, int b);
//int divide(int a, int b);
int divide(int dividend, int divisor);
int negtive(int i);
int getsign(int i);
int bepositive(int i);


template<typename T>
void quicksort(vector<T>& data, int first, int last)
{
	int lower = first + 1;
	int upper = last;
	swap(data[first], data[(first + last) / 2]);
	T bound = data[first];
	while (lower < upper)
	{
		while (lower < last&&data[lower] < bound)
			lower++;
		while (upper >= (first + 1) && data[upper] > bound)
			upper--;
		if (lower < upper)
			swap(data[lower++], data[upper--]);
	}
	swap(data[upper], data[first]);
	if (first < upper - 1)
		quicksort(data, first, upper - 1);
	if (upper + 1 < last)
		quicksort(data, upper + 1, last);
}


class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};


struct RandomListNode {
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :
		label(x), next(NULL), random(NULL) {
	}
};


struct TreeLinkNode {
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

	}
};