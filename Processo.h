#ifndef PROCESSO_H
#define PROCESSO_H


class Processo
{
    public:
        Processo();
        Processo(int tPico, int tInicio);
        ~Processo();

        int tPico;
        int tInicio;
        int tRestante;

};

#endif // PROCESSO_H
