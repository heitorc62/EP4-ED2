#ifndef TRADUTOR_H
#define TRADUTOR_H
#include <string.h>
#include <iostream>
#include <stack>

using namespace std;

class Tradutor{
    private:
    char* trataPonto(int n, int i, char* traduzido);
    char* trataMais(int i, char* traduzido);
    public:
    Tradutor();
    char* traduz(string original);
};

char* trataMais(int i, char* traduzido){
    int j = i; // "(...)+ = ...(...)*"
    stack<char> pilha;
    pilha.push('*'); j--;
    pilha.push(traduzido[j]); j--; // ')'
    int lp = 0, rp = 1;
    string epa1 = "";
    string epa2 = "";
    while(lp != rp){
        if(traduzido[j] == ')') rp++;
        else if(traduzido[j] == '(') lp++;
        pilha.push(traduzido[j]);
        j--;
    }
    int tam = pilha.size();
    while(!pilha.empty()){
        epa2 = epa2 + pilha.top();
        if(pilha.size() != tam && pilha.size() > 2) epa1 = epa1 + pilha.top();
        pilha.pop();
    }
    string epa3 = epa1 + epa2;
    int len = epa3.length();
    char* p = new char[len + 1];
    strcpy(p, epa3.c_str());
    char* novo = new char[strlen(p) + strlen(traduzido)];
    for(int q = 0; q < strlen(novo); q++){
        if(q >= j && q <= i) novo[q] = p[q - j];
        else if(q < j) novo[q] = traduzido[q];
        else novo[q] = traduzido[q - i];        
    }
    return novo;
}


char* Tradutor::trataPonto(int n, int i, char* traduzido){
    int dif;
    string expt = "|*.+[]-^()";
    dif = expt.length();
    int nChars = 95 + 94 - dif;
    char* p = new char[nChars];
    p[0] = '('; p[nChars - 1] = ')';
    for(int j = 0, k = 2; j < 95 || k < 94; j++, k = k + 2){
        if(expt.find(char(j+32)) != string::npos){k = k - 2 ; continue;}
        p[k - 1] = char(j + 32);
        p[k] = '|';
    }
    char* novo = new char[n + 1 + nChars];
    for(int j = 0; j < n + 1 + nChars; j++){
        if(j < i) novo[j] = traduzido[j];
        else if(j > i && j < i + nChars + 1) novo[j] = p[j - i - 1];
        else novo[j] = traduzido[j - nChars];
    }
    return novo;
}

char* Tradutor::traduz(string original){
    int n = original.length();
    char* traduzido = new char[n + 1];
    strcpy(traduzido, original.c_str());
    for(int i = 0; i < n + 1; i++){
        if(traduzido[i] == '.'){
            // traduzir para (a | b | c | d | e | ... ) para todos os caracteres da tabela ascii
            char* novo;
            /*
            int dif;
            string expt = "|*.+[]-^()";
            dif = expt.length();
            int nChars = 95 + 94 - dif;
            char* p = new char[nChars];
            p[0] = '('; p[nChars - 1] = ')';
            for(int j = 0, k = 2; j < 95 || k < 94; j++, k = k + 2){
                if(expt.find(char(j+32)) != string::npos){k = k - 2 ; continue;}
                p[k - 1] = char(j + 32);
                p[k] = '|';
            }
            novo = new char[n + 1 + nChars];
            for(int j = 0; j < n + 1 + nChars; j++){
                if(j < i) novo[j] = traduzido[j];
                else if(j > i && j < i + nChars + 1) novo[j] = p[j - i - 1];
                else novo[j] = traduzido[j - nChars];
            }
            */
            char* p = trataPonto(n, i, traduzido);
            
        }
        else if(traduzido[i] == '+'){
            trataMais(i, traduzido);
            /*
            int j = i; // "(...)+ = ...(...)*"
            stack<char> pilha;
            pilha.push('*'); j--;
            pilha.push(traduzido[j]); j--; // ')'
            int lp = 0, rp = 1;
            string epa1 = "";
            string epa2 = "";
            while(lp != rp){
                if(traduzido[j] == ')') rp++;
                else if(traduzido[j] == '(') lp++;
                pilha.push(traduzido[j]);
                j--;
            }
            int tam = pilha.size();
            while(!pilha.empty()){
                epa2 = epa2 + pilha.top();
                if(pilha.size() != tam && pilha.size() > 2) epa1 = epa1 + pilha.top();
                pilha.pop();
            }
            string epa3 = epa1 + epa2;
            cout << epa3;
            */
            


        }
    }
}

#endif