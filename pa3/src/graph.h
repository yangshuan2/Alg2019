#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

class Edge
{
public:
    Edge(int u, int v, int w) : _u(u), _v(v), _w(w) {}
    bool operator== (Edge e) {
        return (_u == e._u) && (_v == e._v);
    }
    int                 _u;
    int                 _v;
    int                 _w;
};

class Node
{
public:
    Node(int i) : _id(i), _key(-101), _pi(-1), _pi_w(-101), heap_loc(i), inQ(true), color(WHITE) {}
    ~Node() {}

    void push_edge(int v, int w) { _adj.push_back(Edge(_id, v, w)); }
    
    class EdgeComp
    {
    public:
        bool operator() (Edge a, Edge b) { return a._w > b._w; }
    } edgeComp;
    
    bool                inQ;
    Color               color;
    int                 _id;
    int                 _key;
    int                 _pi;
    int                 _pi_w;
    int                 heap_loc;
    int                 _d;
    int                 _f;
    vector<Edge>        _adj;
};

class Undirected
{
public:
    Undirected(int i) { for(int j=0; j<i; j++) V.push_back(j); }
    ~Undirected() {}

    void push_edge(int u, int v, int w) {
        V[u].push_edge(v, w);
        V[v].push_edge(u, w);
    }

    vector<Node>        V;
};

class Directed
{
public:
    Directed(int i) : time(0) { for(int j=0; j<i; j++) V.push_back(j); } 

    void push_edge(int u, int v, int w) { V[u].push_edge(v, w); }

    void DFS();
    void DFS_Visit(Node&);

    static bool nodeComp(pair<int, int> a, pair<int, int> b) { return a.second > b.second; }

    vector<Node>                    V;
    int                             time;
};

#endif // _GRAPH_H_
