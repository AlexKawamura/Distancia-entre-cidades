#include <iostream>
#include "distanciaCidades.hpp"

using namespace std;

//MENU DE FUNCIONALIDADES
int main(){

    int opcao;
    cout << "===CALCULO DA DISTANCIA ENTRE CIDADES===" << endl;
    cout << "Calculo de Dois Ceps - [1]" << endl;
    cout << "Calculo de Dois ou Mais Ceps - [2]" << endl;
    cout << "Opcao: ";
    cin >> opcao;
    switch(opcao){
        case 1:
            funcionalidade1();
            break;
        case 2:
            cout << "Em desenvolvimento" << endl;
            break;
    }
}
//MENU DE FUNCIONALIDADES
