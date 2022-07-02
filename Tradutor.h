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
    char* trataIntervalo(int k, int first, int last, char* traduzido);
    char* trataConjunto(int k, char* traduzido);
    char* trataComplemento();
    bool simboloREgex(char simbolo);
    int index = 0;
    public:
    Tradutor(){};
    char* traduz(string original);
};


char* Tradutor::trataMais(int i, char* traduzido){
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
    j++;
    //cout << "Palavra resultante = " << epa3 << endl;
    char* p = new char[len + 1];
    strcpy(p, epa3.c_str());
    //for(int oi = 0; oi < strlen(p); oi++) cout << p[oi] << " ";
    //cout << endl;
    //cout << "O tamanho da tradução é: " << strlen(p) << endl;
    //cout << "i = " << i << " ;; j = " << j << endl;
    char* novo = new char[strlen(p) + strlen(traduzido) - (i - j + 1)];
    //cout << "oioi" << endl;
    //cout << strlen(novo) << endl;
    for(int q = 0; q < strlen(p) + strlen(traduzido) - (i - j + 1); q++){
        if(q >= j && q < j + strlen(p)) novo[q] = p[q - j];
        else if(q < j) novo[q] = traduzido[q];
        else novo[q] = traduzido[q - strlen(p) + (i - j + 1)];    
    }
    index = strlen(p) + j;

    return novo;
}

bool Tradutor::simboloREgex(char simbolo){
    return (simbolo == '.' || simbolo == '|' || simbolo == '*' || simbolo == '+' || simbolo == '[' || simbolo == ']' || simbolo == '-' || simbolo == '^' || simbolo == '(' || simbolo == ')');
}

char* Tradutor::trataPonto(int n, int k, char* traduzido){
    string expt = "|*.+[]-^()";
    int dif;
    dif = expt.length();
    int nChars = 127 - 32;
    int aux = nChars + dif;
    int nOu = nChars - 1;
    int total = aux + nOu;
    char* p = new char[total + 2];
    p[0] = '('; 
    p[total + 1] = ')';
    int i = 0, j = 1, cont = 0;
    while(i < nChars){
        if(simboloREgex(char(i + 32))){
            p[j] = '\\';
            p[j + 1] = char(i + 32);
            if(cont < nOu){ p[j + 2] = '|'; cont++; }
            i++;
            j = j + 3;
        }
        else{
            p[j] = char(i + 32);
            if(cont < nOu){ p[j + 1] = '|'; cont++; }
            i++;
            j = j + 2;
        }
    }

    //cout << endl;
    //cout << "Tamanho da palavra ini: " << strlen(traduzido) << endl;
    //cout << "tamanho esperado = " << strlen(traduzido) + strlen(p) - 1 << endl;
    char* novo = new char[strlen(traduzido) + strlen(p) - 1];
    //cout << " k = " << k << endl;
    j = 0; aux = 0;
    while(j + aux < strlen(traduzido) + strlen(p)){
        if(j < k) novo[j] = traduzido[j];
        else if(j == k && aux < strlen(p)){novo[j + aux] = p[aux]; aux++; continue;}
        else if(j > k) novo[j + aux - 1] = traduzido[j];
        j++;
    }
    //cout << "Tamanho de novo: " << strlen(novo) << endl; 
    //for(int i = 0; i < strlen(novo) + 1; i++){
    //    cout << novo[i];
    //}
    //cout << endl;
    index = strlen(p);
    return novo;
}

char* Tradutor::trataIntervalo(int k, int first, int last, char* traduzido){
    int nChars = last + 1 - first;
    int nOu = nChars - 1;
    int total = nChars + nOu;
    char* p = new char[total + 2];
    p[0] = '('; 
    p[total + 1] = ')';
    int i = 0, j = 1, cont = 0;
    while(i < nChars){
        p[j] = char(i + first);
        if(cont < nOu){ p[j + 1] = '|'; cont++; }
        i++;
        j = j + 2;
    }

    char* novo = new char[strlen(traduzido) + strlen(p) - 5];
    //cout << " k = " << k << endl;
    j = k;
    int aux = 0;
    for(int q = 0; q < strlen(p) + strlen(traduzido) - 5; q++){
        if(q >= j && q < j + strlen(p)) novo[q] = p[q - j];
        else if(q < j) novo[q] = traduzido[q];
        else novo[q] = traduzido[q - strlen(p) + 5];    
    }

    index = strlen(p) + j;
    return novo;


}

char* Tradutor::trataConjunto(int k, char* traduzido){
    string auxString = "(";
    int i = k + 1;
    int tam = 1;
    while(traduzido[i] != ']'){
        auxString = auxString + traduzido[i];
        if(traduzido[i + 1] != ']') auxString = auxString + '|';
        i++;
        tam++;
    }
    tam++;
    auxString = auxString + ')';
    int n = auxString.length();
    char* p = new char[n+1];
    strcpy(p, auxString.c_str());
    //cout << auxString;

    char* novo = new char[strlen(traduzido) + strlen(p) - tam];
    //cout << " k = " << k << endl;
    int j = k;
    int aux = 0;
    for(int q = 0; q < strlen(p) + strlen(traduzido) - tam; q++){
        if(q >= j && q < j + strlen(p)) novo[q] = p[q - j];
        else if(q < j) novo[q] = traduzido[q];
        else novo[q] = traduzido[q - strlen(p) + tam];    
    }

    index = strlen(p) + j;
    return novo;

}


char* Tradutor::traduz(string original){
    int n = original.length();
    char* traduzido = new char[n + 1];
    strcpy(traduzido, original.c_str());
    char* backup = new char[n + 1];
    strncpy(backup, traduzido, n + 1);
    bool alterou = false;
    char* novo;
    int i = 0;
    while(i < strlen(traduzido)){
        if(traduzido[i] == '.' && (i == 0 || traduzido[i - 1] != '\\')){
            alterou = true;
            //cout << "ponto" <<endl;
            novo = trataPonto(n, i, traduzido);
            traduzido = new char[strlen(novo)];
            strncpy(traduzido, novo, strlen(novo));
            i = i + index - 1;
            cout << "traduzido[" << i << "] = " << traduzido[i] << endl;

        }
        if(traduzido[i] == '+' && (i == 0 || traduzido[i - 1] != '\\')){
            alterou = true;
            //cout << "mais" << endl;
            novo = trataMais(i, traduzido);
            //cout << "i = " << i << endl;
            //cout << "index = " << index << endl;
            traduzido = new char[strlen(novo)];
            strncpy(traduzido, novo, strlen(novo));
            i = index - 1;
            cout << "traduzido[" << i << "] = " << traduzido[i] << endl;

        }
        if(traduzido[i] == '[' && (i == 0 || traduzido[i - 1] != '\\') && traduzido[i + 1] != '^' && traduzido[i + 2] == '-'){
            alterou = true;
            int first = int(traduzido[i + 1]);
            int last = int(traduzido[i + 3]);
            novo = trataIntervalo(i, first, last, traduzido);
            traduzido = new char[strlen(novo)];
            strncpy(traduzido, novo, strlen(novo));
            i = index - 1;
            cout << "traduzido[" << i << "] = " << traduzido[i] << endl;
        }

        if(traduzido[i] == '[' && (i == 0 || traduzido[i - 1] != '\\') && traduzido[i + 1] != '^' && traduzido[i + 2] != '-'){
            alterou = true;
            novo = trataConjunto(i, traduzido);
            traduzido = new char[strlen(novo)];
            strncpy(traduzido, novo, strlen(novo));
            i = index - 1;
            cout << "traduzido[" << i << "] = " << traduzido[i] << endl;
        }
        i++;
    }

    if(alterou) return novo;
    else return backup;
}

#endif