//BLIBLIOTECAS
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <math.h>
//BLIBLIOTECAS

using namespace std;

//FUNÇÕES
void funcionalidade1();
string achar_cidade1(int);
string achar_cidade2(int);
double calcular_distancia(string, string);
//FUNÇÕES

struct Dados{
    int cep1;
    int cep2;
    double distancia;
    string cidade1;
    string cidade2;
};

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

//FUNCIONALIDADE 1
void funcionalidade1(){
    Dados p;
    cout << "Informe os CEPs: " << endl;
    cout << "CEP 1: ";
    cin >> p.cep1;
    cout << "CEP 2: ";
    cin >> p.cep2;
    p.cidade1 = achar_cidade1(p.cep1);
    p.cidade2 = achar_cidade2(p.cep2);
    p.distancia = calcular_distancia(p.cidade1, p.cidade2);
    cout << p.cidade1 << " -> " << p.cidade2 << " : "  << p.distancia << " KM" << endl;
}
//FUNCIONALIDADE 1

//ENCONTRAR CIDADE E ESTADO DO CEP1
string achar_cidade1(int cep1){
    fstream arqCeps;
    string cidade1;
    arqCeps.open("cep.csv", ios::in);
    while(arqCeps.good()){
        string linha;
        getline(arqCeps, linha);
        vector<string> campo = split(linha, ';');
        if (campo.size() < 4)
            continue;
        int cepCidade1 = atoi(campo[1].c_str());
        int cepCidade2 = atoi(campo[2].c_str());
        if(cep1 >= cepCidade1 && cep1 <= cepCidade2){
            cidade1 = campo[0] + "-" + campo[3];
        }
    }
    arqCeps.close();

    return cidade1;
}
//ENCONTRAR CIDADE E ESTADO DO CEP1

//ENCONTRAR CIDADE E ESTADO DO CEP2
string achar_cidade2(int cep2){
    fstream arqCeps;
    string cidade2;
    arqCeps.open("cep.csv", ios::in);
    while(arqCeps.good()){
        string linha;
        getline(arqCeps, linha);
        vector<string> campo = split(linha, ';');
        if(campo.size() < 4)
            continue;
        int cepCidade1 = atoi(campo[1].c_str());
        int cepCidade2 = atoi(campo[2].c_str());
        if(cep2 >= cepCidade1 && cep2 <=cepCidade2){
            cidade2 = campo[0] + "-" + campo[3];
        }
    }
    arqCeps.close();
    return cidade2;
}
//ENCONTRAR CIDADE E ESTADO DO CEP2

//CALCULAR DISTÂNCIA ENTRE CIDADES
double calcular_distancia(string cidade1, string cidade2){
    size_t found;
    double lat1, long1, lat2, long2;
    float R = 6372.795477598;
    float PI = 3.1415926536;
    fstream arqMun;
    string linha;
    string searchFor(",");
    string replaceBy(".");
    arqMun.open("municipios_br.csv", ios::in);
    while(arqMun.good()){
        getline(arqMun, linha);
        vector<string> campo = split(linha, ';');
        if (campo.size() < 5)
            continue;
        //TRANSFORMAR LATITUDE EM INTEIRO
        if(cidade1 == campo[3] + "-" + campo[4]){
            found = campo[1].find( searchFor );
            while (found!=string::npos){
                campo[1].replace( found, searchFor.size(), replaceBy );
                found = campo[1].find( searchFor );
            };
            lat1 = atof(campo[1].c_str());
        //TRANSFORMAR LATITUDE EM INTEIRO

            //TRANSFORMAR LONGITUDE EM INTEIRO
            found = campo[2].find( searchFor );
            while (found!=string::npos){
                campo[2].replace( found, searchFor.size(), replaceBy );
                found = campo[2].find( searchFor );
            };
            long1 = atof(campo[2].c_str());
            //TRANSFORMAR LONGITUDE EM INTEIRO
        }
    }
    //LIMPAR ARQUIVO
    arqMun.clear();
    arqMun.seekg(0, ios::beg);
    //LIMPAR ARQUIVO
    while(arqMun.good()){
        getline(arqMun, linha);
        vector<string> campo = split(linha, ';');
        if (campo.size() < 5)
            continue;
        //TRANSFORMAR LATITUDE EM INTEIRO
        if(cidade2 == campo[3] + "-" + campo[4]){
            found = campo[1].find( searchFor );
            while (found!=string::npos){
                campo[1].replace( found, searchFor.size(), replaceBy );
                found = campo[1].find( searchFor );
            };
            lat2 = atof(campo[1].c_str());
            //TRANSFORMAR LATITUDE EM INTEIRO

            //TRANSFORMAR LONGITUDE EM INTEIRO
            found = campo[2].find( searchFor );
            while (found!=string::npos){
                campo[2].replace( found, searchFor.size(), replaceBy );
                found = campo[2].find( searchFor );
            };
            long2 = atof(campo[2].c_str());
            //TRANSFORMAR LONGITUDE EM INTEIRO
        }
    }
    //CONVERÇÃO GRAUS PARA RADIANDOS
    lat1 = lat1 * PI/180;
    long2 = long2 * PI/180;
    long1 = long1 * PI/180;
    lat2 = lat2 * PI/180;
    //CONVERÇÃO GRAUS PARA RADIANDOS

    //CURVATURA DA TERRA
    double A = sin(lat1) * sin(lat2);
    double B = cos(lat1) * cos(lat2);
    double C = cos(long1 - long2);
    //CURVATURA DA TERRA

    //DISTÂNCIA ENTRE CIDADES
    double distancia = R * acos(A + B * C);
    //DISTÂNCIA ENTRE CIDADES

    arqMun.close();
    return distancia;

}
//CALCULAR DISTÂNCIA ENTRE CIDADES
