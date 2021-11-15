#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <chrono>

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

void multiplicar_matrizes(vector<vector<int>> & m1, 
                            vector<vector<int>> & m2, chrono::steady_clock::time_point inicio,
                            int indice, int lc, int cc,
                            int lf, int cf){   

    int n_1 = m1[0][0], m_2 = m2[0][1];
    int aux_c = 0, aux_l_t = 0, aux_l = 0, cc_maior = 0;
    if(lf - lc > 0){ // verificação de linhas para pular
        cc_maior = 1;
        aux_c = cf;
        aux_l_t = lf - lc;
        cf = m_2;
    }  
 
    vector<int> resultado;
    int somaprod = 0;
    for(int linha = lc; linha <= lf; linha++){
        for(int coluna = cc; coluna < cf; coluna++){
            somaprod = 0;
            for(int a = 1; a < n_1+1; a++){
                somaprod += m1[linha][a-1] * m2[a][coluna];
            }
            resultado.push_back(somaprod);
        }
        if(cc_maior){
            cc = 0;
            if(aux_l == aux_l_t-1){
                cf = aux_c;
            }else{
                cf = m_2;
            }
            aux_l++;
        }
    }   

    chrono::steady_clock::time_point fim = chrono::steady_clock::now();

    string nome_arquivo = "arquivos-thread/3200x3200/10/matriz_threads" + to_string(indice) + ".txt";
    ofstream out(nome_arquivo);
    out << m1[0][0] << " " <<  m2[0][1] << endl;  
    for(int i = 0; i < resultado.size(); i++)
        out << resultado[i] << endl;
    out << "tempo: "  << chrono::duration_cast<chrono::milliseconds>(fim - inicio).count();
    resultado.clear();
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
    int qnt_arquivos = ceil((double) (n1*m2)/P); 

    vector<thread> threads; // o vetor de threads

    auto start = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(start);
    cout << "Iniciando em " << ctime(&start_time)
         << "Calculando..." << endl;
    int linha_c = 0, coluna_c = 0, linha_f = 0, coluna_f = 0;  
    for(int i = 0; i < qnt_arquivos; i++){    
        if(i > 0){
            linha_c = (P*i)/n1;
            coluna_c = (P*i)%n1;           
        }
        else{
            linha_c = 0;
            coluna_c = 0;
        }

        if(i == qnt_arquivos-1){
            linha_f = n1-1;
            coluna_f = m2-1;
        }
        else{
            linha_f = ((P*(i+1))-1)/n1;
            coluna_f = ((P*(i+1))-1)%n1;
        }

        chrono::steady_clock::time_point inicio = chrono::steady_clock::now();
        threads.push_back(thread(multiplicar_matrizes, ref(matriz1), ref(matriz2), inicio, i, 
                                linha_c+1, coluna_c, linha_f+1, coluna_f+1)); 

    }

    for(auto &thread : threads){ 
        thread.join();
    }
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "Finalizado em " << ctime(&end_time) << endl;
    return 0;
}