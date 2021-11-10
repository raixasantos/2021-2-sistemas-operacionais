#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <time.h>
#include <math.h>

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

void multiplicar_matrizes(clock_t inicio, vector<vector<int>> & matriz1, 
                            vector<vector<int>> & matriz2, int indice,
                            int linha_a, int coluna_a){

    ofstream out("matriz_sequencial.txt");
    clock_t fim;

    out << matriz1[0][0] << " " <<  matriz2[0][1] << endl;

    int somaprod;
    for(int i = linha_a; i < matriz1[0][0]+1; i++){
        for(int j = coluna_a; j < matriz2[0][1]; j++){
            somaprod = 0;
            for(int a = 1; a < matriz1[0][1]+1; a++){
                somaprod += matriz1[i][a-1] * matriz2[a][j];
            }
            fim = clock();
            out << somaprod << ", tempo: "  << (double)(fim - inicio) / CLOCKS_PER_SEC << endl;
            cout << somaprod << " ";
        }
        cout << "\n\n";
    }

    linha_a *= 1;

    out << (double)(fim - inicio) / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]){
    vector<vector<int>> matriz1 = ler_matriz(argv[1]);
    vector<vector<int>> matriz2 = ler_matriz(argv[2]); 
    clock_t inicio;
    int linha_a = 1, coluna_a = 0;

    stringstream ss(argv[3]);
    int P;
    ss >> P;
    int n1 = matriz1[0][0], // linhas
        m2 = matriz2[0][1]; // colunas
    int qnt_arquivos = ceil((n1*m2)/P);

    inicio = clock();

    for(int i = 0; i < qnt_arquivos; i++)
        multiplicar_matrizes(inicio, matriz1, matriz2, linha_a, i, coluna_a);

    return 0;
}