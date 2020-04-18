#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <vector>
#include "graph.h"

using namespace std;

class MaxHeap
{
public:
    MaxHeap(Undirected* g, vector<Node>& v) : G(g) {
        for (int i = 0; i < v.size(); i++)
            heap.push_back(i);
        heap_size = v.size();
    }

    int pop() {
        int max = heap[0];
        heap[0] = heap[heap_size - 1];
        G->V[heap[0]].heap_loc = 0;
        heap_size--;
        MaxHeapify(0);
        return max;
    }

    void MaxHeapify(int i) {
        int l = 2 * i + 1;
        int r = l + 1;
        int largest;
        if(l < heap_size && G->V[heap[l]]._key > G->V[heap[i]]._key)       largest = l;
        else                                                               largest = i;
        if(r < heap_size && G->V[heap[r]]._key > G->V[heap[largest]]._key) largest = r;
        if(largest != i) {
            swap(heap[i], heap[largest]);
            G->V[heap[i]].heap_loc = i;
            G->V[heap[largest]].heap_loc = largest;
            MaxHeapify(largest);
        }
    }

    void IncreaseKey(int i, int key) {
        i = G->V[i].heap_loc;
        G->V[heap[i]]._key = key;
        while(i > 0 && G->V[heap[(i-1)/2]]._key < G->V[heap[i]]._key) {
            swap(heap[(i-1)/2], heap[i]);
            G->V[heap[(i-1)/2]].heap_loc = (i-1)/2;
            G->V[heap[i]].heap_loc = i;
            i = (i-1)/2;
        }
    }


    vector<int>   heap;
    int           heap_size;
    Undirected*   G;
};

#endif
