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

int main() 
{
	vector<vector<int>> vecIntS = { 
    { 1,2,8,9 } ,
	{ 2,4,9,12 },
	{ 4,7,10,13 },
	{ 6,8,11,15 } };
	vector<int> vec = { 0,0,1,2,3 };
	vector<int> vec1 = { 0,0,1,2,3 ,4,5,6,3,3,22,3,5,5,6,65,5,22};
	//sort(vec1.begin(), vec1.end());
	int t = Sum_Solution(8);
	cout << t << endl;
	//coutVec1d(vec1);
	system("pause");
	return 0;
}