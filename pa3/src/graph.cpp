#include <fstream>
#include "graph.h"

void
Directed::DFS() {
    for(int i = 0; i < V.size(); i++) {
        V[i]._pi = -1;
        V[i].color = WHITE;
        V[i]._pi_w = -101;
    }
    time = 0;
    for(int i = 0; i < V.size(); i++) {
        Node& u = V[i];
        if(u.color == WHITE) DFS_Visit(u);
    }
}

void
Directed::DFS_Visit(Node& u) {
    time++;
    u._d = time;
    u.color = GRAY;
    //cout << u._id << ' ' << u._d << endl;
    for(int j = 0; j < u._adj.size(); j++) {
        Edge& e = u._adj[j];
        if(e._w == 101) continue;
        Node& v = V[e._v];
        if(v.color == WHITE) {
            v._pi = u._id;
            v._pi_w = e._w;
            DFS_Visit(v);
        }
    }
    u.color = BLACK;
    time++;
    u._f = time;
    //cout << u._id << ' ' << u._f << endl;
}

