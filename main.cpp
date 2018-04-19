#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Processo.h"

#define Quantum 2

using namespace std;

/*Funções para serem usadas como terceiro parâmetro do sort do vector
que são estruturadas para casamento com o _Compare do C++*/


bool compInicio(Processo a, Processo b){
    return (a.tInicio < b.tInicio);
}

bool compPico(Processo a, Processo b){
    return(a.tPico < b.tPico);
}


vector <Processo> LeArquivo(const char *arq){
    ifstream arquivo;
    arquivo.open(arq, ios::in);
    int tInicio, tPico;

    vector <Processo> a;

    while(arquivo.good()){
        arquivo >> tInicio >> tPico;

        Processo aux(tPico, tInicio);

        a.push_back(aux);

    }
    arquivo.close();
    return a;
}
/*
Função que simula o escalonador do tipo First Come First Served
A mais simples das três, basta ordenar por chegada e somar/subtrair os tempos
e dividir pela quantidade de processos para obter os valores médios.
*/

void FCFS(vector <Processo> listaProcesso){

    int tEspera = 0, tResposta = 0, tRetorno = 0, tExec = 0;
    int tamLista = listaProcesso.size();

    sort(listaProcesso.begin(), listaProcesso.end(), compInicio);

    while(!listaProcesso.size() == 0){
        Processo a = listaProcesso[0];
        listaProcesso.erase(listaProcesso.begin());

        if(a.tInicio > tExec){
            tExec = a.tInicio;
        }

        tEspera += tExec - a.tInicio;
        tResposta += tExec - a.tInicio;
        tRetorno += + tExec + a.tPico - a.tInicio;
        tExec += a.tPico;

    }

    float tEsperaM = (float)tEspera/(float)tamLista;
    float tRespostaM = (float)tResposta/(float)tamLista;
    float tRetornoM = (float)tRetorno/(float)tamLista;

    cout << fixed << setprecision(1);//Requisitado na atividade
    cout << "FCFS " << tRetornoM << " " << tRespostaM << " " << tEsperaM << endl;


}

void SJF(vector <Processo> listaProcesso){

    int tEspera = 0, tResposta = 0, tRetorno = 0, tExec = 0, tInicioMin = 2147483647;
    int tamLista = listaProcesso.size();
    float tEsperaM, tRespostaM, tRetornoM;
    vector <Processo> listaAux;
    //sort(listaProcesso.begin(), listaProcesso.end(), compPico);

    for(int i = 0; i < listaProcesso.size(); i++){
        if(listaProcesso[i].tInicio == 0){
            listaAux.push_back(listaProcesso[i]);
            listaProcesso.erase(listaProcesso.begin()+i);
            i--;
        }
    }

    while(listaAux.size() > 0 || listaProcesso.size() > 0){
        if(listaAux.size() == 0 && listaProcesso.size() > 0){
                for(int j = 0; j < listaProcesso.size(); j++){
                    if(listaProcesso[j].tInicio < tInicioMin){
                        tInicioMin = listaProcesso[j].tInicio;
                    }

                }
                if(tInicioMin > tExec)
                    tExec = tInicioMin;//"Caminha até o próximo tempo de inicio minimo"
        }
        for(int i = 0; i < listaProcesso.size(); i++){
            if(listaProcesso[i].tInicio <= tExec){
                listaAux.push_back(listaProcesso[i]);
                listaProcesso.erase(listaProcesso.begin()+i);
                i--;
            }
        }
        sort(listaAux.begin(), listaAux.end(), compPico);
        Processo a = listaAux[0];
        listaAux.erase(listaAux.begin());

        tResposta = tResposta + tExec - a.tInicio;
        tEspera = tEspera + tExec - a.tInicio;
        tRetorno = tRetorno + tExec + a.tPico - a.tInicio;
        tExec = tExec + a.tPico;

    }

    tEsperaM = (float)tEspera/(float)tamLista;
    tRespostaM = (float)tResposta/(float)tamLista;
    tRetornoM = (float)tRetorno/(float)tamLista;

    cout << fixed << setprecision(1);//
    cout << "SJF " << tRetornoM << " " << tRespostaM << " " << tEsperaM << endl;
}

/*void RR(vector <Processo> listaProcesso)
{
    int tResposta = 0, tRetorno = 0, tEspera = 0;
    float tRespostaM = 0, tRetornoM = 0, tEsperaM = 0;
    int tExec = 0;
    int tamLista = listaProcesso.size();
    int numProcesso = tamLista;
    vector <Processo> listaAux;
    Processo primeiro(0,0);

    while(tamLista != 0)
    {
        for (int i = 0; i < listaAux.size(); i++){
            if(listaAux[i].tInicio == tExec){
                listaProcesso.push_back(listaAux[i]);
                listaAux.erase(listaAux.begin()+i);
                i--;
            }else if(listaAux[i].tInicio < tExec){
                tEspera += tExec - listaAux[i].tInicio;
                listaProcesso.push_back(listaAux[i]);
                listaAux.erase(listaAux.begin()+i);
                i--;
            }
        }
        if(primeiro.tRestante > 0)
        {
            listaProcesso.push_back(primeiro);
        }
        primeiro = listaProcesso[0];
        listaProcesso.erase(listaProcesso.begin());

        if(primeiro.tRestante == primeiro.tPico)
        {
            tResposta += tExec - primeiro.tInicio;
        }

        tExec += Quantum;
        primeiro.tRestante -= Quantum;
        tEspera += Quantum * listaProcesso.size();

        if(primeiro.tRestante <= 0)
        {
            tamLista--;
            tExec += primeiro.tRestante;
            cout << "RR " << tRetorno << " " << tResposta << " " << tEspera << endl;
            tEspera += (primeiro.tRestante * int(listaProcesso.size()));
            tRetorno += tExec - primeiro.tInicio;
        }
        //cout << "RR " << tRetorno << " " << tResposta << " " << tEspera << endl;

    }

    tRespostaM = (float)tResposta / (float)numProcesso;
    tRetornoM = (float)tRetorno / (float)numProcesso;
    tEsperaM = (float)tEspera / (float)numProcesso;

    cout << "RR " << tRetornoM << " " << tRespostaM << " " << tEsperaM << endl;



}

*/



int main()
{

    vector <Processo> p, q, r;//Vetores para os três escalonamentos diferentes
    p = q = r = LeArquivo("arquivo.txt");
    FCFS(p);
    SJF(q);
    //RR(r);
}
