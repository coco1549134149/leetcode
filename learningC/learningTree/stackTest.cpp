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


stack<int> stack1;
stack<int> stack2;
void Stpush(int node) {
	stack1.push(node);
}

int Stpop() {
	int temp;
	if (stack2.empty())
	{
		while (!stack1.empty())
		{
			stack2.push(stack1.top());
			stack1.pop();
		}

	}

	temp = stack2.top();
	stack2.pop(); 
	return temp;
}
