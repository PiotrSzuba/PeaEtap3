#pragma once

#include <vector>
#include <time.h>
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include "GenericClass.h"

using namespace std;

class Genetic : public GenericClass
{
	private:
		vector<vector<int>> _matrix;
		vector<vector<int>> _population;
		vector<pair<int, vector<int>>> _costAndPath;
		int _size;
		int _populationSize;
		double _crossoverProbability;
		double _mutationProbability;
		int _mutationAlgorithm;
		int _currentCost = INT_MAX;
		int _noImprove = 0;
		int _iterations = 0;
		random_device _rd;
		mt19937 _gen = mt19937(this->_rd());
		void Start();
		void GeneratePopulation();
		void Selection();
		void Crossover();
		void OrderedCrossover(vector<int>, vector<int>);
		void Mutation();
		void SaveBestPopulation();
		int CalculateCost(vector<int>);
		void GetTwoRandomPoints(int&, int&);
	public:
		Genetic(vector<vector<int>>, int);
};

