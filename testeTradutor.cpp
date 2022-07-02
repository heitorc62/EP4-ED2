#include <iostream>
#include <string.h>
#include "Tradutor.h"


using namespace std;


char* stringToCharArray(string s){
    int n = s.length();
    char* charArray = new char[n+1];
    strcpy(charArray, s.c_str());
    return charArray; 
}



int main(){
    Tradutor tradutor;
    string palavra = "(AB)+x";
    cout << "palavra inicial = " << palavra << endl;
    char* palavra2 = stringToCharArray(palavra);
    cout << "O tamanho de p antes da tradução é: " << strlen(palavra2) << endl;
    char* p = tradutor.traduz(palavra2);
    cout << "O tamanho de p agora é: " << strlen(p) << endl;
    for(int i = 0; i < strlen(p); i++) cout << p[i];
    cout << endl;

}