#include "Genetic.h"

Genetic::Genetic(vector<vector<int>> matrix, int opt)
{
	_size = matrix[0].size();
	_matrix = matrix;												
	this->_populationSize = _size*50;
	this->_mutationProbability = 0.03;
	this->_crossoverProbability = 0.8;
	this->_mutationAlgorithm = 1;
	this->OPT = opt;
	srand(time(NULL));
	Start();
}

void Genetic::Start()
{
	GeneratePopulation();

	while (_noImprove <= _size/2)
	{			
		Selection();
		Crossover();
		Mutation();
		SaveBestPopulation();
	}
}

void Genetic::GeneratePopulation()
{
	vector<int> individual;
	auto rng = default_random_engine(_gen);

	for (int i = 0; i < _size; i++)
	{
		individual.push_back(i);
	}

	for (int i = 0; i < _populationSize; i++)
	{
		shuffle(individual.begin(), individual.end(), rng);
		_population.push_back(individual);
		_costAndPath.push_back(make_pair(CalculateCost(_population[i]), _population[i]));
	}
}

void Genetic::Selection()
{
	sort(_costAndPath.begin(), _costAndPath.end(), [](auto& left, auto& right)
		{
			return left.first < right.first;
		});

	_costAndPath.erase(_costAndPath.begin() + _populationSize, _costAndPath.end());
	_population.erase(_population.begin() + _populationSize, _population.end());

	for (int i = 0; i < _populationSize; i++)
	{
		_population[i] = _costAndPath[i].second;
	}
}

void Genetic::Crossover()
{
	int size = _population.size();

	for (int i = 0; i < size * _crossoverProbability; i++)
	{
		int second;

		do 
		{
			second = rand() % _population.size();
		} while (i == second && i > second);

		OrderedCrossover(_population[i], _population[second]);
	}
}

void Genetic::OrderedCrossover(vector<int> parent1, vector<int> parent2)
{
	vector<int> child1(_size);
	vector<int> child2(_size);

	vector<bool> parent1Vals(parent1.size());
	vector<bool> parent2Vals(parent2.size());

	int start = -1;
	int end = -1;
	int size = parent1.size();

	GetTwoRandomPoints(start,end);

	vector<int> tempChild1(end - start);
	vector<int> tempChild2(end - start);
 
	move(parent1.begin() + start, parent1.begin() + end, tempChild1.begin());
	move(parent2.begin() + start, parent2.begin() + end, tempChild2.begin());
	
	for (int i = 0; i < end - start; i++)
	{
		parent1Vals[tempChild2[i]] = true;
		parent2Vals[tempChild1[i]] = true;
	}

	for (int i = 0, j = 0, k = 0, n = 0; i < size; i++)
	{
		if (i >= start && i < end)
		{
			child1[i] = tempChild1[j];
			child2[i] = tempChild2[j];
			j++;
		}
		else
		{		
			while (parent2Vals[parent2[k]] == true)
			{
				k++;
			}
			while (parent1Vals[parent1[n]] == true)
			{
				n++;
			}
			child1[i] = parent2[k];
			child2[i] = parent1[n];
			k++;
			n++;
		}
	}
	_population.push_back(child1);
	_population.push_back(child2);
}

void Genetic::Mutation()
{
	for (int i = 0; i < _population.size(); i++)
	{
		double pobability = (double)(rand() % 100) / 100;
		if (pobability < _mutationProbability)
		{
			int start = -1;
			int end = -1;
			GetTwoRandomPoints(start,end);

			if (_mutationAlgorithm == 0) //Swap Mutation
			{
				swap(_population[i][start], _population[i][end]);
			}
			else if (_mutationAlgorithm == 1) //Inversion Mutation
			{
				reverse(_population[i].begin() + start, _population[i].begin() + end);
			}
			else //Scramble Mutation
			{
				auto rng = default_random_engine(_gen);
				shuffle(_population[i].begin() + start, _population[i].begin() + end, rng);
			}
		}
	}
}

void Genetic::SaveBestPopulation()
{
	int minCost = INT_MAX;
	int tempCost;
	vector<int> bestPopulation;
	_iterations++;
	for (int i = _populationSize; i < _population.size(); i++)
	{
		tempCost = CalculateCost(_population[i]);
		_costAndPath.push_back(make_pair(tempCost, _population[i]));
		if (minCost > tempCost)
		{
			minCost = tempCost;
			bestPopulation = _population[i];
		}
	}
	if (_currentCost > minCost)
	{
		BestPath = bestPopulation;
		BestPath.push_back(BestPath[0]);
		_currentCost = minCost;
		MinCost = _currentCost;
		cout << _iterations << "  " << _currentCost << "  " << (float(_currentCost - OPT) / float(OPT)) * 100 << "%" << endl;
		_noImprove = 0;
		if (FirstAnswer == 0)
		{
			FirstAnswer = _costAndPath[0].first;
		}
	}
	else
	{
		_noImprove++;
	}
}

int Genetic::CalculateCost(vector<int> path) 
{
	int cost = 0;
	for (int i = 0; i < path.size() - 1; ++i)
	{
		cost += _matrix[path[i]][path[i + 1]];
	}

	cost += _matrix[path[_size - 1]][path[0]];

	return cost;
}

void Genetic::GetTwoRandomPoints(int& start, int& end)
{
	do
	{
		start = rand() % _size;
		end = rand() % _size;
	} while (start == end);

	if (end < start)
	{
		swap(start, end);
	}
}