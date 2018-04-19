#include "Processo.h"

Processo::Processo(int tPico, int tInicio)
{
    this->tPico = tPico;//Tempo Processado
    this->tInicio = tInicio;//Tempo que leva para ele comçar a ser processado
    this->tRestante = this->tPico;//Round Robin
}


Processo::~Processo(){}
