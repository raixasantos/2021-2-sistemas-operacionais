#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <time.h>
#include <chrono>
#include <ctime>    

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

void multiplicar_matrizes(chrono::steady_clock::time_point inicio, vector<vector<int>> & matriz1, vector<vector<int>> & matriz2){
    vector<int> resultado;
    int somaprod;
    for(int i = 1; i < matriz1[0][0]+1; i++){
        for(int j = 0; j < matriz2[0][1]; j++){
            somaprod = 0;
            for(int a = 1; a < matriz1[0][1]+1; a++){
                somaprod += matriz1[i][a-1] * matriz2[a][j];
            }
            resultado.push_back(somaprod);
        }
    }
    chrono::steady_clock::time_point fim = chrono::steady_clock::now();

    
    ofstream out("matriz_sequencial.txt");
    out << matriz1[0][0] << " " <<  matriz2[0][1] << endl;
    for(int i = 0; i < resultado.size(); i++)
        out << resultado[i] << endl;
    out << "tempo: "  << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count();
}

int main(int argc, char *argv[]){
    vector<vector<int>> matriz1 = ler_matriz(argv[1]);
    vector<vector<int>> matriz2 = ler_matriz(argv[2]); 

    auto start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << "Iniciando em " << ctime(&start_time)
         << "Calculando..." << endl;
    chrono::steady_clock::time_point inicio = chrono::steady_clock::now();
    multiplicar_matrizes(inicio, matriz1, matriz2);
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Finalizado em " << ctime(&end_time) << endl;
    return 0;
}