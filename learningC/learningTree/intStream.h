#pragma once
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

class intStream_1 {
public:
	vector<int> intStream;
	void Insert(int num)
	{
		intStream.push_back(num);
		sort(intStream.begin(), intStream.end());
	}

	double GetMedian()
	{
		int size = intStream.size();
		if (size % 2 == 0)
			return (intStream[size / 2] + intStream[(size / 2) - 1]) / 2.0;
		else
			return intStream[(size / 2)]/1.0;
	}

};