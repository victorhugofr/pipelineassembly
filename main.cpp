#include <fstream>
#include "pipeline.hpp"
#include "processos.hpp"
using namespace std;

int main(int argc, char* argv[]) {
	int nciclos = 0;
    int ninstrucao = 0;
    int cont = 0;
    ifstream arquivo(argv[1]);  //abre o arquivo
    if(arquivo.fail()){
        cout << "O arquivo de entrada nao foi encontrado!" << endl;
        return 1;
    }
    string str = "";
    while(!arquivo.eof()) { // faz a contagem de linhas do arquivo
        getline(arquivo, str);
        if(str != "")
            cont++;
    }
    arquivo.clear(); // reseta objeto para limpar memoria
    arquivo.seekg(arquivo.beg); // setando para o começo do arquivo
    if(cont <= 0) {
        cout << "O arquivo foi encontrado, mas está vazio. Adicione instrucoes, lembre-se de salvar e tente novamente." << endl;
        return 1;
    }
    string *instrucoes = new string[cont]; 
    for(int i = 0; i < cont; i++){
        getline(arquivo, instrucoes[i]); //leitura do arquivo
    }   
    arquivo.clear();
    arquivo.seekg(arquivo.beg);
    Pipeline *pipeline = new Pipeline[cont];
    organiza(nciclos, ninstrucao, instrucoes, cont, pipeline); // organiza a sequencia das instrucoes
    saida(nciclos, ninstrucao, pipeline); //saida final
    delete[] instrucoes;
    delete[] pipeline;
    return 0;
}
