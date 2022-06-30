#ifndef TRADUTOR_H
#define TRADUTOR_H
#include <string.h>
#include <iostream>

using namespace std;

class Tradutor{
    public:
    Tradutor();
    char* traduz(string original);
};

char* Tradutor::traduz(string original){
    int n = original.length();
    char* traduzido = new char[n + 1];
    strcpy(traduzido, original.c_str());
    for(int i = 0; i < n + 1; i++){
        if(traduzido[i] == '.'){
            // traduzir para (a | b | c | d | e | ... ) para todos os caracteres da tabela ascii
            char* novo;
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
        }
    }
}

#endif