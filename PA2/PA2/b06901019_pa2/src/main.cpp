#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "mps.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3) 
       return 0;
    
    //////////// read the input file /////////////
    int _2N, buffer_a, buffer_b;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin >> _2N;
    MPS mps(_2N);
    while (fin >> buffer_a >> buffer_b)
        mps.push_edge(buffer_a, buffer_b);
    
    //////////// the executing part ////////////////
    mps();

    //////////// write the output file ///////////
    fout << mps;
    fin.close();
    fout.close();

    return 0;
}
