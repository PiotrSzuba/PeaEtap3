#include "TspFile.h"

TspFile::TspFile(string FileName)
{
	vector<vector<int>> matrix;
	Size = GetMatrixSize(FileName);
	ifstream FileReader("instances2/"+FileName);
	if (FileReader.is_open())
	{
		int i = 0;
		string line;
		while (getline(FileReader, line))
		{
			if (i == 0)
			{
				Name = line;
			}
			else if (i == 1)
			{
				CitiesAmount = line;
			}
			else if(line.length() > 10)
			{
				matrix.push_back(StringLineToVectorInt(line));
			}
			else
			{
				OPT = stoi(line);
			}
			i++;
		}
		Matrix = RepairMatrix(matrix);
		matrix.~vector();
	}
	else
	{
		cout << "Nie ma takiego pliku"<<endl;
	}

	FileReader.close();
}

vector<vector<int>> TspFile::GetMatrix()
{
	return TspFile::Matrix;
}

void TspFile::SetMatrix(vector<vector<int>> matrix)
{
	TspFile::Matrix = matrix;
}

string TspFile::GetName()
{
	return TspFile::Name;
}

string TspFile::GetCitiesAmounts()
{
	return TspFile::CitiesAmount;
}

int TspFile::GetOPT()
{
	return TspFile::OPT;
}

int TspFile::GetSize()
{
	return TspFile::Size;
}

void TspFile::PrintMatrix()
{
	for (auto& row : Matrix)
	{
		for (auto& x : row)
		{
			cout << x << " ";
		}
		cout << endl;
	}
}

int TspFile::GetMatrixSize(string FileName)
{
	string size;
	string DeletedExtension = FileName.substr(0, FileName.find(".", 0));
	vector<char> chars(DeletedExtension.begin(), DeletedExtension.end());
	for (int i = chars.size()-1; i != 0; i--)
	{
		if (chars[i] >= '0' && chars[i] <= '9')
		{
			size += chars[i];
		}
		else
		{
			break;
		}
	}
	size = string(size.rbegin(), size.rend());

	return stoi(size);
}

vector<int> TspFile::StringLineToVectorInt(string line)
{
	vector<int> IntLine;
	string temp = "";
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == ' ')
		{
			try
			{
				IntLine.push_back(stoi(temp));
			}
			catch (...) {}

			temp = "";
		}
		else
		{
			temp += line[i];
		}
	}
	try
	{
		IntLine.push_back(stoi(temp));
	}
	catch (...) {}

	return IntLine;
}

int TspFile::Number(string FileName)
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

vector<string> TspFile::SortFiles(vector<string> FileNames)
{
	vector <pair<string, int>> Pairs;
	for (auto x : FileNames)
	{
		Pairs.push_back(make_pair(x, Number(x)));
	}
	FileNames.clear();

	sort(Pairs.begin(), Pairs.end(), [](auto& left, auto& right)
		{
			return left.second > right.second;
		});

	FileNames.clear();

	for (auto& x : Pairs)
	{
		FileNames.push_back(x.first);
	}

	return FileNames;
}

vector<vector<int>> TspFile::RepairMatrix(vector<vector<int>> matrix) //zmiana 0 na -1 w macierzy z pliku
{
	for (int i = 0, j = 0; i < matrix.size(); i++, j++)
	{
		matrix[i][j] = -1;
	}
	return matrix;
}