#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class GenericClass
{
public:
	vector<int>BestPath;
	int MinCost = 0;
	int OPT = 0;
	int FirstAnswer = 0;
	int startCity = 0;
	void ShowResult();
	string PrintPrd(int);
	string PrintPrd(string);
};

