#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

int gerar_matriz(vector<vector<int>> & matriz){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0,10);

    for(;;){
        for(;;){
            int num = dist(gen);
        }
    }

}

int main(int argc, char *argv[]){
    // int dimensoes    array para armazenar as dimensões das matrizes
    int dimensoes[4]; // n1 m1 n2 m2

    // converter e armazenar os argumentos 
    for(int j = 0; j < 4; j++){
        stringstream ss(argv[j+1]);
        ss >> dimensoes[j];
        cout << dimensoes[j] << endl;
    }

    // gerar as matrizes e guardar em arquivos 
    ofstream arquivo("matriz1.txt");
    arquivo << "Writing this to a file.\n"; 
    arquivo.close();

    ofstream arquivo("matriz2.txt");
    arquivo << "Writing this to a file.\n";
    arquivo.close();


    // verificação
    string texto;
    ifstream arquivo_leitura("matriz.txt");
    while (getline (arquivo_leitura, texto)) {
        cout << texto << endl;
    }
    arquivo_leitura.close();



    return 0;
}