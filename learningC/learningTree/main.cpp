#include <iostream>
#include <cstdio>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <algorithm>
#include <math.h>
#include <queue>
#include <functional>
#include "commonFunc.h"
#pragma comment(lib, "Ws2_32")
using namespace std;

void postorderV2(vector<int>& num, Node* node) 
{
	if (node == NULL)
		return;

	if (node->children.size() != 0)
	{
		for (auto child : node->children)
		{
			postorderV2(num, child);
		}
	}
	num.push_back(node->val);
}

vector<int> postorder(Node* root) {
	vector<int> ans;
	postorderV2(ans, root);
	return ans;

}

vector<vector<int>> levelOrder(Node* root) {
	queue<Node *> quetree;
	vector<vector<int>> res;
	if (root == NULL)
	{
		return res;
	}
	quetree.push(root);
	while (!quetree.empty())
	{
		int length = quetree.size();
		vector<int> vec;
		while (length > 0)
		{
			Node *p = quetree.front();
			quetree.pop();
			vec.push_back(p->val);
			for (auto child : p->children)
			{
				quetree.push(child);
			}
			length--;
		}
		res.push_back(vec);
	}
	reverse(res.begin(), res.end());
	return res;
}
vector<vector<int>> nums;
void dfsLevelOrder(Node* node, int level)
{
	if (node == NULL)
		return;

	if (nums.size() < level + 1)
	{
		vector<int>  vec;
		nums.push_back(vec);
	}

	nums[level].push_back(node->val);
	for (auto x : node->children)
	{
		dfsLevelOrder(x, level + 1);
	}


}

vector<vector<int>> levelOrderV2(Node* root) 
{
	dfsLevelOrder(root, 0);
	return nums;
}

TreeNode* searchBST(TreeNode* root, int val) {
	if (root==NULL)
	{
		return NULL;
	}

	if (root->val == val)
	{
		return root;
	}
	else if (root->val<val)
	{
		searchBST(root->right, val);
	}
	else
	{
		searchBST(root->left, val);
	}
	return NULL;
}

int nlz(unsigned x)
{
	int n;

	if (x == 0) return(32);
	n = 1;
	if ((x >> 16) == 0) { n = n + 16; x = x << 16; }
	if ((x >> 24) == 0) { n = n + 8; x = x << 8; }
	if ((x >> 28) == 0) { n = n + 4; x = x << 4; }
	if ((x >> 30) == 0) { n = n + 2; x = x << 2; }
	n = n - (x >> 31);
	return n;
}

int TreeDepth(TreeNode* pRoot)
{
	if (pRoot == NULL)
		return 0;
	return max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1;
}

bool IsBalanced_Solution(TreeNode* pRoot) {
	if (pRoot==NULL)
	{
		return true;
	}
	int LH = TreeDepth(pRoot->left);
	int RH = TreeDepth(pRoot->right);
	if (abs(LH-RH)>1)
	{
		return false;
	}

	return IsBalanced_Solution(pRoot->left) && IsBalanced_Solution(pRoot->right);

}

void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
	map<int, int> mapInt;
	map<int, int>::iterator iter;
	for (int i: data)
	{
		if ((iter=mapInt.find(i))!=mapInt.end())
		{
			mapInt.erase(i);
		}
		else
		{
			mapInt.insert({ i,1 });
		}
	}
	*num1 = *num2 =0;
	iter = mapInt.begin();
	for (int i = 0;i<data.size();i++)
	{
		if (iter->first==data[i])
		{
			*num1 = data[i];
			break;
		}
	}
	iter++;
	for (int i = 0; i < data.size(); i++)
	{
		if (iter->first == data[i])
		{
			*num2 = data[i];
			break;
		}
	}
}

vector<vector<int> > FindContinuousSequence(int sum) {
	int maxNum = sum / 2 + 1;
	vector<int>  vecInt;
	vector<vector<int>> vecIntS;
	int term = 0;
	for (int i=1;i<=maxNum;i++)
	{
		term += i;
		vecInt.push_back(i);
		cout << " add " << i << "        sum :" << term << "    pushback    " << i << endl;
        while (term>sum)
			{
				term -= vecInt[0];
				cout << "bigger than result" << "  erase   " << vecInt[0] << "sum:  " << term << endl;
				vecInt.erase(vecInt.begin());
				

			}

			if (term == sum)
			{
				if (vecInt.size() >= 2)
				    vecIntS.push_back(vecInt);
				term -= vecInt[0];
				cout << "find one result. pushback!" << "  erase    " << vecInt[0]  << endl;
				vecInt.erase(vecInt.begin());
			}
	}
	return vecIntS;
}

vector<int> FindNumbersWithSum(vector<int> array, int sum) {
	int term = 0; 
	int size = array.size();
	int i = 0;
	int j = size - 1;
	vector<int> res;
	for (;i<j;)
	{
		term = array[i] + array[j];
		if (term > sum)
			j--;
		else if (term < sum)
			i++;
		else 
		{
			res.push_back(array[i]);
			res.push_back(array[j]);
			break;
		}
	}
	return res;
}

string LeftRotateString(string str, int n) {
	if (str.size() == 0)
		return str;
	n = n%str.size();
	if (n == 0) return str;
	string term = "";
	for (int i=0;i<n;i++)
	{
		term+=str[i];
	}
	for (int j=n;j<str.size();j++)
	{
		str[j - n] = str[j];
	}
	int j = 0;
	int i = str.size() - n;
	for (;i<str.size();i++,j++)
	{
		str[i] = term[j];
	}
	return str;
}

string ReverseSentence(string str) {
	if (str.size()==0)
	{
		return str;
	}
	str += " ";
	vector<string> vec;
	int i = 0;
	int j = 0;
	bool flag = false;
	for (;j<str.size();j++)
	{
		if (str[j] == ' ')
		{
			string term = str.substr(i, j - i);
			vec.push_back(term);
			flag = true;
		}
		else 
		{
			if (flag)
			{
				i = j;
				flag = false;
			}
		}
	}
	reverse(vec.begin(), vec.end());
	string s;
	for (i = 0; i < vec.size(); i++)
	{
		s+=vec[i];
		if (i!=vec.size()-1)
		{
			s += " ";
		}
	}
	return s;
}

string ReverseSentenceV2(string str) 
{
	int size = str.size();
	reverse(str.begin(), str.end());
	int s = 0;
	for (int i=0;i<size;i++)
	{
		if (str[i] == ' ') 
		{
			reverse(str.begin() + s, str.begin() + i);
			s = i + 1;
		}
		if (i == size - 1) 
		{
			reverse(str.begin() + s, str.end());
		}

	}
	return str;
}
void coutVec2d(vector<vector<int>> vec) 
{
	for (int i=0;i<vec.size();i++)
	{
		for (int j=0;j<vec[i].size();j++)
		{
			cout << vec[i][j] << "  ";
		}
		cout << endl;
	}
}

void coutVec1d(vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << "  ";
		
	}
	cout << endl;
}

bool IsContinuous(vector<int> numbers) {
	if (numbers.size()<5)
	{
		return false;
	}
	int max = -1;
	int min = 14;
	map<int, int> mapInt;
	map<int, int>::iterator iter;
	for (int i : numbers) 
	{
		if (i != 0)
		{
			if ((iter = mapInt.find(i)) != mapInt.end())
		    {
			return false;
		    } 
		mapInt.insert({ i,1 });

			max = i > max ? i : max;
			min = i < min ? i : min;
		}
	}
	int cha =max-min;
	if (cha<5)
	{
		return true;
	}
	return false;
}

bool Find(int target, vector<vector<int> > array) {
	int  i, j;
	for (i = 0, j = array[0].size() - 1; i < array.size()&& j >= 0;)
	{
		if (array[i][j]==target)
		{
			return true;
		}
		 else if (array[i][j]>target)
		{
			j--;
		}
		 else
		{
			 i++;
		}
	}
	return false;
}

void replaceSpace(char *str, int length) {
	if (str == NULL)
		return;
	int blanks = 0;
	int originlen = 0;
	for (int i = 0;str[i] != '\0';i++)
	{
		originlen++;
		if (str[i]==' ')
		{
			blanks++;
		}
	}
	int len = originlen + 2 * blanks;
	if (len+1>length)
	{
		return;
	}

	char*pStr1 = str + originlen;
	char*pStr2 = str + len;

	while (pStr1<pStr2)
	{
		if (*pStr1==' ')
		{
			*pStr2-- = '0';
			*pStr2-- = '2';
			*pStr2-- = '%';
		}
		else 
		{
			*pStr2-- = *pStr1;
		}
		pStr1--;
	}
}

vector<int> printListFromTailToHead(ListNode* head) {
	vector<int> vec;
	while (head!=NULL)
	{
		vec.push_back(head->val);
		head = head->next;
	}
	reverse(vec.begin(), vec.end());
	return vec;
}

TreeNode* R(vector<int> a, int abegin, int aend, vector<int> b, int bbegin, int bend)
{
	if (abegin >= aend || bbegin >= bend)
		return NULL;
	TreeNode* root = new TreeNode(a[abegin]);
	int pivot;
	for (pivot = bbegin; pivot < bend; pivot++)
		if (b[pivot] == a[abegin])
			break;
	root->left = R(a, abegin + 1, abegin + pivot - bbegin + 1, b, bbegin, pivot);
	root->right = R(a, abegin + pivot - bbegin + 1, aend, b, pivot + 1, bend);
	return root;
}

TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
	return R(pre, 0, pre.size(), vin, 0, vin.size());
}

int minNumberInRotateArray(vector<int> rotateArray) {
	if (rotateArray.size()==0)
	{
		return 0;
	}
	int temp = 0;
	for (temp =0; temp<rotateArray.size()-1; temp++)
	{
		if (rotateArray[temp]>rotateArray[temp+1])
		{
			break;
		}
	}
	reverse(rotateArray.begin(), rotateArray.begin() + temp + 1);
	reverse(rotateArray.begin() + temp + 1, rotateArray.end());
	reverse(rotateArray.begin(), rotateArray.end());
	return rotateArray[0];
}

int Fibonacci(int n) {

	if (n == 0)
		return 0;

	if (n == 1)
		return 1;
	int first = 0;
	int second = 1;
	int result = 0;
	n -= 2;
	while (n >= 0)
	{
		result = first + second;
		first = second;
		second = result;
		n--;
	}

	return result;
}

int LastRemaining_Solution(int n, int m)
{
	vector<int> vec;
	for (int i = 0; i < n; i++) 
	{
		vec.push_back(i);
	}
	int iter = 0;
	while (n > 1)
	{
		int index = m%n-1;
		if (index < 0)
			index += n;
		int size = vec.size();
		if ((iter+index)>=size)
		{
			iter = index- (size - iter);
		}
		else 
		{
			iter = iter + index;
		}
		//if (iter == -1)  iter = 0;
		vec.erase(vec.begin() + iter);
		n--;
	}
	return vec[0];
}

int LastRemaining_SolutionV2(int n, int m)
{
	if (n == 0) return -1;
	int s = 0;
	for (int i = 2; i <= n; i++) {
		s = (s + m) % i;
	}
	return s;
}

int Sum_Solution(int n) {
	int ans = n;
	bool b= (n > 0) && ((ans += Sum_Solution(n-1))>0);
	return ans;
}

int jumpFloor(int number) {
	if (number == 0||number==1) return 1;

	return jumpFloor(number - 1) + jumpFloor(number - 2);
	
}

int jumpFloorII(int number) {
	if (number == 0 || number == 1) return 1;
	int num = 0;
	for (int i=1;i<=number;i++) 
	{
		num += jumpFloorII(number - i);
	}
	return num;

}

int rectCover(int n) {

	if (n == 0) return 0;
	if (n == 1) return 1;
	int f = 1;
	int s = 2;
	int res = 2;
	n -= 2;
	while (n > 0)
	{
		res = f + s;
		f = s;
		s = res;
		n--;
	}
	return res;

}

int Add(int a, int b)
{
	if (b == 0)
		return a;
	int sum, ret;
	sum = a^b;
	ret = (a & b) << 1;
	return Add(sum, ret);
}

int  NumberOf1(int n) {
	int count = 0;
	while (n!=0)
	{
		n = (n - 1)&n;
		count++;
	}
	return count;
}

double Power(double base, int exponent) {
	double res = 1;
	int n;
	if (exponent == 0) return 1;
	if (exponent > 0)
	{
		n = 1;
	}
	else
	{
		exponent = -exponent;
		n = -1;
		if (base==0)
		{
			return 0;
		}
	}
	// v1
	//while (exponent!=0)
	//{
	//	if (exponent&1)
	//	{
	//		res *= base;
	//	}
	//	base *= base;
	//	exponent >>= 1;
	//}


//v2
	while (exponent!=0)
	{
		res *= base;
		exponent--;
	}
	return n > 0 ? res : (1 / res);
}


void reOrderArray(vector<int> &array) {
	vector<int> vec;
	int last = 0;
	for (int i = 0; i < array.size(); i++) 
	{
		if (array[i]%2==1)
		{
			array[last] = array[i];
			last++;
			
		}
		else
		{
			vec.push_back(array[i]);
		}
	}

	for (int i=0;i<vec.size();i++)
	{
		array[last] = vec[i];
		last++;
	}
}

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
	queue<ListNode*> q;
	while (pListHead!=NULL)
	{
		if (q.size() != k)
		{
			q.push(pListHead);
		}
		else 
		{
			q.pop();
			q.push(pListHead);
		}
		pListHead = pListHead->next;
	}
	
	if (q.size()<k)
	{
		return NULL;
	}
	
	return q.front();
}

ListNode* ReverseList(ListNode* pHead) {
	if (pHead == NULL)  return pHead;
	ListNode* prev = NULL;
	ListNode *next = NULL;
	while (pHead)
	{
		next = pHead->next;
		pHead->next = prev;
		prev = pHead;
		pHead = next;
	}
	return prev;
}
//////////////////////////////////////////////////////////////////////////////
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == NULL)
		return pHead2;
	if (pHead2 == NULL)
		return pHead1;
	ListNode* head = pHead1;
	if (pHead1->val>pHead2->val)
	{
		int temp = pHead2->val;
		pHead2->val = pHead1->val;
		pHead1->val = temp;
	}
	while (pHead2!=NULL&&pHead1!=NULL)
	{
		ListNode* next = pHead1->next;
		if (next==NULL)
		{
			if (pHead2->val >= pHead1->val)
			{
				pHead1->next = pHead2;
				//pHead2 = pHead2->next;
				break;
			}
		}
		else 
		{
			if (pHead2->val >= pHead1->val&&pHead2->val<=next->val)
			{
				pHead1->next = pHead2;
				pHead2 = pHead2->next;
				pHead1->next->next = next;
			}
		}
		pHead1 = pHead1->next;
	}
	if (pHead2!=NULL)
	{
		pHead1->next = pHead2;
	}
	return head;
}
/////////////////////////////////////////////////////////////////////////
bool isSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
	if (pRoot2 == NULL) return true;
	if (pRoot1 == NULL) return false;
	if (pRoot1->val == pRoot2->val)
		return isSubtree(pRoot1->left, pRoot2->left) && isSubtree(pRoot1->right, pRoot2->right);
	else
		return false;
}

bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
	if (pRoot2 == NULL||pRoot1==NULL)  return false;
	return isSubtree(pRoot1, pRoot2) || HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
}
//////////////////////////////////////////////////////////////////////////
void Mirror(TreeNode *pRoot) {
	if (!pRoot) return;
	TreeNode* temp = pRoot->left;
	pRoot->left = pRoot->right;
	pRoot->right = temp;
	if (pRoot->left) Mirror(pRoot->left);
	if (pRoot->right) Mirror(pRoot->right);
}
//////////////////////////////////////////////////////////////////////////////////////
void circleMatrix(vector<vector<int>>& matrix, vector<int>& vec,int leftI,int LeftJ,int rightI,int rightJ) 
{
	vec.push_back(matrix[leftI][LeftJ]);
    if (leftI==rightI&&LeftJ==rightJ)
		return;
	int i, j;
	if (LeftJ==rightJ)
	{
		for (j = LeftJ,i = leftI+1; i <= rightI;i++)
		{
			vec.push_back(matrix[i][j]);
		}
		return;
	}
	if (leftI == rightI)
	{
		for (i = leftI,j = LeftJ+1; j <= rightJ; j++)
		{
			vec.push_back(matrix[i][j]);
		}
		return;
	}

	bool f=true;
	bool r = true;
	j = LeftJ + 1;
	if (j == rightJ) f = false;
	for (i = leftI;i!=leftI||j!=LeftJ;)
	{
		
		vec.push_back(matrix[i][j]);

		if (r)
		{
			if (f)
			{
				j++;
				if (j == rightJ) f = false;
			}
			else
			{
				i++;
				if (i == rightI) f = true;
			}

			if (j == rightJ&&i == rightI)
			{
				r = false;
			}
		}
		else 
		{
			if (f)
			{
				j--;
				if (j == LeftJ) f = false;
			}
			else
			{
				i--;
				if (i == leftI) f = true;
			}
		}
	}
}

vector<int> printMatrix(vector<vector<int> > matrix) {
	vector<int> vec;
	int w, h,i,j;
	w = matrix[0].size()-1;
	h = matrix.size()-1;
	i = 0;
	j = 0;
	while (i<=h&&j<=w)
	{
		circleMatrix(matrix, vec, i, j, h, w);
		i++;
		j++;
		w--;
		h--;
	}
	return vec;
}

vector<int> printMatrixV2(vector<vector<int> > matrix) {
		int row = matrix.size();
		int col = matrix[0].size();
		vector<int> res;

		// 输入的二维数组非法，返回空的数组
		if (row == 0 || col == 0)  return res;

		// 定义四个关键变量，表示左上和右下的打印范围
		int left = 0, top = 0, right = col - 1, bottom = row - 1;
		while (left <= right && top <= bottom)
		{
			// left to right
			for (int i = left; i <= right; ++i)  res.push_back(matrix[top][i]);
			// top to bottom
			for (int i = top + 1; i <= bottom; ++i)  res.push_back(matrix[i][right]);
			// right to left
			if (top != bottom)
				for (int i = right - 1; i >= left; --i)  res.push_back(matrix[bottom][i]);
			// bottom to top
			if (left != right)
				for (int i = bottom - 1; i > top; --i)  res.push_back(matrix[i][left]);
			left++, top++, right--, bottom--;
		}
		return res;
}
///////////////////////////////////////////////////////////////
bool IsPopOrder(vector<int> pushV, vector<int> popV) {
	if (pushV.size() == 0) return true;
	stack<int> stackInt;
	int size = pushV.size();
	int i = 1;
	int j = 0;
	stackInt.push(pushV[0]);
	while (stackInt.size() != 0 || i < size)
	{
		if (stackInt.empty())
		{
			stackInt.push(pushV[i]);
			i++;
		}
		
		if (stackInt.top() == popV[j])
		{
			stackInt.pop();
			j++;
		}
		else if(i<size)
		{
			stackInt.push(pushV[i]);
			i++;
		}
		else
		{
			return false;
		}
	}
	return true;
}
/////////////////////////////////////////////////////////////
vector<int> PrintFromTopToBottom(TreeNode* root) {
	queue<TreeNode *> quetree;
	vector<int> res;
	if (root == NULL)
	{
		return res;
	}
	quetree.push(root);
	while (!quetree.empty())
	{
		int length = quetree.size();
		while (length > 0)
		{
			TreeNode *p = quetree.front();
			quetree.pop();
			res.push_back(p->val);
			if (p->left) quetree.push(p->left);
			if (p->right) quetree.push(p->right);

			length--;
		}
	}
	return res;
}
/////////////////////////////////////////////////////////////
bool getResOfBSTTree(vector<int> vec, int s, int e) 
{
	int i = 0;
	int j = 0;
	if (e - s <= 1) return true;
	for (i = s;i<e;i++)
	{
		if (vec[i] > vec[e]) break;
	}
	for (j = i; j < e; j++) 
	{
		if (vec[j] < vec[e]) return false;
	}
	bool left = true;
	bool right = true;
	if (i>0) left = getResOfBSTTree(vec, s, i - 1);
	if (i < vec.size() - 1) right = getResOfBSTTree(vec, i, e - 1);

	return left&&right;
}

bool VerifySquenceOfBST(vector<int> sequence) {
	if (sequence.size() == 0) return false;
	return getResOfBSTTree(sequence, 0, sequence.size() - 1);
}
///////////////////////////////////////////////////////////
vector<vector<int> >  res;
vector<int> vec;
vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
	if (root == NULL) return res;
	vec.push_back(root->val);
	if (expectNumber - root->val == 0 && root->left == NULL&&root->right == NULL) res.push_back(vec);
	if (root->left) FindPath(root->left, expectNumber - root->val);
	if (root->right) FindPath(root->right, expectNumber - root->val);
	if (vec.size() != 0) vec.pop_back();
	return res;
}
//////////////////////////////////////////////////////////////////////////
/*
struct RandomListNode {
int label;
struct RandomListNode *next, *random;
RandomListNode(int x) :
label(x), next(NULL), random(NULL) {
}
};
*/
void cloneNode(RandomListNode* pHead) 
{
	RandomListNode* pNode = pHead;
	while (pNode)
	{
		RandomListNode* p = new RandomListNode(pNode->label);
		p->next = pNode->next;
		pNode->next = p;
		pNode = p->next;
	}
}
void connectRandomNode(RandomListNode* pHead) 
{
	RandomListNode* pNode = pHead;
	RandomListNode* pClone = pHead->next;
	while (pNode)
	{
		if (pNode->random)
		{
			pClone->random = pNode->random->next;
		}
		pClone = pClone->next->next;
		pNode = pNode->next->next;
	}
}
RandomListNode* reconnectNode(RandomListNode* pHead) 
{
	////////////// v1
	//RandomListNode* pNode = pHead;
	//RandomListNode *pCloneHead = pHead->next;
	//while (pNode)
	//{
	//	RandomListNode* pClone = pNode->next;
	//	pNode->next = pClone->next;
	//	pNode = pNode->next;
	//	if (pNode)
	//	{
	//		pClone->next = pNode->next;
	//	}
	//}
	///////////////////////////v2
	RandomListNode* tmp;
	RandomListNode *pCloneHead = pHead->next;
	RandomListNode* curNode = pHead;
	while (curNode->next) 
	{
		tmp = curNode->next;
		curNode->next = tmp->next;
		curNode = tmp;
	}
	return pCloneHead;
}
RandomListNode* Clone(RandomListNode* pHead)
{
	if (pHead == NULL) return NULL;
	cloneNode(pHead);
	connectRandomNode(pHead);
	return reconnectNode(pHead);

}
////////////////////////////////////////////////

TreeNode* Convert(TreeNode* pRootOfTree)
{
	stack<TreeNode*> stNode;
	TreeNode* pNode = pRootOfTree;
	TreeNode* Pre = NULL;
	TreeNode* Phead;
	while (pNode!=NULL||!stNode.empty())
	{
		if (pNode!=NULL)
		{
			stNode.push(pNode);
			pNode = pNode->left;
		}
		else 
		{
			TreeNode* node = stNode.top();
			stNode.pop();
			if (Pre==NULL)
			{
				Pre = node;
				Phead = node;
			}
			else 
			{
				Pre->right = node;
				node->left = Pre;
				Pre = node;
			}
			pNode = node->right;
		}
	}
	return Phead;
}
//////////////////////////////////////////////////////
void Permutation1(string str, vector<string>& vecStr, int begin) 
{
	if (begin == str.size())
	{
		vecStr.push_back(str);
		return;
	}
	for (int i=begin;str[i]!='\0';i++)
	{
		if (i != begin&&str[begin] == str[i])
			continue;
		swap(str[begin], str[i]);
		Permutation1(str, vecStr, begin + 1);
		swap(str[begin], str[i]);
	}
}

vector<string> Permutation(string str) {
	vector<string>  vecStr;
	if (str.size() == 0) return vecStr;
	Permutation1(str, vecStr, 0);
	sort(vecStr.begin(), vecStr.end());
	return vecStr;
}

/////////////////////////////////////////////////////////
int MoreThanHalfNum_Solution(vector<int> numbers) {
	if (numbers.size() == 0) return 0;
	int num, count;
	num = 0;
	count = 0;
	for (int n:numbers)
	{
		if (num==n)
		{
			count++;
		}
		else if (num!=n&&count!=0)
		{
			count--;
		}
		else if (num!=n&&count==0)
		{
			num = n;
			count++;
		}
	}
	count = 0;
	for (int n:numbers)
	{
		if (n==num)
		{
			count++;
		}
	}
	return count * 2 > numbers.size() ? num : 0;
}
/////////////////////////////////////////////////////////

int Partition_index(vector<int>& vec, int begin, int end) 
{
	int low = begin;
	int high = end;
	int p = vec[low];
	while (low<high)
	{
		while (low < high&&p <= vec[high])
			high--;
		vec[low] = vec[high];
		while (low < high&&p >= vec[low])
			low++;
		vec[high] = vec[low];
	}
	vec[low] = p;
	return low;
}


vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
	
	if (input.size() < k) return vector<int>();
	if (input.size() == k) return input;

	int start = 0;
	int end = input.size() - 1;
	int index = Partition_index(input, start, end);
	while (index!=(k-1))
	{
		if (index<(k-1))
		{
			start = index + 1;
			index = Partition_index(input, start, end);
		}
		else if (index>(k-1))
		{
			end = index - 1;
			index = Partition_index(input, start, end);
		}
	}
	
	vector<int> vec(input.begin(), input.begin() + k);
	sort(vec.begin(), vec.end());
	return vec;
}
//法2  待理解
vector<int> GetLeastNumbers_Solution_v2(vector<int> input, int k) 
{
	int len = input.size();
	if (len <= 0 || k > len) return vector<int>();

	//仿函数中的greater<T>模板，从大到小排序
	multiset<int, greater<int> > leastNums;
	vector<int>::iterator vec_it = input.begin();
	for (; vec_it != input.end(); vec_it++)
	{
		//将前k个元素插入集合
		if (leastNums.size() < k)
			leastNums.insert(*vec_it);
		else
		{
			//第一个元素是最大值
			multiset<int, greater<int> >::iterator greatest_it = leastNums.begin();
			//如果后续元素<第一个元素，删除第一个，加入当前元素
			if (*vec_it < *(leastNums.begin()))
			{
				leastNums.erase(greatest_it);
				leastNums.insert(*vec_it);
			}
		}
	}

	return vector<int>(leastNums.begin(), leastNums.end());
}


///////////////////////////////////////////////////////////////////
int FindGreatestSumOfSubArray(vector<int> array) {
	if (array.size() == 0) return 0;
	int max = -100;
	int sum = 0;
	
	for (int n:array)
	{
		sum += n;
		if (max<=sum)
		{
			max = sum;
		}
		if (sum<0)
		{
			sum = 0;
		}
	}
	return max;
}

///////////////////////////////////////////////////////////////////
int NumberOf1Between1AndN_Solution(int n)
{
	//主要思路：设定整数点（如1、10、100等等）作为位置点i（对应n的各位、十位、百位等等），分别对每个数位上有多少包含1的点进行分析
	//根据设定的整数位置，对n进行分割，分为两部分，高位n/i，低位n%i
	//当i表示百位，且百位对应的数>=2,如n=31456,i=100，则a=314,b=56，此时百位为1的次数有a/10+1=32（最高两位0~31），每一次都包含100个连续的点，即共有(a%10+1)*100个点的百位为1
	//当i表示百位，且百位对应的数为1，如n=31156,i=100，则a=311,b=56，此时百位对应的就是1，则共有a%10(最高两位0-30)次是包含100个连续点，当最高两位为31（即a=311），本次只对应局部点00~56，共b+1次，
	//所有点加起来共有（a%10*100）+(b+1)，这些点百位对应为1
	//当i表示百位，且百位对应的数为0,如n=31056,i=100，则a=310,b=56，此时百位为1的次数有a/10=31（最高两位0~30）
	//综合以上三种情况，当百位对应0或>=2时，有(a+8)/10次包含所有100个点，还有当百位为1(a%10==1)，需要增加局部点b+1
	//之所以补8，是因为当百位为0，则a/10==(a+8)/10，当百位>=2，补8会产生进位位，效果等同于(a/10+1)
	int count = 0;
	long long i = 1;
	for (i = 1; i <= n; i *= 10)
	{
		//i表示当前分析的是哪一个数位
		int a = n / i, b = n%i;
		count = count + (a + 8) / 10 * i + (a % 10 == 1)*(b + 1);
	}
	return count;
}

/////////////////////////////////////////////////////////////////////
bool pibjie(int a, int b)
{
	string A = "";
	string B = "";
	A += to_string(a);
	A += to_string(b);
	B += to_string(b);
	B += to_string(a);
	return A < B;
}
string PrintMinNumber(vector<int> numbers) {
	if (numbers.size() == 0) return "";
	if (numbers.size() == 1) return to_string(numbers[0]);
	string str="";
	sort(numbers.begin(), numbers.end());
	long long a, b;
	a = numbers[0];
	for (int i = 1; i < numbers.size(); i++) 
	{
		b = numbers[i];
        if (pibjie(a,b))
        {
			a = a*pow(10,to_string(b).size()) + b;
        }
		else
		{
			a = b*pow(10,to_string(a).size()) + a;
		}
	}
	return to_string(a);
}

string PrintMinNumber_v2(vector<int> numbers) {
	string  answer = "";
	sort(numbers.begin(), numbers.end(), pibjie);   //sort可以自己定制排序规则  排序规则必须要是静态函数
	for (int i = 0; i < numbers.size(); i++) {
		answer += to_string(numbers[i]);
	}
	return answer;
}
////////////////////////////////////////////////////////////////////
int GetUglyNumber_Solution(int index) {            //丑数   都是由2，3，5为因子组成
	if (index < 7)return index;
	vector<int> res(index);
	res[0] = 1;
	int t2 = 0, t3 = 0, t5 = 0, i;
	for (i = 1; i < index; ++i)
	{
		res[i] = min(res[t2] * 2, min(res[t3] * 3, res[t5] * 5));
		if (res[i] == res[t2] * 2)t2++;
		if (res[i] == res[t3] * 3)t3++;
		if (res[i] == res[t5] * 5)t5++;
	}
	return res[index - 1];
}
///////////////////////////////////////////////////////////////////
int FirstNotRepeatingChar(string str) {
	if (str.size() == 0) return -1;
	map<char, int> mapChar;
	map<char, int>::iterator it;
	for (int i = 0;i<str.size();i++)
	{
		char c = str[i];
		it = mapChar.find(c);
		if (it!=mapChar.end())
		{
			mapChar[c] = -1;
		}
		else
		{
			mapChar[char(c)] = i;
		}
	}
	int min =10000;
	for (auto ch:mapChar)
	{
		int index = ch.second;
		if (index >=0)
		{
			min = min < index ? min : index;
		}
	}
	return min;
}

int FirstNotRepeatingCharv2(string str)
{
	int len = str.size();
	if (len <= 0)
		return -1;
	int cnt[100] = { 0 };
	int i, res = -1;
	for (i = 0; i < len; i++)
	{
		cnt[str[i] - 'A']++;
	}
	for (i = 0; i < len; i++)
	{
		if (cnt[str[i] - 'A'] == 1)
		{
			res = i;
			break;
		}
	}
	return res;
}

/////////////////////////////////////////////////////////
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
	int len1 = 0, len2 = 0;
	ListNode* p1 = pHead1;
	ListNode* p2 = pHead2;

	while (p1)
	{
		len1++;
		p1 = p1->next;
	}
	while (p2) 
	{
		len2++;
		p2 = p2->next;
	}
	int d = len1 - len2;
	if (d>0)
	{
		p1 = pHead1;
		p2 = pHead2;
	}
	else
	{
		d = -d;
		p1 = pHead2;
		p2 = pHead1;
	}

	for (int i=0;i<d;i++)
	{
		p1 = p1->next;
	}

	while (p1!=NULL&&p2!=NULL)
	{
		if (p1 == p2)
			break;
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}

//////////////////////////////////////////////////////////////////
//查找某个有序数组的某个数字的出现字数
int GetNumberOfK(vector<int> data, int k) 
{
	if (data.size() == 0) return 0;
	int begin = 0;
	int end = data.size() - 1;
	int m = 0;
	int n = 0;
	while (begin <= end)
	{
		m = (begin + end) / 2;
		if (data[m] > k)
		{
			end = m - 1;
		}
		else if (data[m] < k)
		{
			begin = m + 1;
		}
		else
		{
			break;
		}
	}
	if (data[m] == k)
	{
		n = m;
		while (m >= 0)
		{
			if (data[m] == k)
			{
				m--;
			}
			else {
				m++;
				break;
			}
		}
		if (m == -1) m++;
		while (n < data.size())
		{
			if (data[n]==k)
			{
				n++;
			}
			else
		        break;
		}
	}
	else 
	{
		return 0;
	}
	return n - m;
}
///////////////////////////////////////////////////////////////////////////
int StrToInt(string str) {
	if (str.size() == 0) return 0;
	int sum = 0;
	bool flag = true;
	for (char c : str)
	{
		if (c=='-')
		{
			flag = false;
		}
		else if (c=='+')
		{
		    flag = true;
		}
		else if (c>='0'&&c<='9')
		{
			sum = sum * 10 + (c - '0');
		}
		else
		{
			return 0;
		}
	}
	if (flag) return sum;
	else return -sum;
}
////////////////////////////////////////////////////////////////
// Parameters:
//        numbers:     an array of integers
//        length:      the length of array numbers
//        duplication: (Output) the duplicated number in the array number
// Return value:       true if the input is valid, and there are some duplications in the array number
//                     otherwise false
bool duplicate(int numbers[], int length, int* duplication) {
	vector<int> vec(length);
	for (int i=0;i<length;i++)
	{
		vec[numbers[i]]++;
	}
	for (int i = 0; i < length; i++)
	{
		if (vec[numbers[i]]>1)
		{
			*duplication = numbers[i];
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////
//给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。不能使用除法。
vector<int> multiply(const vector<int>& A) {
	int sum = 1;
	vector<int> res(A.size());
	int index, count = 0;
	for (int i = 0;i<A.size();i++)
	{
		int a = A[i];
		if (a==0)
		{
			index = i;
			count++;
			
		}
		else
		{
			sum *= a;
		}
	}
	if (count>1)
	{
		return res;
	}
	else if (count==1)
	{
		res[index] = sum;
	}
	else
	{
		for (int i = 0; i<A.size(); i++)
		{
			int a = A[i];
			int d = divide(sum, a);
			res[i] = d;
		}
	}

	return res;
}

//方法2
vector<int> multiplyv2(const vector<int>& A) 
{
	int n = A.size();
	vector<int> b0(n, 1);
	vector<int> b1(n, 1);
	for (int i=1;i<n;i++)
	{
		b0[i] = b0[i - 1] * A[i - 1];
	}
	for (int i = n-2;i>=0;i--)
	{
		b1[i] = b1[i + 1] * A[i + 1];
	}
	vector<int> b(n, 1);
	for (int i =0;i<n;i++)
	{
		b[i] = b0[i] * b1[i];
	}
	return b;
}
///////////////////////////////////////////////////////////////////
//请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 
//在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配
/*
	首先，考虑特殊情况：
	1>两个字符串都为空，返回true
	2>当第一个字符串不空，而第二个字符串空了，返回false（因为这样，就无法
	匹配成功了,而如果第一个字符串空了，第二个字符串非空，还是可能匹配成
	功的，比如第二个字符串是“a*a*a*a*”,由于‘*’之前的元素可以出现0次，
	所以有可能匹配成功）
	之后就开始匹配第一个字符，这里有两种可能：匹配成功或匹配失败。但考虑到pattern
	下一个字符可能是‘*’， 这里我们分两种情况讨论：pattern下一个字符为‘*’或
	不为‘*’：
	1>pattern下一个字符不为‘*’：这种情况比较简单，直接匹配当前字符。如果
	匹配成功，继续匹配下一个；如果匹配失败，直接返回false。注意这里的
	“匹配成功”，除了两个字符相同的情况外，还有一种情况，就是pattern的
	当前字符为‘.’,同时str的当前字符不为‘\0’。
	2>pattern下一个字符为‘*’时，稍微复杂一些，因为‘*’可以代表0个或多个。
	这里把这些情况都考虑到：
	a>当‘*’匹配0个字符时，str当前字符不变，pattern当前字符后移两位，
	跳过这个‘*’符号；
	b>当‘*’匹配1个或多个时，str当前字符移向下一个，pattern当前字符
	不变。（这里匹配1个或多个可以看成一种情况，因为：当匹配一个时，
	由于str移到了下一个字符，而pattern字符不变，就回到了上边的情况a；
	当匹配多于一个字符时，相当于从str的下一个字符继续开始匹配）
	之后再写代码就很简单了。
*/
bool match(char* str, char* pattern)
{
	if (*str == '\0' && *pattern == '\0')
		return true;
	if (*str != '\0' && *pattern == '\0')
		return false;

	if (*(pattern+1)!='*')
	{
		if (*str == *pattern || (*str != '\0'&&*pattern == '.'))
			return match(str + 1, pattern + 1);
		else
			return false;
	}
	else 
	{
		if (*str == *pattern || (*str != '\0'&&*pattern == '.')) 
		{
			return match(str, pattern + 2) || match(str + 1, pattern);
		}
		else
		{
			return match(str, pattern + 2);
		}
	}
}

//请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。
//但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。
//首先判断是否有符号（ + 或者 - ），如果有，则对后面的字符串判断
//首先需要扫描数字直到结束或是遇到其他字符，结束则返回true，否则继续按情况判断下一个需要判断的字符
//
//如果是小数点'.'，是则扫描数字，直到结束（返回true）或者遇到特殊字符，如果是e或E，那么对后面的数判断是否符合指数表示，如果是其他字符则返回false。
//如果是e或者E，那么对后面的数判断是否符合指数表示。
//如果不符合上面的情况则返回false
//指数判断：
//首先判断是否是符号，如果是，跳到下一位判断后面的是否是数字组成的串，是则表示指数表示是正确的，否则是不正确的。
int indexOfStr(char* string) 
{
	int index = 0;
	while (*string >= '0'&&*string <= '9')
	{
		index++;
		string++;
	}
	return index;
}

bool isExponential(char* string) 
{
	if (*string!='\0')
	{
		if (*string == '+' || *string == '-') string++;
		int index = indexOfStr(string);
		string += index;
		if (*string == '\0') return true;
		return false;
	}
	return false;
}

bool isNumeric(char* string)
{
	if (string == NULL) return false;
	if (*string == '+' || *string == '-')
		string++;
	if (*string == '\0') return false;
	int index = indexOfStr(string);
	string += index;
	if (*string!='\0')
	{
		if (*string =='.')
		{
			string++;
			int index2 = indexOfStr(string);
			string += index2;
			if (*string!='\0')
			{
				if (*string=='e'||*string=='E')
				{
					string++;
					return isExponential(string);
				}
				return false;
			}
			return true;
		}
		else if (*string == 'e' || *string == 'E')
		{
			string++;
			return isExponential(string);
		}
		return false;
	}
	return true;

}

//请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。
//当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。
//Insert one char from stringstream
string strForFirstAppear="";
//vector<int> countOfChars(128,0);  这句不行  换成下一句可以  //不知道为什么
int countOfChars[128] = { 0 };
void Insert(char ch)
{
	strForFirstAppear += ch;
	countOfChars[ch]++;
}
//return the first appearence once char in current stringstream
char FirstAppearingOnce()
{
	int size = strForFirstAppear.size();
	for(int i=0;i<size;i++)
	{
		if (countOfChars[strForFirstAppear[i]] == 1) return strForFirstAppear[i];
	}
	return '#';
}

//给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。
//https://www.nowcoder.com/questionTerminal/253d2c59ec3e4bc68da16833f79a38e4
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	if (pHead == NULL||pHead->next==NULL) return NULL;
	ListNode* p1 = pHead;
	ListNode* p2 = pHead;

	while (p1->next!=NULL&&p2->next!=NULL)
	{
		p1 = p1->next;
		p2 = p2->next->next;
		if (p1==p2)
		{
			p2 = pHead;
			while (p1!=p2)
			{
				p1 = p1->next;
				p2 = p2->next;
			}
			if (p1==p2)
			{
				return p1;
			}
		}
	}
	return NULL;
}

//在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 
//例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
ListNode* deleteDuplication(ListNode* pHead)
{
	if (pHead == NULL || pHead->next == NULL) return pHead;
	bool flag = false;
	bool head = false;
	ListNode* pre = pHead;
	ListNode* pNode = pHead;
	

	while (pNode->next!=NULL)
	{
		if (pNode->val== pNode->next->val)
		{
			flag = true;
			pNode->next = pNode->next->next;
		}
		else
		{
			if (head)
			{
				if (flag)
				{
					flag = false;
					pre->next = pNode->next;
				}
				else
				{
					pre = pNode;
				}
			}
			else
			{
				if (flag)
				{
					flag = false;
				}
				else
				{
					pHead = pNode;
					head = true;
					pre = pHead;
				}
			}
			pNode = pNode->next;

		}
	}
	if (flag && (!head)) return NULL;
	if (flag&&head) pre->next = NULL;
	if (!head) return pNode;
	return pHead;
}


//遍历单链表
void coutListNode(ListNode* head) 
{
	ListNode* p = head;
	while (p != NULL)
	{
		cout << p->val <<"    ";
		p = p->next;
	}
	cout << endl;
}
//新建链表
ListNode* newListNode(vector<int> vec) 
{
	if (vec.size() <= 0) return NULL;
	ListNode* head = new ListNode(vec[0]);
	ListNode* p = head;
    for (int i =1;i<vec.size();i++)
    {
		ListNode* n = new ListNode(vec[i]);
		p->next = n;
		p = n;
    }
	return head;
}

//给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
//注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
	if (pNode == NULL) return NULL;
	if (pNode->right!=NULL)
	{
		pNode = pNode->right;
		while (pNode->left != NULL)
		{
			pNode = pNode->left;
		}
		return pNode;
	}
	while (pNode->next!=NULL)
	{
		TreeLinkNode* p = pNode->next;
		if (p->left==pNode)
		{
			return p;
		}
		pNode = pNode->next;
	}
	return NULL;
}

//请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
//方法1
bool isSymmetrical1(TreeNode* p1, TreeNode* p2) 
{
	if (p1 == NULL&&p2 == NULL) return true;
	if (p1 == NULL || p2 == NULL) return false;
	if (p1->val != p2->val) return false;

	return isSymmetrical1(p1->left, p2->right) && isSymmetrical1(p1->right, p2->left);

}
bool isSymmetrical(TreeNode* pRoot)
{
	return isSymmetrical1(pRoot, pRoot);
}
//方法2
bool isSymmetrical2(TreeNode* pRoot) 
{
	if (pRoot == NULL) return true;
	stack<TreeNode*> st;
	st.push(pRoot->left);
	st.push(pRoot->right);
	while (!st.empty())
	{
		TreeNode* left = st.top();
		st.pop();
		TreeNode* right = st.top();
		st.pop();
		if (left == NULL&&right == NULL) continue;
		if (left == NULL || right == NULL) return false;
		if (left->val != right->val) return false;
		st.push(left->left);
		st.push(right->right);
		st.push(left->right);
		st.push(right->left);
	}
	return true;
}

//请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。
vector<vector<int> > Print(TreeNode* pRoot) {
	queue<TreeNode *> quetree;
	vector<vector<int> > res;
	bool rightBegin= false;
	if (pRoot == NULL)
	{
		return res;
	}
	quetree.push(pRoot);
	while (!quetree.empty())
	{
		int length = quetree.size();
		vector<int> vec;
		while (length > 0)
		{
			TreeNode *p = quetree.front();
			quetree.pop();
			vec.push_back(p->val);
			if (p->left) quetree.push(p->left);
			if (p->right) quetree.push(p->right);

			length--;
		}
		if (rightBegin)
		{
			reverse(vec.begin(), vec.end());
			rightBegin = false;
		}
		else
			rightBegin = true;
		res.push_back(vec);
	}
	return res;
}

//从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。
vector<vector<int> > Print_2(TreeNode* pRoot) {
	queue<TreeNode *> quetree;
	vector<vector<int> > res;
	if (pRoot == NULL)
	{
		return res;
	}
	quetree.push(pRoot);
	while (!quetree.empty())
	{
		int length = quetree.size();
		vector<int> vec;
		while (length > 0)
		{
			TreeNode *p = quetree.front();
			quetree.pop();
			vec.push_back(p->val);
			if (p->left) quetree.push(p->left);
			if (p->right) quetree.push(p->right);

			length--;
		}
		res.push_back(vec);
	}
	return res;
}

//请实现两个函数，分别用来序列化和反序列化二叉树
//什么叫序列化啊。。。。。
void Serialize_f(TreeNode* root, string &s) 
{
	if (root == NULL)
	{
		s += "#";
		return;
	}
	string r = to_string(root->val);
	s += r;
	s += ',';
	Serialize_f(root->left, s);
	Serialize_f(root->right, s);
}

char* Serialize(TreeNode *root) {
	string s = "";
	if (root == NULL) return NULL;
	Serialize_f(root, s);
	char* str = new char[s.length() + 1];
	int i;
	for (i=0;i<s.length();i++)
	{
		str[i] = s[i];
	}
	str[i] = '\0';
	return str;
}
TreeNode* Deserialize_f(char **str)
{
	if (**str =='#')
	{
		(*str)++;
		return NULL;
	}
	int num = 0;
	while (**str!='\0'&&**str!=',')
	{
		num = num * 10 + ((**str) - '0');  //防止有多位数  比如上升到 十位 百位
		++(*str);

	}
	TreeNode *root = new TreeNode(num);
	if (**str == '\0')
		return root;
	else
		(*str)++;
	root->left = Deserialize_f(str);
	root->right = Deserialize_f(str);
	return root;
}

TreeNode* Deserialize(char *str) {
	if (str == NULL) return NULL;
	TreeNode* res = Deserialize_f(&str);
	return res;
}


//给定一棵二叉搜索树，请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8）    中，按结点数值大小顺序第三小结点的值为4。

static bool compareTreeNode(TreeNode* p1, TreeNode* p2) 
{
	if (p1->val <= p2->val) return true;
	return false;
}

void binKthNode(TreeNode* pRoot, vector<TreeNode*>& vec) 
{
	if (pRoot == NULL) return;
	while (pRoot)
	{
		vec.push_back(pRoot);
		binKthNode(pRoot->left,vec);
		binKthNode(pRoot->right,vec);
	}
}

TreeNode* KthNode(TreeNode* pRoot, int k)
{
	vector<TreeNode*> vec;
	binKthNode(pRoot, vec);
	sort(vec.begin(), vec.end(), compareTreeNode);
	return vec[k - 1];
}
//以上方法会超出内存  但是是针对无序的搜索树  且消耗内存
//方法2  忘记看是二叉搜索树了  递归 每次都是k-1  中序递归

vector<TreeNode*> vecTree;
TreeNode* KthNode_2(TreeNode* pRoot, int k)
{
	if (pRoot == NULL) return NULL;
	if (pRoot->left) return KthNode_2(pRoot->left, k);
	if (vecTree.size()!=k)
	{
		vecTree.push_back(pRoot);
	}
	else 
	{
		return vecTree[k - 1];
	}
	if (pRoot->right) return KthNode_2(pRoot->right, k);
	return NULL;
}

//以上递归的方法耗内存 不能通过牛客
//方法3  非递归 用stack
TreeNode* KthNode_3(TreeNode* pRoot, int k)
{
	if (pRoot == NULL) return NULL;

	stack<TreeNode*> stTree;
	TreeNode* p = pRoot;
	int count = 0;
	while (p != NULL||!stTree.empty())
	{
		while (p) 
		{
			stTree.push(p);
			p = p->left;
		}

		if (!stTree.empty())
		{
			p = stTree.top();
			stTree.pop();
			if (count == k - 1)
			{
				return p;
			}
			p = p->right;
			
			count++;
		}
	}
	return NULL;
}

int climbStairs(int n) {
	if (n == 0) return 1;
	if (n == 1) return 1;
	return climbStairs(n - 1) + climbStairs(n - 2);
}
// 斐波那契公式
int Fibonacci_argn(int n) 
{
	double sqrt5 = sqrt(5);
	double fibn = pow((1 + sqrt5) / 2, n + 1) - pow((1 - sqrt5) / 2, n + 1);
	return (int)(fibn / sqrt5);


	//链接：https ://leetcode-cn.com/problems/two-sum/solution/pa-lou-ti-c-by-gpe3dbjds1/

}


//判断是否二叉搜索树
long cur = -2147483649;
bool isValidBST(TreeNode* root) {
	if (root == NULL) return true;
	if (root->left == NULL&&root->right == NULL)
	{
		if (root->val>cur)
		{
			cur = root->val;	
			return true;
		}
		
	}
	bool left = true, right = true, curr = true;
	if (root->left) left = isValidBST(root->left);
	if (root->val > cur)
	{
		curr = true;
		cur = root->val;
	}
	else
	{
		return false;
	}
	if (root->right) right = isValidBST(root->right);

	return curr&&left&&right;
}

bool isValidBST_v2(TreeNode* root) {
	static TreeNode* prev;
	if (root!=NULL)
	{
		if (!isValidBST(root->left)) return false;
		if (prev != NULL&&prev->val >= root->val) return false;
		prev = root;
		if (!isValidBST(root->right)) return false;
	}
	return true;
}

int main() 
{
	vector<vector<int>> vecIntS = { 
    { 1,2,3,4 },
	{ 5,6,7,8 },
	{ 9,10,11,12 },
	{ 13,14,15,16 }};
	vector<int> vec = { 3334,3,3333332 };
	vector<int> vec1 = { 1,1,2,2,2,3,3,3,4,4,5 };
	string str = "-1233aad234";
	char* string = "12e";
	//vector<int> res = multiplyv2(vec1);
	//bool r = isNumeric(string);
	//coutVec1d(res);
	//cout << '\0' << endl;
	ListNode* pNode = newListNode(vec1);
	ListNode* res = deleteDuplication(pNode);
	coutListNode(res);
	system("pause");
	return 0;
} 