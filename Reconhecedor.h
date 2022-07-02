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
    //for(int i = 0; i < strlen(re) + 1; i++) cout << re[i] << " ";
    //cout << endl;
    //cout << "vivo" << endl;
    nfa();
    //G.show();
}

void Reconhecedor::nfa(){
    G = Digrafo(strlen(re) + 1); // precisa do accept state
    //cout << "Grafo inicial: " << endl;
    //G.show();
    stack<int> pilha;
    stack<int> pilhaOu;
    int ou;
    for(int i = 0; i < strlen(re); i++){
        int lp = i;
        if(re[i] == '(' || re[i] == '|'){
            pilha.push(i);
        }
        else if(re[i] == ')'){
            while(re[pilha.top()] == '|'){
                ou = pilha.top(); pilha.pop();
                G.addAresta(ou, i);
                pilhaOu.push(ou);
            }
            //Agora tem um lp na pilha.
            lp = pilha.top(); pilha.pop();
            while(!pilhaOu.empty()){
                ou = pilhaOu.top(); pilhaOu.pop();
                G.addAresta(lp, ou + 1);
            }
            /*
            int ou = pilha.top(); pilha.pop();
            if(re[ou] == '|'){
                lp = pilha.top(); pilha.pop();
                G.addAresta(lp, ou + 1);
                G.addAresta(ou, i);
            }
            else lp = ou;*/
        }
        if(i + 1 < strlen(re) && re[i + 1] == '*'){
            G.addAresta(lp, i + 1);
            G.addAresta(i + 1, lp);
        }
        if(re[i] == '(' || re[i] == '*' || re[i] == ')' || re[i] == '\\')
            G.addAresta(i, i + 1);
        /*
        cout << "Após a primeira iteração, o grafo é: " << endl;
        G.show();
        int opopop;
        cout << "Insira 1 para continuar. " << endl;
        cin >> opopop;
        */
    }
}


bool Reconhecedor::reconhece(Digrafo G, char* texto){
    bool* atingidos = new bool[G.V];
    for(int i = 0; i < G.V; i++) atingidos[i] = false;
    G.dfsR(0, atingidos);

    for(int i = 0; i < G.V; i++){
        if(atingidos[i]){
            if(re[i] == '(' || re[i] == ')' || re[i] == '\\') atingidos[i] = false;
        }
    }
    
    for(int i = 0; i < strlen(texto); i++){
        /*
        for(int opa = 0; opa < G.V; opa++) cout << atingidos[opa] << " ";
        cout << endl;
        */
        bool* prox = new bool[G.V];
        for(int l = 0; l < G.V; l++) prox[l] = false;
        for(int j = 0; j < G.V; j++){
            if(atingidos[j] && re[j] == texto[i]) prox[j+1] = true;
        }
        bool* marked = new bool[G.V];
        for(int j = 0; j < G.V; j++) atingidos[j] = false;
        for(int j = 0; j < G.V; j++){
            if(prox[j]){
                for(int k = 0; k < G.V; k++) marked[k] = false;
                G.dfsR(j, marked);
                for(int k = 0; k < G.V; k++){
                    if(marked[k] && re[k] != '(' && re[k] != ')' && re[k] != '\\') atingidos[k] = true;
                }
            }
        }
    }
    return atingidos[G.V-1];
}







#endif