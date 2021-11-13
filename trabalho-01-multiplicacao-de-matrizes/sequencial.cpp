#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <time.h>

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

void multiplicar_matrizes(clock_t inicio, vector<vector<int>> & matriz1, vector<vector<int>> & matriz2){
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
    clock_t fim;
    fim = clock();


    ofstream out("matriz_sequencial.txt");
    out << matriz1[0][0] << " " <<  matriz2[0][1] << endl;
    for(int i = 0; i < resultado.size(); i++)
        out << resultado[i] << endl;
    out << "tempo: "  << (double)(fim - inicio) / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]){
    vector<vector<int>> matriz1 = ler_matriz(argv[1]);
    vector<vector<int>> matriz2 = ler_matriz(argv[2]); 
    clock_t inicio;
    inicio = clock();
    multiplicar_matrizes(inicio, matriz1, matriz2);

    return 0;
}