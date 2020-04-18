#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "maxHeap.h"

using namespace std;

void onUndirectedGraph(fstream&, const string&);
void onDirectedGraph(fstream&, const string&);

int main(int argc, char** argv) {

    if (argc != 3) {
        cerr << "Wrong input!\n";
        return 0;
    }

    fstream fin(argv[1]);
    char type;
    fin >> type;

    if(type == 'u') 
        onUndirectedGraph(fin, argv[2]);
    else if(type == 'd')
        onDirectedGraph(fin, argv[2]);
    else 
        cerr << "Wrong input!\n";

    fin.close();

    return 0;
}

void 
onUndirectedGraph(fstream& fin, const string& outFileName) {
    unsigned vNum, eNum;
    fin >> vNum >> eNum;
    Undirected G(vNum);

    for(int i = 0; i < eNum; i++) {
        unsigned u, v, w;
        fin >> u >> v >> w;
        G.push_edge(u, v, w);
    }

    G.V[0]._key = 0;

    MaxHeap Q(&G, G.V);
    while(Q.heap_size > 0) {
        int uIdx = Q.pop();
        Node& u = G.V[uIdx];
        u.inQ = false;
        for(int i = 0; i < G.V[uIdx]._adj.size(); i++) {
            Edge& e = G.V[uIdx]._adj[i];
            Node& v = G.V[e._v];
            if(v.inQ && e._w > v._key) {
                v._pi = uIdx;
                Q.IncreaseKey(e._v, e._w);
            }
        }
    }

    vector<Edge> toDrop;
    int total_weight = 0;
    for(int i = 0; i < vNum; i++) {
        Node& u = G.V[i];
        for(int j = 0; j < u._adj.size(); j++) {
        Edge& e = u._adj[j];
            Node& v = G.V[e._v];
            if(!(u._pi == v._id || u._id == v._pi) && u._id < v._id) {
                toDrop.push_back(e);
                total_weight += e._w;
            }
        }
    }

    fstream fout;
    fout.open(outFileName.c_str(), ios::out);

    fout << total_weight << endl;

    //cout << total_weight << endl;
    //cout << "start writing to file..." << endl;

    for(int i = 0; i < toDrop.size(); i++) {
        Edge e = toDrop[i];
        fout << e._u << ' ' << e._v << ' ' << e._w << '\n';
    }
    fout.flush();

    fout.close();
    return;
}

void 
onDirectedGraph(fstream& fin, const string& outFileName) {

    unsigned vNum, eNum;
    fin >> vNum >> eNum;
    Directed G(vNum);

    for(int i = 0; i < eNum; i++) {
        unsigned u, v, w;
        fin >> u >> v >> w;
        G.push_edge(u, v, w);
    }

    vector<Edge> toDrop;
    int total_weight = 0;
    int diff = 0;

    do {
        diff = toDrop.size();
        G.DFS();
        for(int i = 0; i < vNum; i++) {
            Node& u = G.V[i];
            for(int j = 0; j < u._adj.size(); j++) {
                Edge& e = u._adj[j];
                if(e._w == 101) continue;
                Node& v = G.V[e._v];
                if(u._f < v._f) {
                    Edge min_edge = e;
                    Edge edge = e;
                    //cerr << e._u << ' ' << e._v << ' ' << e._w << endl;
                    do {
                        edge = Edge(G.V[edge._u]._pi, edge._u, G.V[edge._u]._pi_w);
                        if(edge._w < min_edge._w) min_edge = edge;
                        //cerr << edge._u << ' ' << edge._v << ' ' << edge._w << endl;
                    } while(edge._u != e._v);
                    bool cont = false;
                    for(int i = 0; i < G.V[min_edge._u]._adj.size(); i++) {
                        Edge& ee = G.V[min_edge._u]._adj[i];
                        if(ee == min_edge && ee._w == 101) { cont = true; break; }
                    }
                    if(cont) continue;
                    toDrop.push_back(min_edge);
                    total_weight += min_edge._w;
                    for(int i = 0; i < G.V[min_edge._u]._adj.size(); i++) {
                        Edge& ee = G.V[min_edge._u]._adj[i];
                        if(ee == min_edge) ee._w = 101;
                    }
                    //cerr << "k";
                }
            }
        }
        diff -= toDrop.size();
        //cerr << diff << endl;
    } while (diff != 0);

    fstream fout;
    fout.open(outFileName.c_str(), ios::out);

    fout << total_weight << endl;

    //cout << total_weight << endl;
    //cout << "start writing to file..." << endl;

    for(int i = 0; i < toDrop.size(); i++) {
        Edge e = toDrop[i];
        fout << e._u << ' ' << e._v << ' ' << e._w << '\n';
    }
    fout.flush();

    fout.close();

    return;
}


