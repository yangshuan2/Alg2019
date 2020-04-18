#ifndef _MPS_H_
#define _MPS_H_

#include <vector>
#include <iostream>

using namespace std;

typedef pair<int, int> edge;

class MPS
{
public:
    MPS(int a) : _2N(a) { 
        table1 = new int*[a]; 
        for(int i = 0; i < a; i++) table1[i] = new int[a];  
        edgeList = new int[_2N];
    }
    ~MPS() {
        for(int i = 0; i < _2N; i++) delete [] table1[i];
        delete [] table1;
        delete [] edgeList;
    }
    void push_edge(int a, int b) { edgeList[a] = b; edgeList[b] = a; }
    void operator() ();
    
    friend ostream& operator<< (ostream&, const MPS&);

private:
    void constructSol(int,int);

    int            _2N;
    int**          table1;
    int*           edgeList;
    vector<edge>   result;
};

#endif // _MPS_H_
