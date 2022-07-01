#include <iostream>
#include <string.h>
#include <stack>

using namespace std;

int main(){
    string original = "((AB)*C)+";
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
        else if(traduzido[i] == '+'){
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
            //cout << "O tamanho da pilha é: " << tam << endl;
            while(!pilha.empty()){
                epa2 = epa2 + pilha.top();
                //cout << "epa2 = " << epa2 << endl;
                if(pilha.size() != tam && pilha.size() > 2) epa1 = epa1 + pilha.top();
                pilha.pop();
            }
            string epa3 = epa1 + epa2;
            cout << epa3;
        }
    }
}