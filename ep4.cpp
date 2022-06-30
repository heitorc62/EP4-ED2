#include <iostream>
#include "Reconhecedor.h"
#include <typeinfo>
#include <cstring>

using namespace std;

char* stringToCharArray(string s){
    int n = s.length();
    char* charArray = new char[n+1];
    strcpy(charArray, s.c_str());
    return charArray; 
}


int main(){
    char* re;
    string entrada = "(A*CG|A*TA|AAG*T)*";
    //string entrada = "(A|B|C)";
    //cin >> entrada;
    re = stringToCharArray(entrada);

    //for(int i = 0; i < a; i++) cout << re[i] << endl;
    //cout << "Insira a expressão regular: " << endl;
    //cin >> re;
    /*
    int N;
    cout << "Insira a quantidade de palavras a serem testadas: " << endl;
    cin >> N;
    */
    Reconhecedor reconhecedor(re);
    string palavra;
    char* p;
    
    
    palavra = "AAAGT";
    p = stringToCharArray(palavra);
    if(reconhecedor.reconhece(p)) cout << "S" << endl;
    else cout << "N" << endl;
    
    /*
    for(int i = 0; i < N; i++){
        cout << "Insira a " << i+1 << " palavra: " << endl;
        cin >> palavra;
        p = stringToCharArray(palavra);
        if(reconhecedor.reconhece(p)) cout << "S" << endl;
        else cout << "N" << endl;

    }
    */
}
