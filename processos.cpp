#include "pipeline.hpp"
#include "processos.hpp"
#include <string>
void PrintarInstrucao(Pipeline pipeline) { // SEPARACAO DOS PRINTS(AS ESTRUTURAS MUDAM)
    if((pipeline.opcode == "add") || (pipeline.opcode == "sub")) {
        cout << pipeline.opcode << " " << pipeline.alvo << ", " << pipeline.opr1 << ", " << pipeline.opr2;
    }
    else if(pipeline.opcode == "j"){
        cout << pipeline.opcode << " " << pipeline.pular;
    }
    else if((pipeline.opcode == "lw") || (pipeline.opcode == "sw")){
        cout << pipeline.opcode << " " << pipeline.alvo << "," << pipeline.aux << "(" << pipeline.opr1 << ")";
    }
    else if((pipeline.opcode == "beq") || (pipeline.opcode == "bne")){
        cout << pipeline.opcode << " " << pipeline.opr1 << ", " << pipeline.opr2 << ", " << pipeline.pular;
    }
}

bool conflito(Pipeline p1, Pipeline p2) {     				// SE RETORNAR TRUE ENTAO EXISTE CONFLITO
    if((p1.alvo != "") && ((p2.opr1 == p1.alvo) || (p2.opr2 == p1.alvo))){ // VERIFICAR 3 DEPOIS
        return true; //aux
    }
    else if((p1.opcode == "lw" && p2.opcode == "sw" && p1.alvo == p2.alvo )|| (p1.opcode == "lw" && p2.opcode == "sw" && p1.alvo==p2.opr1) ){
        return true;
    }
    return false;  // SE RETORNAR FALSE, ENTAO NAO EXISTE
}

Pipeline Instrucoes(string instrucaooriginal) {
    Pipeline instrucaofinal;
    stringstream ss;
    ss << instrucaooriginal;
    string string = "";
    getline(ss, instrucaofinal.opcode, ' ');
    if((instrucaofinal.opcode == "add") || instrucaofinal.opcode == "sub") {
        getline(ss, instrucaofinal.alvo, ',');
        getline(ss, instrucaofinal.opr1, ',');
        getline(ss, instrucaofinal.opr2);
    }
    else if((instrucaofinal.opcode == "beq") || (instrucaofinal.opcode == "bne")) { //INSTRUCOES BEQ E BNE
        getline(ss, instrucaofinal.opr1, ',');
        getline(ss, instrucaofinal.opr2, ',');
        getline(ss, string);
        instrucaofinal.pular = stoi(string); // QUANTO DEVO PULAR 
    }
    else if(instrucaofinal.opcode == "j"){ // INSTRUCAO JUMP
        getline(ss, string);
        instrucaofinal.pular = stoi(string); // QUANTO DEVO PULAR
    }
    else if((instrucaofinal.opcode == "lw") || (instrucaofinal.opcode == "sw")){ // INSTRUCOES LW E SW
        getline(ss, instrucaofinal.alvo, ',');
        getline(ss, instrucaofinal.aux, '(');
        getline(ss, instrucaofinal.opr1, ')');
    }

    instrucaofinal.alvo.erase(remove(instrucaofinal.alvo.begin(), instrucaofinal.alvo.end(), ' '), instrucaofinal.alvo.end()); // remover espaços e , e ()
    instrucaofinal.opr1.erase(remove(instrucaofinal.opr1.begin(), instrucaofinal.opr1.end(), ' '), instrucaofinal.opr1.end()); // para pegar o opr1, op2 e alvo puros, nao ocorrer de 
    instrucaofinal.opr2.erase(remove(instrucaofinal.opr2.begin(), instrucaofinal.opr2.end(), ' '), instrucaofinal.opr2.end()); // pegar um () ou espaço sem querer.
    
    return instrucaofinal;
}
void organiza(int& nciclos, int& ninstrucao, string *instrucoes, int cont, Pipeline *pipeline) {// importante observar q o pos é vidivido em 5 em 5, ou seja, se quiser andar 1, soma 5
    int pos = 0;
    int i=0;
    while(i < cont) {
        pipeline[ninstrucao] = Instrucoes(instrucoes[i]);      // organiza as instrucoes
        if(ninstrucao > 0) { 
            pos = pipeline[ninstrucao - 1].posicao + 5;        // anda 1                  
            for(int j = 0; ((j < 3) && (j < i)); j++) {                             
                if((conflito(pipeline[ninstrucao - (j + 1)], pipeline[ninstrucao])) == true){ // se existir conflito entre as 3 instrucoes apos, some 5*3 na posicao (ande 3)
                    while((pos - pipeline[ninstrucao - (j + 1)].posicao) < 20){ // portanto, caso exista conflito de 3 apos, ja vai ter somado 5 e a posicao sera correta.
                        pos += 5;
                    }
                    break;
                } else{
                    pos = pipeline[ninstrucao - 1].posicao + 5; // senao, some 5(ande 1)
                }
            }
            pipeline[ninstrucao].posicao = pos;//salva
        }
        if(pipeline[ninstrucao].pular > 0) // caso haja jump ou beq e bnq
            i = pipeline[ninstrucao].pular - 1;
        else
            i++;
        nciclos = 5 + (pipeline[ninstrucao].posicao / 5); //formula, 5+numero de posicoes
        ninstrucao++;
    }
}
void saida(int nciclos, int ninstrucao, Pipeline *pipeline) {
	int ciclo=0;
	int *vetor = new int[ninstrucao];
    cout << endl << "Quantidade total de ciclos: " << nciclos << endl;
    cout << "*****************************************************" << endl;
    string estagios[5] = {"IF", "ID", "EX", "MEM", "WB"};
    for(int i = 0; i < ninstrucao; i++){
        vetor[i] = 0;
    }
    while(ciclo < nciclos) {//enquanto menor que a quantidade total de ciclos
        cout << "Ciclo " << (ciclo + 1) << endl;
        for(int i = 0; i < 5; i++) {
            cout << estagios[i] << ": ";
            for(int j = 0; j < ninstrucao; j++) {
                if((pipeline[j].posicao+vetor[j]) == ((ciclo * 5) + i)) {
                    PrintarInstrucao(pipeline[j]);
                    vetor[j] += 6; // proximo estagio
                    if(vetor[j] >= 30) vetor[j] = 0; // zera para a proxima instrucao
                    break;
                }
            }
            cout << endl;
        }
        cout << "*******************************************************" << endl;
    ciclo++; // conta o numero de ciclos
    }
    delete[] vetor;
}