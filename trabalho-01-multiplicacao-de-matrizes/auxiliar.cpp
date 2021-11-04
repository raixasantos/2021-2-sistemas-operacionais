#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;

void gerar_matriz(int mt[], int gatilho, string arquivo){
    srand(time(NULL));    
    int linha = mt[0], coluna = mt[1],
        matrizPrencher[linha][coluna];
    
    ofstream out(arquivo);
    out << linha << " " << coluna << "\n";
    for(int i = 0; i < linha; i++) {
        for(int j = 0; j < coluna; j++) {
            matrizPrencher[i][j] = rand() % 10; //sorteando os números na matriz
            out << matrizPrencher[i][j] << " "; //escrevendo no aquivo txt designado
        }
        out << "\n";
    }
    out.close();
}

int main(int argc, char *argv[]){
    // int dimensoes    array para armazenar as dimensões das matrizes
    int dimensoes[4]; // n1 m1 n2 m2
    int mt1[2], mt2[2]; //mt1 = matriz 1 & mt2 = matriz 2
    // converter e armazenar os argumentos
    for(int j = 0; j < 4; j++){
        stringstream ss(argv[j+1]);
        ss >> dimensoes[j];
    }
    for(int i = 0; i < 2; i++){//preenchendo o vetor com o tamanho da linha e coluna da matriz
        mt1[i] = dimensoes[i];
        mt2[i] = dimensoes[i+2];
    }
    
    gerar_matriz(mt1, 1, "matriz1.txt"); //1º matriz chamando func
    gerar_matriz(mt2, 2, "matriz2.txt"); //2º matriz chamando func

    return 0;
}