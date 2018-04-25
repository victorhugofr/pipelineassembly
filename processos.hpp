#ifndef PROCESSOS_HPP
#define PROCESSOS_HPP
#include "pipeline.hpp"
    void PrintarInstrucao(Pipeline p);
    bool conflito(Pipeline p1, Pipeline p2);
    Pipeline Instrucoes(string instrucao);
    void organiza(int& nciclos, int& ninstrucao, string *instrucoes, int cont, Pipeline *pipeline);
    void saida(int contaC, int contaI, Pipeline *pipeline);
  #endif