#include "HybridBB.h"

//pomysl: jesli najgoresze dziecko sasiada jest lepsze niz soasiad to przez sasiada nigdy nie bedzie przechodzilo rozwiazanie
//bo minimalny koszt pojscia do kolejnego miasta to 0 a wiec najgorsze dziecko zawsze bedzie lepszym roziwazaniem niz sosiad
//czyli DFS liczy lowerbound a BFS liczy upperbound


struct comparator //dla best value search
{
	bool operator()(const City lhs, const City rhs) const {
		return lhs.cost > rhs.cost;
	}
};

struct comparatorReversed //dla UpperBound
{
	bool operator()(const City lhs, const City rhs) const {
		return lhs.cost < rhs.cost;
	}
};

HybridBB::HybridBB(vector<vector<int>> matrix, int opt)
{
	OPT = opt;
	size = matrix.size();
	detail = 1;
	for (int i = 0; i <= size+20; i++) //inicjalizacja granic na poziom
	{
		upperPerLevel.push_back(INT_MAX);
	}

	MinCost = CalculateCost(matrix);

	BestPath = currentPath;
}


int HybridBB::CalculateCost(vector<vector<int>> matrix)
{
	int start = source;
	vector<int> tempPath;
	City root(matrix, tempPath, 0, -1, 0);
	root.cost = calculateCost(root);
	LowerBound = root.cost;
	DFSBFS(root);
	lastCity.path.push_back(source); //dodanie do sciezki miasta poczatkowego
	currentPath = lastCity.path;

	return lastCity.cost;
}
void HybridBB::DFSBFS(City& city)
{
	if (city.cost >= UpperBound)
	{
		return;
	}
	if (city.level == size - 1) //jesli tutaj dojdzie to oznacza ze reszta nie spelnia warunkow
	{
		lastCity = city;
		UpperBound = city.cost;
		upperPerLevel[city.level] = UpperBound;
		//cout << UpperBound << "  " << (float(UpperBound - OPT) / float(OPT)) * 100 << "%" << endl;
		if (FirstAnswer <= 0)
		{
			FirstAnswer = UpperBound;
		}
		return;
	}
	priority_queue<City, vector<City>, comparator> pq;
	priority_queue<City, vector<City>, comparatorReversed> pqR;
	vector<int> tempPath;
	int i = city.vertex; //zapamietanie numeru miasta
	for (int j = 0; j < size; j++) //sprawdzanie dzieci
	{
		if (city.reducedMatrix[i][j] != -1)
		{
			tempPath = city.path;
			City child(city.reducedMatrix, tempPath, city.level + 1, i, j); //zwieksz poziom pozycje dziecka(i: numer rodzica , j: numer dziecka)
			tempPath = child.path;
			child.cost = city.cost + city.reducedMatrix[i][j] + calculateCost(child);
			if (child.cost <= upperPerLevel[city.level + detail]) //zwieksza lub zmniejsza dokladnosc przeszukiwania
			{

				pq.push(child);
				pqR.push(child);

			}
		}

	}
	while(!pqR.empty())
	{
		City max = pqR.top();
		pqR.pop();
		if (max.cost <= upperPerLevel[city.level])
		{
			upperPerLevel[city.level] = max.cost; 
		}
	}
	while (!pq.empty())
	{
		City min = pq.top();
		pq.pop();
		if (min.cost <= upperPerLevel[city.level+ detail])
		{
			DFSBFS(min);
		}
	}
}

int HybridBB::rowReduction(City& city)
{
	int min = INT_MAX;
	int cost = 0;

	for (int i = 0; i < size; i++)
	{
		min = INT_MAX;
		for (int j = 0; j < size; j++) //znajdywanie minimum w wierszu
		{
			if (city.reducedMatrix[i][j] < min && city.reducedMatrix[i][j] != -1)
			{
				min = city.reducedMatrix[i][j];
			}
		}
		for (int j = 0; j < size; j++) //redukcja wiersza
		{
			if (city.reducedMatrix[i][j] != -1 && min != INT_MAX)
			{
				city.reducedMatrix[i][j] -= min;
			}
		}
		if (min != INT_MAX)
		{
			cost += min;
		}
	}
	//cout << "EndRowRed" << endl;
	return cost;
}

int HybridBB::columnReduction(City& city)
{
	int min = INT_MAX;
	int cost = 0;

	for (int i = 0; i < size; i++)
	{
		min = INT_MAX;
		for (int j = 0; j < size; j++) //znajdywanie minimum w kolumnie
		{
			if (city.reducedMatrix[j][i] < min && city.reducedMatrix[j][i] != -1)
			{
				min = city.reducedMatrix[j][i];
			}
		}
		for (int j = 0; j < size; j++) //redukcja kolumny
		{
			if (city.reducedMatrix[j][i] != -1 && min != INT_MAX)
			{
				city.reducedMatrix[j][i] -= min;
			}
		}
		if (min != INT_MAX)
		{
			cost += min;
		}
	}
	//cout << "EndColRed" << endl;
	return cost;
}

int HybridBB::calculateCost(City& city)
{
	return rowReduction(city) + columnReduction(city);
}

int HybridBB::GetDetail(int level)
{
	if (level > 15)
	{
		return level - 13;
	}
	if (level == 15)
	{
		return 8;
	}
	return 2;
}
