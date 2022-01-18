#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class City
{
private:

public:
	City();
	City(vector<vector<int>>, vector<int>, int, int, int);
	vector<int> path; //droga która prowadzi do miasta
	vector<vector<int>> reducedMatrix; //zapamietanie zreedukowanej tabblicy
	int cost = 0;  //kosz dotarcia do miasta
	int vertex = 0; //numer miasta
	int level = 0; //poziom w drzewie
	int size = 0;
};

