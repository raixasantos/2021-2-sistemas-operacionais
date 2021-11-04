#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

vector<vector<int>> ler_matriz(char *arquivo){
    ifstream arquivo_leitura(arquivo);  
    string texto;
    int nx = 0, mx = 0, init = 0;
    vector<vector<int>> matriz;

    int aux_coluna = 0;
    while (getline(arquivo_leitura, texto)){
        vector<int> aux;
        stringstream ss(texto);
        if(init == 0){
            ss >> nx;
            aux.push_back(nx);
            init++;
        }
        if(init == 1){
            ss >> mx;
            aux.push_back(mx);
            matriz.push_back(aux);
            init++;
        }
        else{
            int tmp;
            for(aux_coluna = 0; aux_coluna < mx; aux_coluna++){
                ss >> tmp;
                aux.push_back(tmp);
            }
            
            matriz.push_back(aux);
        }
    }
    arquivo_leitura.close();

    return matriz;
}

vector<vector<int>> multiplicar_matrizes(vector<vector<int>> & matriz1, vector<vector<int>> matriz2){
    vector<vector<int>> matriz_resultado;
    vector<int> aux;
    for(int i = 1; i < matriz1[0][0]+1; i++){
        for(int j = 0; j < matriz2[0][1]; j++){
            int somaprod = 0;
            for(int a = 0; a < matriz1[0][1]; a++){
                cout << "matriz1: " << matriz1[i][a] << " * matriz2: " << matriz2[a][j] << endl;
                somaprod += matriz1[i][a] * matriz2[a][j];
            } 
            aux.push_back(somaprod); 
        }
        matriz_resultado.push_back(aux);
        cout << "\nfiz " << i << "!" << endl; 
    }
    

    cout << "\nverifica:\n";
    for(int i = 0; i < matriz1[0][0]; i++){
        for(int j = 0; j < matriz2[0][1]; j++){
            cout << "c" << i << j << ": " << matriz_resultado[i][j] << endl;
        }
        cout << endl;
    }

    return matriz_resultado;
}

int main(int argc, char *argv[]){
    vector<vector<int>> matriz1 = ler_matriz(argv[1]);
    vector<vector<int>> matriz2 = ler_matriz(argv[2]);    
    vector<vector<int>> matriz_resultado = multiplicar_matrizes(matriz1, matriz2);

    return 0;
}