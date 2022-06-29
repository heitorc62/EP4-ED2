#include <iostream>
#include "Reconhecedor.h"

using namespace std;

int main(){
    char* re;
    cin >> re;
    int N;
    cin >> N;
    char* palavra;
    Reconhecedor reconhecedor(re);
    for(int i = 0; i < N; i++){
        cin >> palavra;
        if(reconhecedor.reconhece(palavra)) cout << "S" << endl;
        else cout << "N" << endl;

    }
}
