#include "Processo.h"

Processo::Processo(){
    this->tPico = 0;
    this->tInicio = 0;
    this->tRestante = 0;
}

Processo::Processo(int tPico, int tInicio)
{
    this->tPico = tPico;//Tempo que leva pra ele ser processado
    this->tInicio = tInicio;//Tempo que leva para ele coemçar a ser processado
    this->tRestante = tPico;//Round Robin
}


Processo::~Processo(){}
