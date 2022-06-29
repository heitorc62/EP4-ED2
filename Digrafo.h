#ifndef DIGRAFO_H
#define DIGRAFO_H

#include <iostream>
#include "Bag.h"

class Digrafo{
    public:
    Digrafo(){};
    Digrafo(int V);  // cria um digrafo com V vértices sem arestas.
    //Digrafo(In in)   // Lê um digrafo a partir da entrada padrão
    int V; // número de vértices
    int E; // número de arestas
    void addAresta(int v, int w); // Adiciona aresta v->w ao digrafo
    Bag<int>* adj;
    //directedDfs(int s);
    void dfs();
    void dfsR(int V, bool* marked/*, int* pre, int *beg, int *end, int& t*/);
};

Digrafo::Digrafo(int V){
    this->V = V;
    this->E = 0;
    adj = new Bag<int>[V];
    for(int v = 0; v < V; v++){
        adj[v] = Bag<int>();
    }
}


void Digrafo::dfs(){
    bool* marked = new bool[V];
    int* pred = new int[V];
    int* beg = new int[V];
    int* end = new int[V];
    int tempo = 0;
    for(int i = 0; i < V; i++){
        marked[i] = false;
        beg[i] = pred[i] = end[i] = -1;
    }
    for(int v = 0; v < V; v++){
        if(!marked[v]){
            pred[v] = v;
            dfsR(v, marked/*, pred, beg, end, tempo*/);
        }
    }
}



void Digrafo::addAresta(int v, int w){
    adj[v].add(w);
    E++;
}

void Digrafo::dfsR(int v, bool* marked/*, int* pred, int *beg, int *end, int& t*/){
    marked[v] = true;
    //beg[v] = t++;
    for(int i = 0; i < adj[v].size(); i++){
        int w = adj[v].at(i);
        if(!marked[w]){
            //pred[w] = v;
            dfsR(w, marked/*, pred, beg, end, t*/);
        }
        /*
        else if(end[w] == -1) // retorno
        else if(end[w] < beg[v]) // cruzado
        else if(pred[w] != v) // descendente
        */
    }
    //end[v] = t++;
}


#endif