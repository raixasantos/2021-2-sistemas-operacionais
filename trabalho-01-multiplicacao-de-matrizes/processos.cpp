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

void* multiplicar_matrizes(vector<vector<int>> & m1, 
                            vector<vector<int>> & m2, clock_t inicio,
                            int indice){
    string nome_arquivo = "matriz_processos" + to_string(indice) + ".txt";
    ofstream out(nome_arquivo);
    out << m1[0][0] << " " <<  m2[0][1] << endl;    

    int somaprod = 0;
    for(int i = 1; i < m1[0][0]+1; i++){
        for(int j = 0; j < m2[0][1]; j++){
            somaprod = 0;
            for(int a = 1; a < m1[0][1]+1; a++){
                somaprod += m1[i][a-1] * m2[a][j];
            }
            clock_t fim;
            fim = clock();
            out << somaprod << ", tempo: "  << (double)(fim - inicio) / CLOCKS_PER_SEC << endl;
        }
    }    

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    vector<vector<int>> matriz1, matriz2;
    matriz1 = ler_matriz(argv[1]);
    matriz2 = ler_matriz(argv[2]); 

    stringstream ss(argv[3]);
    int P;
    ss >> P;
    int n1 = matriz1[0][0], // linhas
        m2 = matriz2[0][1]; // colunas
    int qnt_arquivos = ceil((n1*m2)/P);

    pid_t processos[qnt_arquivos]; // o vetor de threads
        
    clock_t inicio;

    for(int i = 0; i < qnt_arquivos-1; i++){         
        processos[i] = fork();      
        if(processos[i] == 0){   
            inicio = clock();    
            multiplicar_matrizes(matriz1, matriz2, inicio, i); 
            //exit(0);
        }
    }    
    
    inicio = clock();        
    multiplicar_matrizes(matriz1, matriz2, inicio, qnt_arquivos); 
    for(int i = 0; i < qnt_arquivos; i++){
        wait(NULL);
    }

    return 0;
}