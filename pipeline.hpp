#ifndef PIPELINE_HPP
#define PIPELINE_HPP
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

class Pipeline{
public:
    string opcode = "";
    string alvo = "";
    string opr1 = "";
    string opr2 = "";
    string num = "";
    int posicao = 0;
    int pular = 0;
    };
    
    void PrintarInstrucao(Pipeline p);
    bool conflito(Pipeline p1, Pipeline p2);
    Pipeline Instrucoes(string instrucao);
    void organiza(int& nciclos, int& ninstrucao, string *instrucoes, int cont, Pipeline *pipeline);
    void saida(int contaC, int contaI, Pipeline *pipeline);
#endif