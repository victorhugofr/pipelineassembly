#ifndef PIPELINE_HPP
#define PIPELINE_HPP
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

class Pipeline{
public:
    string opcode;
    string alvo;
    string opr1;
    string opr2;

    string aux; //p/ instrucao lw e sw
    int posicao = 0;
    int pular = 0;
    };
#endif