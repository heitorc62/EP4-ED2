#include <iostream>
#include <string.h>
using namespace std;

int main(){
    string original = "o.i";
    int n = original.length();
    char* traduzido = new char[n + 1];
    char* novo;
    int dif;
    int nChars;
    strcpy(traduzido, original.c_str());
    for(int i = 0; i < n + 1; i++){
        if(traduzido[i] == '.'){
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