// server.cpp

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

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void coutVec2d(vector<vector<int>> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
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

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int sum=0;
	int baseNum = 0;
	ListNode *l = new ListNode(-1);
	ListNode *head = l;
	while (l1 !=NULL|| l2 != NULL)
	{
		int a, b;
		if (l1 == NULL) a = 0;
		else a = l1->val;
		if (l2 == NULL) b = 0;
		else b = l2->val;
		

		sum = a + b + baseNum;
		if (sum >= 10) 
		{
			l->val = sum - 10;
			baseNum = 1;
		}
		else
		{
			l->val = sum;
			baseNum = 0;
		}
		ListNode *newNode = new ListNode(-1);
		l->next = newNode;
		if (l1 != NULL) l1 = l1->next;
		if (l2 != NULL) l2 = l2->next;
		l = l->next;
	}
	if (baseNum = 1)
	{
		ListNode *newNode = new ListNode(1);
		l->next = newNode;
	}

	return head;
}

int numJewelsInStones(string J, string S) {
	
	int sum = 0;
	//solution one;
	/*for (int i = 0; i < S.size(); i++)
	{
		char s = S[i];
		for (int j=0;j<J.size();j++)
		{
			char ss = J[j];
			if (s==ss)
			{
				sum++;
				break;
			}
		}
	}*/


	//solution two;
	int count[52] = { 0 };
	for (char s : S) count[int(s) - 65]++;
	for (char j : J) sum += count[int(j)-65];
	return sum;
}

int lengthOfLongestSubstring(string s) {
	int n = s.length();
	map<char, int> Map_tmp;
	map<char, int>::iterator iter;
	int i = 0, ans = 0;

	for (int j = 0; j < n; j++) {
		if ((iter = Map_tmp.find(s[j])) != Map_tmp.end()) {
			cout << iter->second << endl;
			i = max(i, iter->second);
		}
		ans = max(ans, j - i + 1);
		Map_tmp[(s[j])] = j + 1;
	}
	return ans;
}

string longestPalindromeVersionOne(string s) {
	int len = s.size();
	if (len == 0 || len == 1)
	    return s;
	int start = 0;
	int max = 1;
	vector<vector<int>> dp(len, vector<int>(len));
	for (int i = 0; i < len; i++) 
	{
		dp[i][i] = 1;
		if (i < len - 1 && s[i] == s[i + 1]) 
		{
			dp[i][i + 1] = 1;
			max = 2;
			start = i;
		}
	}
	for (int l = 3; l <= len; l++) 
	{
		for (int i = 0; i + l - 1 < len; i++) 
		{
			int j = l + i - 1;
			if (s[i] == s[j] && dp[i + 1][j - 1]==1)
			{
				dp[i][j] = 1;
				start = i;
				max = l;
			}
		}
	}
	return s.substr(start, max);
}


string removeOuterParentheses(string S) {
	stack<char> chStack;
	chStack.push(S[0]);
	int start = 0;
	vector<string> strVec;
	for (int i=1;i<S.size();i++)
	{
		if (!chStack.empty()) 
		{
			char c = chStack.top();
			if (c == '('&&S[i] == ')') 
			{
				chStack.pop();
				if (chStack.empty()) 
				{
					string temp = S.substr(start, i - start+1);
					strVec.push_back(temp);
					start = i + 1;
				}
			}
			else 
			{
				chStack.push(S[i]);
			}

		}
		else
		{
			chStack.push(S[i]);
		}
	}
	string res = "";
	for (int j=0;j<strVec.size();j++)
	{
		res += strVec[j].substr(1, strVec[j].size() - 2);
	}
	return res;
}

string removeOuterParentheses_two(string S) 
{
	string res;
	int l = 0;

	for (int i = 0; i < S.size(); i++) 
	{
		if (S[i] == '(') 
		{
			l++;
			if (l > 1) res.push_back('(');
		}
		else 
		{
			l--;
			if (l > 0) res.push_back(')');
		}
	}

	return res;
}

vector<string> reorderLogFiles(vector<string>& logs) {
	vector<string>content;
	for (auto l : logs)
	{
		int i = 0;
		while (l[i] != ' ')
			i++;
		string tmp = l.substr(i + 1);
		content.push_back(tmp);
	}

	int second = logs.size() - 1;
	int start = second - 1;

	while (start >= 0)
	{
		if (content[second][0] >= 'a' && content[second][0] <= 'z')
		{
			if (content[start][0] >= '0' && content[start][0] <= '9')
			{
				string t = content[start];
				content[start] = content[second];
				content[second] = t;
				t = logs[start];
				logs[start] = logs[second];
				logs[second] = t;
			}
			else
				start--;

		}
		else
		{
			second--;
			if (second == start)
				start--;
		}

	}

	for (int i = 0; i < content.size(); i++)

	{
		if (content[i][0] >= '0' && content[i][0] <= '9')
		{
			start = i;
			break;
		}
	}
	for (int i = 0; i < start; i++)
		for (int j = i + 1; j < start; j++)
		{
			if (content[i] > content[j])
			{
				string t = content[i];
				content[i] = content[j];
				content[j] = t;
				t = logs[i];
				logs[i] = logs[j];
				logs[j] = t;
			}
			else if (content[i] == content[j])
			{
				if (logs[i] > logs[j])
				{
					string t = content[i];
					content[i] = content[j];
					content[j] = t;
					t = logs[i];
					logs[i] = logs[j];
					logs[j] = t;
				}
			}
		}
	return logs;
}

#define CHANGEINT(x) x==0? 1:0

vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
	for (int i=0;i<A.size();i++)
	{
		reverse(A[i].begin(), A[i].end());
		for (int j = 0; j < A[i].size(); j++)
		{
			A[i][j] = CHANGEINT(A[i][j]);
		}
	}
	return A;
}

int uniqueMorseRepresentations(vector<string>& words) {
	set<string>  m;
	//map<string, int>::iterator iter;
	vector<string>  mosi =
	{ ".-","-...","-.-.","-..",".","..-.","--.","....","..",
		".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",
		"...","-","..-","...-",".--","-..-","-.--","--.." };

		for(auto l : words)
		{
			string temp = "";
			for (auto i : l)
			{
				temp += mosi[i - 'a'];
			}
			
		 m.insert(temp);
			
		}
		return m.size();
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	int i = m - 1;
	int j = n - 1;
	int index = nums1.size() - 1;
    while (i>=0&&j>=0)
	{
		if (nums2[j]>=nums1[i])
		{
			nums1[index] = nums2[j];
			index--;
			j--;
		}
		else 
		{
			nums1[index] = nums1[i];
			index--;
			i--;
		}
	}
	while (i>=0)
	{
		nums1[index] = nums1[i];
		index--;
		i--;
	}
	while (j >= 0)
	{
		nums1[index] = nums2[j];
		index--;
		j--;
	}
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};
 
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
	if (t1 == NULL&&t2 == NULL)
		return t1;
	if (t1==NULL)
	    return t2;
	if (t2 == NULL)
		return t1;
	t1->val = t1->val + t2->val;
	t1->left = mergeTrees(t1->left, t2->left);
	t1->right = mergeTrees(t1->right, t2->right);
	return t1;	
}

bool judgeCircle(string moves) {
	int i = 0;
	int j = 0;
	for (auto ch : moves)
	{
		switch (ch)
		{
		case 'R':
			i++;
			break;
		case 'L':
			i--;
			break;
		case 'U':
			j++;
			break;
		case 'D':
			j--;
			break;
		default:
			break;
		}
	}
	if (i == 0 && j == 0)
		return true;
	else
		return false;
}

vector<int> selfDividingNumbers(int left, int right) {
	vector<int> answer;
	bool suc = true;
	while (left<=9&&left<=right)
	{
		answer.push_back(left);
		left++;
	}
	while (left <= right)
	{
		if (left % 10 == 0)
			suc = false;
		else 
		{
			int test = left;
			while (test != 0)
			{
				int x = test % 10;
				if (x == 0) 
				{
					suc = false;
					break;
				}
				else if (left%x==0)
				{
					test = test / 10;
					suc = true;
				}
				else 
				{
					suc = false;
					break;
				}
			}

		}
		if (suc)
		{
			answer.push_back(left);
		}
		left++;
	}
	return answer;
}


bool checkPerfectNumber(int num) {
	int sum=0;
	for (int i = sqrt(num); i >= 1; i--) 
	{
		if (num%i == 0) 
		{
			sum += i;
			int j = num / i;
			if (j != i&&j!=num) 
			{
				sum += j;
			}
			if (sum > num)
				return false;
		}
	}
	if (num == sum)
		return true;
	else
		return false;
}

#define RIGHT_CON 1
#define DOWN_CON 2
#define LEFT_CON 3
#define UP_CON 4
bool isRobotBounded(string instructions) {
	int i = 0;
	int j = 0;
	int dir = UP_CON;
	for (int l = 0; l < 5; l++) 
	{
		for (auto ch : instructions)
		{
			switch (ch)
			{
			case 'G':
				switch (dir)
				{
				case RIGHT_CON:
					i++;
					break;
				case DOWN_CON:
					j--;
					break;
				case LEFT_CON:
					i--;
					break;
				case UP_CON:
					j++;
					break;
				}
				break;
			case 'L':
				switch (dir)
				{
				case RIGHT_CON:
					dir = UP_CON;
					break;
				case DOWN_CON:
					dir = RIGHT_CON;
					break;
				case LEFT_CON:
					dir = DOWN_CON;
					break;
				case UP_CON:
					dir = LEFT_CON;
					break;
				}
				break;
			case 'R':
				switch (dir)
				{
				case RIGHT_CON:
					dir = DOWN_CON;
					break;
				case DOWN_CON:
					dir = LEFT_CON;
					break;
				case LEFT_CON:
					dir = UP_CON;
					break;
				case UP_CON:
					dir = RIGHT_CON;
					break;
				}
				break;
			}
		}
		if (i == 0 && j == 0)
			return true;
	}
		return false;
}


//计算器第一个版本  只能加减  而且不能处理减负数的情况
int calculate_one(string s) {
	stack<char> chs;
	s.append(")");
	chs.push('(');
	int term = 0;
	for (char c : s)
	{
		if (chs.empty())
		{
			chs.push(c);
		}
		else 
		{
			if (c == ')')
			{
				stack<char> vec;
				while (chs.top()!='(')
				{
					vec.push(chs.top());
					chs.pop();
				}
				chs.pop();
				char last;
				last = vec.top();
				vec.pop();
				int cal = 0;
				int add1, add2 = 0;
				add1 = last - '0';
				while(!vec.empty())
				{
					char cc = vec.top();
					if (cc>='0'&&cc<='9')
					{
						if (last >= '0'&&last <= '9') 
						{
							if (cal == 0) 
							{
								add1 = add1 * 10 + (cc - '0');
								vec.pop();
							}
							else 
							{
								add2 = add2 * 10 + (cc - '0');
								vec.pop();
							}
						}
						else 
						{
							add2 = cc - '0';
							vec.pop();
						}
					}
					else if(cc=='+')
					{
						if (cal == 1) 
						{
							add1 = add1 + add2;
						}
						else if (cal == -1)
						{
							add1 = add1 - add2;
						}
						vec.pop();
						cal = 1;
					}
					else if(cc=='-')
					{
						if (cal == 1)
						{
							add1 = add1 + add2;
						}
						else if (cal == -1)
						{
							add1 = add1 - add2;
						}
						vec.pop();
						cal = -1;
					}
					last = cc;
				}
				if (cal == 1)
				{
					add1 = add1 + add2;
				}
				else if (cal == -1)
				{
					add1 = add1 - add2;
				}
				stack<char> tt;
				while (add1 != 0) 
				{
					int a = add1 % 10;
					add1 /= 10;
					tt.push(a + '0');
				}
				while (!tt.empty())
				{
					char ss = tt.top();
					chs.push(ss);
					tt.pop();
				}



			}
			else 
			{
				chs.push(c);
			}
		}

		//stack<char> chs_c = chs;
		//while (!chs_c.empty())
		//{
		//	char i = chs_c.top();
		//	cout << i << " ";
		//	chs_c.pop();
		//}
		//cout << endl;
	}
	stack<char> vec;
	while (!chs.empty())
	{
		vec.push(chs.top());
		chs.pop();
	}

	term = (vec.top() - '0');
	vec.pop();
	while (!vec.empty())
	{
		char i = vec.top();
		term = (term * 10) + (i-'0');
		vec.pop();
	}
	return term;

}
//计算器第二个版本  减少运行时间  但还是不能处理负数
int calculate_two(string s) 
{
	stack<char> stackChar;
	int index_operator = -1;
	stack<int> stackInt;
	int index_num = -1;

	char temp_char;
	int temp_int;

	bool trigger;
	for (int i = 0; i < s.size(); i++) 
	{
		temp_char = s[i];
		trigger = false;

		if (temp_char == ' ') 
		{
		}
		else 
			if (temp_char >= '0'&&temp_char <= '9') 
			{
				temp_int = temp_char - '0';
				while (i+1<s.size()&&(s[i + 1] >= '0'&&s[i + 1] <= '9'))
				{
					temp_int = temp_int * 10+ (s[i + 1] - '0');
					i++;
				}
				stackInt.push(temp_int);
				trigger = true;
			}
			else 
			{
				if (temp_char != ')') 
				{
					stackChar.push(temp_char);
				}
				else
				{
					stackChar.pop();
					trigger = true;
				}
			}
		if (trigger && ((!stackChar.empty()) && (stackChar.top() == '+' || stackChar.top() == '-'))) 
		{
			int secondInt = stackInt.top();
			stackInt.pop();
			int firstInt = stackInt.top();
			stackInt.pop();
			if (stackChar.top() == '+') 
			{
				stackChar.pop();
				int res = firstInt + secondInt;
				stackInt.push(res);
			}
			else if (stackChar.top() == '-') 
			{
				stackChar.pop();
				int res = firstInt - secondInt;
				stackInt.push(res);
			}
		}
	}
	return stackInt.top();

}
//第三个版本  未完成
int calculate_three(string s)
{
	stack<char> stackChar;
	stack<int> stackInt;

	char temp_char;
	int temp_int;

	bool trigger;
	for (int i = 0; i < s.size(); i++)
	{
		temp_char = s[i];
		trigger = false;

		if (temp_char == ' ')
		{
		}
		else
			if (temp_char >= '0'&&temp_char <= '9')
			{
				temp_int = temp_char - '0';
				while (i + 1 < s.size() && (s[i + 1] >= '0'&&s[i + 1] <= '9'))
				{
					temp_int = temp_int * 10 + (s[i + 1] - '0');
					i++;
				}
				if (stackChar.top() == '+' || stackChar.top() == '(')
				{
					stackInt.push(temp_int);
				}
				else if (stackChar.top() == '-')
				{
					stackInt.push(-temp_int);
				}

				trigger = true;
			}
			else
			{
				if (temp_char != ')')
				{
					stackChar.push(temp_char);
				}
				else
				{
					stackChar.pop();
					trigger = true;
				}
			}
		if (trigger && ((!stackChar.empty()) && (stackChar.top() == '+' || stackChar.top() == '-')))
		{
			int secondInt = stackInt.top();
			stackInt.pop();
			int firstInt = stackInt.top();
			stackInt.pop();
			stackChar.pop();
			int res = firstInt + secondInt;
			stackInt.push(res);

		}

		
	}
	return stackInt.top();
}


TreeNode* invertTree(TreeNode* root) {
	if (root == NULL)
	{
		return NULL;
	}
	if (!(root->left == NULL&&root->right == NULL)) 
	{
		TreeNode *temp = root->right;
		root->right = root->left;
		root->left = temp;
		if (root->left!=NULL)
		{
			root->left = invertTree(root->left);
		}
		if (root->right != NULL)
		{
			root->right = invertTree(root->right);
		}
	}
	return root;
}
//判断平衡二叉树 递归解法

int maxDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

int minDepth(TreeNode* root) {
	if (root == NULL)
	{
		return 0;
	}
	int left = minDepth(root->left);
	int right = minDepth(root->right);
	return (left == 0 || right == 0) ? left + right + 1 : min(left, right) + 1;
}

bool isBalance(TreeNode *l, TreeNode *r)
{
	int value = abs(maxDepth(l) - maxDepth(r));
	if (value > 1)
	{
		return false;
	}
	return true;
}

bool isBalanced(TreeNode* root) {
	if (root == NULL)
	{
		return true;
	}
	if (isBalance(root->left, root->right)) 
	{
		if (root->left!=NULL)
		{
			if (isBalanced(root->left))
		    {
				return isBalanced(root->right);
			}
			return false;
		}
		else 
		{
			return isBalanced(root->right);
		}
	}
	return false;
}

vector<vector<int>> levelOrder(TreeNode* root) {
	queue<TreeNode *> quetree;
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
		while (length>0)
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
	reverse(res.begin(), res.end());
	return res;
}

vector<int> diStringMatch(string S) {
	int Max = S.size();
	int Min = 0;
	vector<int> res;
	for (char c : S) 
	{
		if (c == 'I') res.push_back(Min++);
		else res.push_back(Max--);
	}
	res.push_back((Max + Min) / 2);
	return res;
}

int GreatestCommonDivisor(int a, int b)

{
	if (a >= b) return a%b ? GreatestCommonDivisor(b, a%b) : b;
	else return b%a ? GreatestCommonDivisor(a, b%a) : a;
}
bool hasGroupsSizeX(vector<int>& deck) {
	if (deck.size()<2)
	{
		return false;
	}
	map<int, int> mapInt;
	map<int, int>::iterator iter;

	for (int i : deck)
	{
		if ((iter = mapInt.find(i)) != mapInt.end()) 
		{
			mapInt[i]++;
		}
		else 
		{
			mapInt[i] = 1;
		}
	}

	iter = mapInt.begin();
	int K = iter->second;
	while (iter != mapInt.end())
	{
		K = GreatestCommonDivisor(K, iter->second);
		if (K==1)
		{
			return false;
		}
		iter++;
	}

	return true;
}

int majorityElement(vector<int>& nums) {
	map<int, int> mapInt;
	map<int, int>::iterator iter;

	for (int i : nums)
	{
		if ((iter = mapInt.find(i)) != mapInt.end())
		{
			mapInt[i]++;
		}
		else
		{
			mapInt[i] = 1;
		}
	}

	iter = mapInt.begin();
	
	while (iter != mapInt.end())
	{
		int K = iter->second;
		if (K > (nums.size()/2))
		{
			return iter->first;
		}
		iter++;
	}
	return 0;

}

//vector<int> vecMajorityElement(vector<int>& nums) {
//	
//}

int peakIndexInMountainArray(vector<int>& A) {
	int l = 0;
	int r = A.size() - 1;
	while (l<r)
	{
		int mid = (l + r) / 2;
		if (A[mid]>A[mid-1]&&A[mid]>A[mid+1])
		{
			return mid;
		}
		else if (A[mid]>A[mid - 1] && A[mid]<A[mid + 1])
		{
			l = mid+1;
		}
		else if (A[mid]<A[mid - 1] && A[mid]>A[mid + 1])
		{
			r = mid;
		}
	}
	return 0;
}

vector<int> sortArrayByParity(vector<int>& A) {
	int i, j;
	int _size = A.size();
	for (i = 0, j = _size - 1; i < j;)
	{
		while (i<_size&&A[i] % 2 == 0 ) i++;
		while (j>=0&&A[j] % 2 == 1) j--;
		if (i<j)
		{
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
			i++;
			j--;
		}
		
	}
	return A;
}

void reverseString(vector<char>& s) {
	reverse(s.begin(), s.end());
}

static bool check(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
		c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
		return true;
	}
	return false;
}

string reverseVowels(string s) {
	int i, j;
	for (i=0,j=s.size()-1;i<j;)
	{
	}
}

int main()
{
	vector<int> B = { 0,2 };
	vector<int> A = sortArrayByParity(B);
	coutVec1d(A);
	coutVec1d(B);
	//cout << a << endl;
	system("pause");
	return 0;
}


