#pragma once
#include <stack>
#include <iostream>
#include <cstdio>
using namespace std;

class SolutionOfNewStack {
public:
	void push(int value) {
		stackInt.push(value);
		if (stackMin.empty())
		{
			stackMin.push(value);
		}
		else 
		{
			int temp_min = stackMin.top();
			int newMin = temp_min > value ? value : temp_min;
			stackMin.push(newMin);
		}
	}
	void pop() {
		if (!stackInt.empty())
		{
			stackInt.pop();
			stackMin.pop();
		}
	}
	int top() {
		return stackInt.top();
	}
	int min() {
		return stackMin.top();
	}

private:
	stack<int> stackInt;
	stack<int> stackMin;
};