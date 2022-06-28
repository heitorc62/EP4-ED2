#ifndef DIGRAFO_H
#define DIGRAFO_H

#include <iostream>
#include "Bag.h"

class Digrafo{
    public:
    Digrafo(int V);  // cria um digrafo com V vértices sem arestas.
    //Digrafo(In in)   // Lê um digrafo a partir da entrada padrão
    int V; // número de vértices
    int E; // número de arestas
    void addAresta(int v, int w); // Adiciona aresta v->w ao digrafo
    Bag<int>* adj;
    //directedDfs(int s);
};

Digrafo::Digrafo(int V){
    this->V = V;
    this->E = 0;
    adj = new Bag<int>[V];
    for(int v = 0; v < V; v++){
        adj[v] = Bag<int>();
    }
}

void Digrafo::addAresta(int v, int w){
    adj[v].add(w);
    E++;
}



#endif