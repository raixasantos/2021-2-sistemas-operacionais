#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

using namespace std;

vector<vector<int>> matriz1, matriz2;
int linha_atual, coluna_atual, 
    P, arquivo_atual;
clock_t inicio, fim;

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

void* multiplicar_matrizes(void *tid){
    string nome_arquivo = "matriz_threads" + to_string(arquivo_atual) + ".txt";
    ofstream out(nome_arquivo);
    out << matriz1[0][0] << " " <<  matriz2[0][1] << endl;    

    int somaprod = 0;
    for(int i = linha_atual; i < linha_atual+P; i++){ // corrigir 
        for(int j = coluna_atual; j < coluna_atual+P; j++){ // corrigir
            somaprod = 0;
            for(int a = 1; a < matriz1[0][1]+1; a++){
                somaprod += matriz1[i][a-1] * matriz2[a][j];
            }
            fim = clock();
            out << somaprod << ", tempo: "  << (double)(fim - inicio) / CLOCKS_PER_SEC << endl;
        }
    }    

    linha_atual += P;
    coluna_atual += P;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    matriz1 = ler_matriz(argv[1]);
    matriz2 = ler_matriz(argv[2]); 
    
    linha_atual = 1;
    coluna_atual = 0;
    arquivo_atual = 1;

    stringstream ss(argv[3]);
    ss >> P;
    int n1 = matriz1[0][0], // linhas
        m2 = matriz2[0][1]; // colunas
    int qnt_arquivos = ceil((n1*m2)/P);

    pthread_t thread[qnt_arquivos];
    int status = 0;

    for(int i = 0; i < qnt_arquivos;){
        inicio = clock();
        // criar threads 
        status = pthread_create(&thread[i], NULL, multiplicar_matrizes, (void*)(size_t)i);

        if(status != 0){
            cout << "Erro na criação da thread. Código de erro: %d.\n" << status;
            return 1;
        }else{ 
            i++;
            arquivo_atual++;
        }
    }

    return 0;
}