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
#pragma comment(lib, "Ws2_32")
using namespace std;

template<typename T>
void quicksort(vector<T>& data, int first, int last)
{
	int lower = first + 1;
	int upper = last;
	swap(data[first], data[(first + last) / 2]);
	T bound = data[first];
	while (lower < upper)
	{
		while (lower<last&&data[lower] < bound)
			lower++;
		while (upper >= (first + 1)&&data[upper] > bound)
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
int main() 
{
	vector<vector<int>> vecIntS = { 
    { 1,2,3,4 },
	{ 5,6,7,8 },
	{ 9,10,11,12 },
	{ 13,14,15,16 }};
	vector<int> vec = { 3334,3,3333332 };
	vector<int> vec1 = { 4,5,1,6,2,7,3,8 };
	string str = "erhklkasldkalkdakdwrerladkaldka";
	//vector<int> res = printMatrix(vecIntS);
	int r = FirstNotRepeatingChar(str);
	//coutVec1d(r);
	cout << r << endl;
	system("pause");
	return 0;
}