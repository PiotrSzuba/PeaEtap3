#pragma once
#include "City.h"
#include "GenericClass.h"

class HybridBB : public GenericClass
{
private:
	City lastCity;
	int CalculateCost(vector<vector<int>>);
	void DFSBFS(City&);
	int tempUpper = INT_MAX;
	int tempLower = INT_MAX;
	int detail = 1;
	int GetDetail(int);
	vector<int> upperPerLevel;
	vector<int> avgUpperPerLevel;
	vector<int> allUpperPerLevel;
	vector<int> amountOfData;
	int rowReduction(City& city);
	int columnReduction(City& city);
	int calculateCost(City& city);
	int LowerBound = INT_MAX;
	int UpperBound = INT_MAX;
public:
	vector<int> currentPath;
	int source = 0;
	int size = 0;
	HybridBB(vector<vector<int>>, int);
};

