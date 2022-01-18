#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class TspFile
{
private:
	int GetMatrixSize(string);
	vector<int> StringLineToVectorInt(string);
	static int Number(string);
	vector<vector<int>> RepairMatrix(vector<vector<int>>);
public:
	int Size;
	string Name;
	string CitiesAmount;
	int OPT;
	vector<vector<int>> Matrix;
	TspFile(string);
	vector<vector<int>> GetMatrix();
	void SetMatrix(vector<vector<int>>);
	string GetName();
	string GetCitiesAmounts();
	int GetOPT();
	int GetSize();
	void PrintMatrix();
	static vector<string> SortFiles(vector<string>);
};

