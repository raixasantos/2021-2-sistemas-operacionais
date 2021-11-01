#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include <random>
#include <time.h> //silvia add

using namespace std;

/*int gerar_matriz(vector<vector<int>> & matriz){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0,10);

    for(;;){
        for(;;){
            int num = dist(gen);
        }
    }

}*/

void gerar_matriz(int mt[], int gatilho){
    srand(time(NULL));
    
    int linha = 0, coluna = 0, x = 0;
    linha = mt[0];
    coluna = mt[1];
    int matrizPrencher[linha][coluna];

    cout << "linha: " << linha << endl;
    cout << "coluna: " << coluna << endl;
    cout << "gatilho " << gatilho << endl;

    
    if(gatilho == 1){//sorteando e escrevendo a 1º matriz
        ofstream out("matriz1.txt");
        for(int i = 0; i < linha; i++) {//sorteando os números na matriz
            for(int j = 0; j < coluna; j++) {
                matrizPrencher[i][j] = rand() % 10;
            }
        }

        for(int i = 0; i < linha; i++) {//escrevendo no aquivo txt designado
            for(int j = 0; j < coluna; j++) {
                out << matrizPrencher[i][j] << " ";
            }
            cout << "\n";
        }

        out.close();

    } else if (gatilho == 2) {//sorteando e escrevendo 2º matriz
        ofstream out2("matriz2.txt");
        for(int i = 0; i < linha; i++) {//sorteando os números na matriz
            for(int j = 0; j < coluna; j++) {
                matrizPrencher[i][j] = rand() % 10;
            }
        }

        for(int i = 0; i < linha; i++) {//escrevendo no aquivo txt designado
            for(int j = 0; j < coluna; j++) {
                out2 << matrizPrencher[i][j] << " ";
            }
            cout << "\n";
        }

        out2.close();
    }

    

   

}

int main(int argc, char *argv[]){
    // int dimensoes    array para armazenar as dimensões das matrizes
    int dimensoes[4]; // n1 m1 n2 m2
    int mt1[2], mt2[2]; //mt1 = matriz 1 & mt2 = matriz 2
    // converter e armazenar os argumentos
    for(int j = 0; j < 4; j++){
        stringstream ss(argv[j+1]);
        ss >> dimensoes[j];
        cout << dimensoes[j] << endl;
    }
    for(int i = 0; i < 2; i++){//preenchendo o vetor com o tamanho da linha e coluna da matriz
        mt1[i] = dimensoes[i];
        mt2[i] = dimensoes[i+2];
    }

    for(int i = 0; i < 2; i++){//apenas vendo se esta guardando no local correto
        cout << "matriz 1: [ " << mt1[i] << " ]" << endl;
        cout << "matriz 2 : (  " << mt2[i] << " )" << endl;
    }
    
    gerar_matriz(mt1, 1); //1º matriz chamando func
    gerar_matriz(mt2, 2); //2º matriz chamando func


    return 0;
}