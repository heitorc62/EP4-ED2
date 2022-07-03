#ifndef TRADUTOR_H
#define TRADUTOR2_H
#include <string.h>
#include <iostream>
#include <stack>

using namespace std;

class Tradutor2{
    private:
    string trataPonto(int i, string traduzido);
    string trataMais(int i, string traduzido);
    string trataIntervalo(int k, int first, int last, string traduzido);
    string trataConjunto(int k, string traduzido);
    string trataComplemento(int k, string traduzido);
    bool simboloREgex(char simbolo);
    bool contido(char caractere, string conjunto);
    int index = 0;
    public:
    Tradutor2(){};
    string traduz(string original);
};


string Tradutor2::trataMais(int i, string traduzido){
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
    //cout << "trauzido[" << i << "] = " << traduzido[i] << endl;
    //cout << "traduzido[" << j << "] = " << traduzido[j] << endl;
    string epa3 = epa1 + epa2;
    //cout << epa3 << endl;
    string novo = "";
    j++;
    for(int q = 0; q < traduzido.length() + epa3.length() - (i - j + 1); q++){
        if(q < j) novo = novo + traduzido[q];
        if(q >= j && q < j + epa3.length()) novo = novo + epa3[q - j];
        if(q >= j + epa3.length()) novo = novo + traduzido[q - epa3.length() + (i - j + 1)];
    }
    
    index = j + epa3.length();
    return novo;

}

bool Tradutor2::simboloREgex(char simbolo){
    return (simbolo == '.' || simbolo == '|' || simbolo == '*' || simbolo == '+' || simbolo == '[' || simbolo == ']' || simbolo == '-' || simbolo == '^' || simbolo == '(' || simbolo == ')');
}

string Tradutor2::trataPonto(int k, string traduzido){
    string p = "(";
    for(int i = 32; i < 127; i++){
        if(simboloREgex(char(i))) p = p + '\\';
        p = p + char(i);
        if(i < 126) p = p + '|';
    }
    p = p + ')';
    string novo = "";
    for(int i = 0; i < traduzido.length() + p.length() - 1; i++){
        if(i < k) novo = novo + traduzido[i];
        if(i >= k && i < k + p.length()) novo = novo + p[i - k];
        if(i >= k + p.length()) novo = novo + traduzido[i - p.length() + 1];
    }
    index = k + p.length();
    return novo;
}



string Tradutor2::trataIntervalo(int k, int first, int last, string traduzido){
    string p = "(";
    for(int i = first; i <= last; i++){
        p = p + char(i);
        if(i < last) p = p + '|';
    }
    p = p + ')';
    string novo = "";
    for(int i = 0; i < traduzido.length() + p.length() - 5; i++){
        if(i < k) novo = novo + traduzido[i];
        if(i >= k && i < k + p.length()) novo = novo + p[i - k];
        if(i >= k + p.length()) novo = novo + traduzido[i - p.length() + 5];
    }

    index = k + p.length();
    return novo;

}

string Tradutor2::trataConjunto(int k, string traduzido){
    string p = "(";
    int i = k + 1;
    int cont = 1;
    while(traduzido[i] != ']'){
        p = p + traduzido[i];
        if(traduzido[i + 1] != ']') p = p + '|';
        i++;
        cont++;
    }
    cont++;
    p = p + ')';

    string novo = "";
    for(int i = 0; i < traduzido.length() + p.length() - cont; i++){
        if(i < k) novo = novo + traduzido[i];
        if(i >= k && i < k + p.length()) novo = novo + p[i - k];
        if(i >= k + p.length()) novo = novo + traduzido[i - p.length() + cont];
    }

    index = k + p.length();

    return novo;

    

}

bool Tradutor2::contido(char caractere, string conjunto){
    for(int i = 0; i < conjunto.length(); i++){
        if(caractere == conjunto[i]) return true;
    }
    return false;
}


string Tradutor2::trataComplemento(int k, string traduzido){
    string alfa = "";
    int j = k + 2;
    int cont = 3;
    while(traduzido[j] != ']') { alfa = alfa + traduzido[j]; j++; cont++;}
    j = k + 2;
    string p = "(";
    for(int i = 32; i < 127; i++){
        if(simboloREgex(char(i)) && !contido(char(i), alfa)){
            p = p + '\\';
            p = p + char(i);
            if(i < 126) p = p + '|';
        }
        else if(!contido(char(i), alfa)){
            p = p + char(i);
            if(i < 126) p = p + '|';
        } 
    }
    p = p + ')';
    string novo = "";
    
    for(int i = 0; i < traduzido.length() + p.length() - cont; i++){
        if(i < k) novo = novo + traduzido[i];
        if(i >= k && i < k + p.length()) novo = novo + p[i - k];
        if(i >= k + p.length()) novo = novo + traduzido[i - p.length() + cont];
    }


    index = k + p.length();
    return novo;
    
}



string Tradutor2::traduz(string original){
    string backup(original);
    string traduzido(original);
    bool alterou = false;
    string novo;
    int i = 0;
    while(i < traduzido.length()){
        if(traduzido[i] == '.' && (i == 0 || traduzido[i - 1] != '\\')){
            alterou = true;
            novo = trataPonto(i, traduzido);
            traduzido = novo;
            //cout << "tamanho de novo = " << novo.length() << endl;
            //cout << "novo[" << index << "] = " << novo[index] << endl;
            i = index - 1;

        }
        if(traduzido[i] == '+' && (i == 0 || traduzido[i - 1] != '\\')){
            alterou = true;
            novo = trataMais(i, traduzido);
            traduzido = novo;
            //cout << "tamanho de novo = " << novo.length() << endl;
            //cout << "novo[" << index << "] = " << novo[index] << endl;
            i = index - 1;

        }
        if(traduzido[i] == '[' && (i == 0 || traduzido[i - 1] != '\\') && traduzido[i + 1] != '^' && traduzido[i + 2] == '-'){
            alterou = true;
            int first = int(traduzido[i + 1]);
            int last = int(traduzido[i + 3]);
            novo = trataIntervalo(i, first, last, traduzido);
            traduzido = novo;            
            //cout << "tamanho de novo = " << novo.length() << endl;
            //cout << "novo[" << index << "] = " << novo[index] << endl;
            i = index - 1;
        }

        if(traduzido[i] == '[' && (i == 0 || traduzido[i - 1] != '\\') && traduzido[i + 1] != '^' && traduzido[i + 2] != '-'){
            alterou = true;
            novo = trataConjunto(i, traduzido);
            traduzido = novo;            
            //cout << "tamanho de novo = " << novo.length() << endl;
            //cout << "novo[" << index << "] = " << novo[index] << endl;            
            i = index - 1;
        }

        if(traduzido[i] == '[' && (i == 0 || traduzido[i - 1] != '\\') && traduzido[i + 1] == '^'){
            alterou = true;
            novo = trataComplemento(i, traduzido);
            traduzido = novo;            
            i = index - 1;
        }
        i++;
    }

    if(alterou) return novo;
    else return backup;
}

#endif