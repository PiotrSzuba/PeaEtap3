#include "City.h"
City::City() {}
City::City(vector<vector<int>> parentMatrix, vector<int> path, int level, int i, int j)
{
    this->size = parentMatrix.size(); //inaczej obiekt niewie jaka jest ilosc miast
    this->level = level; //ustaw ilosc odwiedzonych miast
    this->vertex = j; //zapamietaj pozycje dziecka
    this->path = path;
    this->path.push_back(this->vertex); //dodaj swoja pozycje do sciezki
    this->reducedMatrix = parentMatrix;
    for (int k = 0; level != 0 && k < size; k++)
    {
        this->reducedMatrix[i][k] = -1;
        this->reducedMatrix[k][j] = -1;
    }
    this->reducedMatrix[j][0] = -1;

}
