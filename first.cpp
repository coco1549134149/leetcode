#include <iostream>
#include <vector>
#include <stdio.h>
#include <CString>
#include <stack>
#include <map>
using namespace std;

void quick_sort(vector<int> &a, int left,int right)
{
	if (left >= right)
		return ;
	int indexmark = left;//标记的索引
	int i = right;//首先比较的是最后一个值
	bool findBig = true;
	int count = right - left;

	while (count-- > 0)
    {
		if (findBig&&a[i] < a[indexmark] || (!findBig&&a[i] > a[indexmark]))
		{
			swap(a[i], a[indexmark]);
			swap(i, indexmark);
			findBig = !findBig;
		}
		findBig ? i-- : i++;
    }
	quick_sort(a, left, indexmark - 1);
	quick_sort(a, indexmark + 1, right);
}

int heightChecker(vector<int>& heights) {
	vector<int> a = heights;
	quick_sort(a, 0, a.size() - 1);
	cout << endl;
	int num = 0;
	for (int i = 0; i < a.size(); i++) 
	{
		if (a[i]!=heights[i])
		{
			num++;
		}
	}
	return num;
}

string removeDuplicates_One(string S) {
	if (S.size()==0||S.size()==1)
	{
		return S;
	}
	bool change = true;
	int sum = 0;
	while (change)
	{
		for (int i = 0; i < S.size()-1; i++)
		{
			if (S.size() == 0 || S.size() == 1)
			{
				return S;
			}
			if (S[i] == S[i+1])
			{
				S.erase(i,1);
				S.erase(i,1);
				sum++;
			}

		}
		if (sum > 0)
		{ 
			change = true;
			sum = 0;
		}
		else
			change = false;
	}
	return S;
}
string removeDuplicates_Two(string S) {
	stack<char> c;
	for (int i=0;i<S.size();i++)
	{
		if (c.size() > 0)
		{
			char ch = c.top();
			if (S[i]==ch)
			{
				c.pop();
			}
			else
			{
				c.push(S[i]);
			}
		}
		else
		{
			c.push(S[i]);
		}
	}

	string term = "";
	while (c.size()>0)
	{
		char ch = c.top();
		term += ch;
		c.pop();
	}
	reverse(term.begin(), term.end());


	return term;
}

void insertItem(vector<int>& t, int item) 
{
	if (t.size()==0)
	{
		t.push_back(item);
		return;
	}
	if (t.size() == 1) 
	{
		if (t[0] > item) 
		{
			t.insert(t.begin(), item);
		}
		else 
		{
			t.insert(t.end(), item);
		}
	}
	for (int i = 0; i < t.size()-1; i++) 
	{
		if (item > t[i] && item <= t[i + 1]) 
		{
			t.insert(t.begin() + i + 1, item);
			return;
		}
	}
	return;
}

int lastStoneWeight(vector<int>& stones) {
	if (stones.size() == 0)
	{
		return 0;
	}
	quick_sort(stones, 0, stones.size() - 1);

	int last = 0;
	while (stones.size() > 1)
	{
		int first = stones[stones.size() - 1];
		int second = stones[stones.size() - 2];
		stones.pop_back();
		stones.pop_back();

		if (first==second)
		{
			last = 0;
		}
		else
		{
			last = first - second;
		}
		stones.push_back(last);
		quick_sort(stones, 0, stones.size() - 1);
	}
	return stones[0];
}

int largestSumAfterKNegations(vector<int>& A, int K) {
	vector<int> intVec(201);
	for (int i=0;i<A.size();i++)
	{
		intVec[A[i] + 100]++;
	}
while (K>0)
{
	int index = 0;
	for (int j=0;j<intVec.size();j++)
	{
		if (intVec[j]>0)
		{
			index = j - 100;
			intVec[j]--;
			break;
		}
	}
	intVec[-index+100]++;
	K--;
}
int sum = 0;

for (int j = 0; j < intVec.size(); j++)
{
	sum += (j - 100)*intVec[j];
}
	return sum;
}

int main() 
{

	vector<int> a = { -1,-1,-1,7,4,1,8,1 };
	int s = largestSumAfterKNegations(a,4);
	cout << s << endl;

	system("pause");
	return 0;

}