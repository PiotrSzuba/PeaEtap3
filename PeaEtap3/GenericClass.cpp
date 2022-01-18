#include "GenericClass.h"


void GenericClass::ShowResult()
{
    cout << endl;
    if (FirstAnswer > 0)
    {
        cout << "0 " << FirstAnswer << "  " << (float(FirstAnswer - OPT) / float(OPT)) * 100 << "%" << endl;

    }
    cout << "Sciezka: ";
    for(int i = 0; i < BestPath.size() - 1; i++)
    {
        cout << BestPath[i] << " -> ";
    }
    cout << BestPath[BestPath.size()-1];
    cout << endl;
    cout << MinCost << "  " << (float(MinCost - OPT) / float(OPT)) * 100 << "%" << endl;
}

string GenericClass::PrintPrd(int iter)
{
    return to_string(iter) + "   " + to_string(MinCost) + "  " + to_string((float(MinCost - OPT) / float(OPT)) * 100) + "%";
}

string GenericClass::PrintPrd(string iter)
{
    return iter + "   " + to_string(MinCost) + "  " + to_string((float(MinCost - OPT) / float(OPT)) * 100) + "%";
}