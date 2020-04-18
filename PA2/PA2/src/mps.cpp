#include "mps.h"
#include <iomanip>

void
MPS::operator() ()
{
    for(int i = 0; i < _2N; i++)
        table1[i][i] = 0;
    for(int l = 1; l < _2N; l++)
    {
        for(int i = 0; i < _2N - l; i++)
        {
            int j = i + l;
            int k = edgeList[j];
            if(k > j || k < i)
                table1[i][j] = table1[i][j-1];
            else if(k > i)
            {
                int a = table1[i][k-1] + 1 + table1[k+1][j-1];
                int b = table1[i][j-1];
                table1[i][j] = a > b ? a : b;
            }
            else
                table1[i][j] = table1[i+1][j-1] + 1;
        }
    }
    constructSol(0, _2N - 1);
}

void
MPS::constructSol(int i, int j)
{
    if(i >= j) return;
    int k = edgeList[j];
    if(k > j || k < i)
        constructSol(i, j - 1);
    else if(i < k)
    {
        int a = table1[i][k-1] + 1 + table1[k+1][j-1];
        int b = table1[i][j-1];
        if(a > b)
        {
            constructSol(i, k - 1);
            result.push_back(edge(k, j));
            constructSol(k + 1, j - 1);
        }
        else
            constructSol(i, j - 1);
    }
    else
    {
        result.push_back(edge(k, j));
        constructSol(i + 1, j - 1);
    }
}

ostream&
operator<< (ostream& os, const MPS& mps)
{
    os << mps.result.size() << endl;
    for(unsigned i = 0; i < mps.result.size(); i++)
        os << mps.result[i].first << " " << mps.result[i].second << endl;
    return os;
}

