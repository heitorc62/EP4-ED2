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
    char* traduzido = new char[n+1];
    strcpy(traduzido, original.c_str());
    for(int i = 0; i < n+1; i++){
        if(traduzido[i] == '.'){
            // traduzir para (a | b | c | d | e | ... ) para todos os caracteres da tabela ascii
        }
    }

}

#endif