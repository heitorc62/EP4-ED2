#ifndef RECONHECEDOR_H
#define RECONHECDOR_H

#include <iostream>
#include "Digrafo.h"
#include <string.h>
#include <stack>

using namespace std;


class Reconhecedor{
    public:
    char* re;
    Digrafo G;
    Reconhecedor(char* padrao);
    bool reconhece(char* p);
    bool reconhece(Digrafo G, char* p);
    void nfa();

};

bool Reconhecedor::reconhece(char* p){
    return reconhece(G, p);
}

Reconhecedor::Reconhecedor(char* padrao){
    re = padrao;
    nfa();
}

void Reconhecedor::nfa(){
    G = Digrafo(strlen(re) + 1); // precisa do accept state
    stack<int> pilha;
    for(int i = 0; i < strlen(re); i++){
        int lp = i;
        if(re[i] == '(' || re[i] == '|'){
            pilha.push(i);
        }
        else if(re[i] == ')'){
            int ou = pilha.top(); pilha.pop();
            if(re[ou] == '|'){
                lp = pilha.top(); pilha.pop();
                G.addAresta(lp, ou + 1);
                G.addAresta(ou, i);
            }
            else lp = ou;
        }
        if(i + 1 < strlen(re) && re[i + 1] == '*'){
            G.addAresta(lp, i + 1);
            G.addAresta(i + 1, lp);
        }
        if(re[i] == '(' || re[i] == '*' || re[i] == ')')
            G.addAresta(i, i + 1);
    }
}


bool Reconhecedor::reconhece(Digrafo G, char* texto){
    bool* atingidos = new bool[G.V];
    for(int i = 0; i < G.V; i++) atingidos[i] = false;
    G.dfsR(0, atingidos);
    for(int i = 0; i < strlen(texto); i++){
        bool* prox = new bool[G.V];
        for(int l = 0; l < G.V; l++) prox[l] = false;
        for(int j = 0; j < G.V; j++){
            if(atingidos[j] && re[j] == texto[i]) prox[j+1] = true;
        }
        bool* marked = new bool[G.V];
        for(int j = 0; j < G.V; j++) atingidos[j] = false;
        for(int j = 0; j < G.V; j++){
            if(prox[j]){
                for(int k = 0; k < G.V; k++) marked[k] = true;
                G.dfsR(j, marked);
                for(int k = 0; k < G.V; k++){
                    if(marked[k]) atingidos[k] = true;
                }
            }
        }
    }
    return atingidos[G.V-1];
}







#endif