#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "TspFile.h"
#include "Genetic.h"
#include "Timer.h"

using namespace std;
using namespace chrono;

template <class T>
void ResultWrapper(string FilePath)
{
	long long Time = 0;
	TspFile Data(FilePath);
	//Data.PrintMatrix();
	cout << string(typeid(T).name()).erase(0,6) <<":" << "\n\n";
	auto start = steady_clock::now();
	T Object(Data.GetMatrix(), Data.GetOPT());
	auto end = steady_clock::now();
	Time += duration_cast<milliseconds>(end - start).count();
	Object.ShowResult();
	cout << endl;
	cout << FilePath << " uzywajac " << string(typeid(T).name()).erase(0, 6) << " to " << Time << " Millisekund" << endl;
}

void displayMenu(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wybierz plik" << endl;
	cout << "2.Genetic" << endl;
	cout << "3.Pomiar Genetic" << endl;
	cout << "0.Exit" << endl;
	cout << "Wybierasz: ";
}

int AnalyzeInput(vector<string> FileNames,string input)
{
	int option = 1;
	bool digits = false;
	for (auto& x : input)
	{
		if (x >= '0' && x <= '9')
		{
			digits = true;
		}
		else
		{
			digits = false;
			break;
		}
	}

	if (digits)
	{
		option = stoi(input);
		option = FileNames.size() - option;
	}
	else
	{
		int i = 0;
		for (auto& name : FileNames)
		{
			if (name.find(input) != std::string::npos)
			{
				option = i;
			}
			i++;
		}
	}

	return option;
}

string SetFile()
{
	vector<string> FileNames;
	string path = "instances/";
	int Length = path.length();
	string input = "";
	int option = 0;
	for (const auto& entry : fs::directory_iterator(path))
	{
		auto StringPath = entry.path().string().erase(0, Length);
		FileNames.push_back(StringPath);
	}
	FileNames = TspFile::SortFiles(FileNames);
	int i = FileNames.size();
	for (auto& x : FileNames)
	{
		cout << i << ". " << x << endl;
		i--;
	}
	cout << "Wybierasz: ";
	cin >> input;
	option = AnalyzeInput(FileNames, input);

	return FileNames[option];
}

template <class T>
void Pomiar(int Repeats, int start, int end)
{
	Timer<T>timer1(Repeats, start, end);
}

int main()
{
	string FilePath = "m6.atsp";
	TspFile Data1(FilePath);
	char option = ' ';
	while (option != '0')
	{
		displayMenu(FilePath);
		cin >> option;
		cout << endl;
		switch (option)
		{
		case '1':
			FilePath = SetFile();
			break;
		case '2':
			ResultWrapper<Genetic>(FilePath);
			break;
		case '3':
			//Pomiar<Genetic>(1, 2, 24);
			break;
		}
	}
	return 0;
}