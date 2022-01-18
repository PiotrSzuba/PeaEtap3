#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <algorithm>
#include "TspFile.h"

namespace fs = std::filesystem;
using namespace std;
using namespace chrono;


template<class T>
class Timer
{
private:
	vector<vector<int>> Matrix;
	vector<pair<string, int>> SortedFiles;
	int OPT;
	string FilePath;

	void ClearFile(string FileName)
	{
		fstream Plik;
		Plik.open(FileName, ios::trunc);
		Plik.close();
	}

	void SaveToFile(string FileName, vector<string> results)
	{
		FileName += ".txt";
		ifstream myfile(FileName, ios::in);
		string line;
		string storage[100];
		int j = 0;
		fstream Plik(FileName, ios::out);
		if (Plik.is_open())
		{
			for (auto& result : results)
			{
				Plik << result << endl;
			}
		}
		Plik.close();
		fs::path p = FileName;
		cout << fs::absolute(p) << endl;
	}

	int Number(string FileName)
	{
		string number = "";
		for (auto c : FileName)
		{
			if (c >= '0' && c <= '9')
			{
				number.push_back(c);
			}
			else if (c == '.')
			{
				return stoi(number);
			}
		}
		return stoi(number);
	}

	vector<string> ListAllFiles()
	{
		vector<string> FileNames;
		string path = "instances/";
		int Length = path.length();

		for (const auto& entry : fs::directory_iterator(path))
		{
			auto StringPath = entry.path().string().erase(0, Length);
			FileNames.push_back(StringPath);
		}

		return FileNames;
	}

	bool Comparison(const pair<string, int>& a, const pair<string, int>& b)
	{
		return a.second < b.second;
	}

	vector<pair<string, int>> SortFiles(vector<string> FileNames)
	{
		vector <pair<string, int>> Pairs;
		for (auto x : FileNames)
		{
			Pairs.push_back(make_pair(x, Number(x)));
		}
		FileNames.clear();

		sort(Pairs.begin(), Pairs.end(), [](auto& left, auto& right)
			{
				return left.second < right.second;
			});

		return Pairs;
	}

	vector<string> ReducedFileList(int start, int end)
	{
		vector<string> FileNames;
		for (auto x : SortedFiles)
		{
			if (x.second >= start && x.second <= end)
			{
				FileNames.push_back(x.first);
			}
		}

		return FileNames;
	}

public:
	Timer(int Repeats, int start, int end)
	{
		SortedFiles = SortFiles(ListAllFiles());
		FullTest(Repeats, start, end);
	}

	Timer(string FilePath, int Repeats)
	{
		FullTestSA(FilePath, Repeats);
	}

	void TestOnce(string FilePath)
	{
		TspFile Data(FilePath);
		Matrix = Data.GetMatrix();
		OPT = Data.GetOPT();
		this->FilePath = FilePath;
		cout << "Testowanie: " << FilePath << " uzywajac " << string(typeid(T).name()).erase(0, 6) << endl;
		long long Time = 0;
		auto start = steady_clock::now();
		T Object(Matrix, OPT);
		auto end = steady_clock::now();
		Time += duration_cast<milliseconds>(end - start).count();
		cout << "Sredni czas: " << FilePath << " uzywajac " << string(typeid(T).name()).erase(0, 6) << " to " << Time << " Millisekund" << endl;
	}

	void FullTest(int Repeats, int start, int end)
	{
		vector<string> FileNames = ReducedFileList(start, end);
		vector<string> Results;
		string Result;
		ClearFile(string(typeid(T).name()).erase(0, 6) + ".txt");
		for (auto FilePath : FileNames)
		{
			//cout << "Testowanie: " << FilePath << " uzywajac " << string(typeid(T).name()).erase(0, 6) << endl;
			try
			{
				TspFile Data(FilePath);
				Matrix = Data.GetMatrix();
				OPT = Data.GetOPT();
			}
			catch (const std::exception&)
			{

			}

			long long Time = 0;
			int AvgPath = 0;
			for (int i = 0; i < Repeats; ++i)
			{
				auto start = steady_clock::now();
				T Object(Matrix, OPT);
				auto end = steady_clock::now();
				Time += duration_cast<milliseconds>(end - start).count();
				AvgPath += Object.MinCost;
			}
			double time = Time;
			AvgPath /= Repeats;
			float var = (float(AvgPath - OPT) / float(OPT)) * 100;
			cout << "Sredni czas: " << FilePath << " uzywajac " << string(typeid(T).name()).erase(0, 6) << " to " << time / Repeats << " Millisekund" << " OPT: " << OPT << " Wynik: " << var << endl;
			Result = FilePath + " " + to_string(time / Repeats) +  " " + to_string(var);
			Results.push_back(Result);
		}
		SaveToFile(string(typeid(T).name()).erase(0, 6), Results);
	}

	void FullTestSA(string FilePath,int Repeats)
	{;
		vector<string> Results;
		string Result;
		ClearFile(string(typeid(T).name()).erase(0, 6) + ".txt");
		TspFile Data(FilePath);
		bool paths[] = { false, true };
		double multi[] = { 8,9 };
		double coolTs[] = {0.998,0.999};
		for (int k = 0; k < 2; k++)
		{
			for (int l = 0; l < 2; l++)
			{
				for (int j = 0; j < 2; j++)
				{
					long long Time = 0;
					int AvgPath = 0;
					Matrix = Data.GetMatrix();
					OPT = Data.GetOPT();
					int size = Matrix.size();
					int iters = (int)pow((double)size, (double)2) / multi[j];
					double currT = pow((double)size, 2) * 10;
					double coolT = coolTs[l];
					bool BB = paths[k];
					for (int i = 0; i < Repeats; ++i)
					{

						auto start = steady_clock::now();
						//SimulatedAnnealing Object(Matrix, OPT, BB, coolT, currT, iters);
						auto end = steady_clock::now();

						Time += duration_cast<milliseconds>(end - start).count();
						//AvgPath += Object.MinCost;
					}
					double time = Time / Repeats;
					AvgPath /= Repeats;
					float var = (float(AvgPath - OPT) / float(OPT)) * 100;
					cout << "Sredni czas: " << FilePath << " uzywajac " << string(typeid(T).name()).erase(0, 6) << " to " << time << " Millisekund" << " OPT: " << OPT << " Wynik: " << AvgPath << endl;
					Result = FilePath + " " + to_string(time) + " " + to_string(var) + " " + to_string(coolT) + " " + to_string(currT) + " " + to_string(BB) + " " + to_string(multi[j]);
					Results.push_back(Result);
				}
			}
		}
		SaveToFile(string(typeid(T).name()).erase(0, 6), Results);
	}
};