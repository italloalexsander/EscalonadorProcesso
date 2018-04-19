#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Processo.h"

#define Quantum 2

using namespace std;

/*Funções para serem usadas como terceiro parâmetro do sort do vector
que são estruturadas para casamento com o _Compare do C++

Nome: Itallo Alexsander da Fonseca
Matrícula: 11500777

Para compilar, basta abrir o cmd no local onde estão os arquivos
E inserir: "g++ -o main main.cpp Processo.cpp"
Para executar, ainda no cmd é só digitar: "main.exe"
O arquivo.txt pode ser alterado sem a necessidade de recompilar o executavel

*/


bool compInicio(Processo a, Processo b){
    return (a.tInicio < b.tInicio);
}

bool compPico(Processo a, Processo b){
    return(a.tPico <= b.tPico);
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

void SJF(vector <Processo> listaProcesso)
{

    int tEspera = 0, tResposta = 0, tRetorno = 0, tExec = 0, tInicioMin = 1000000;
    int tamLista = listaProcesso.size();
    int numProcesso = tamLista;
    float tEsperaM, tRespostaM, tRetornoM;
    vector <Processo> listaPronto;

    while(numProcesso != 0)
    {
        for(int i = 0; i < listaProcesso.size();i++)
        {
            if(listaProcesso[i].tInicio <= tExec)
            {
                    listaPronto.push_back(listaProcesso[i]);
                    listaProcesso.erase(listaProcesso.begin()+i);
                    i--;
            }
        }

        sort(listaPronto.begin(), listaPronto.end(), compPico);

        Processo primeiro = listaPronto[0];
        numProcesso--;
        listaPronto.erase(listaPronto.begin());

        tEspera += tExec - primeiro.tInicio;
        tResposta += tExec - primeiro.tInicio;
        tExec += primeiro.tPico;
        tRetorno += tExec - primeiro.tInicio;
    }

    tRetornoM = (float)tRetorno / (float)tamLista;
    tRespostaM = (float)tResposta / (float)tamLista;
    tEsperaM = (float)tEspera / (float)tamLista;

    cout << fixed << setprecision(1);//
    cout << "SJF " << tRetornoM << " " << tRespostaM << " " << tEsperaM << endl;

}

void RR(vector <Processo> listaProcesso)
{
    int tResposta = 0, tRetorno = 0, tEspera = 0;
    float tRespostaM = 0, tRetornoM = 0, tEsperaM = 0;
    int tExec = 0;
    int tamLista = listaProcesso.size();
    int numProcesso = tamLista;
    vector <Processo> listaProntos;
    Processo primeiro(0,0);

    while(numProcesso != 0)
    {
        for (int i = 0; i < listaProcesso.size(); i++)
        {
            if(listaProcesso[i].tInicio == tExec)
            {
                listaProntos.push_back(listaProcesso[i]);
                listaProcesso.erase(listaProcesso.begin()+i);
                i--;
            }else if(listaProcesso[i].tInicio < tExec)
            {
                tEspera += tExec - listaProcesso[i].tInicio;
                listaProntos.push_back(listaProcesso[i]);
                listaProcesso.erase(listaProcesso.begin()+i);
                i--;
            }
        }
        if(primeiro.tRestante > 0)
        {
            listaProntos.push_back(primeiro);
        }
        primeiro = listaProntos[0];
        listaProntos.erase(listaProntos.begin());

        if(primeiro.tRestante == primeiro.tPico)
        {
            tResposta += tExec - primeiro.tInicio;
        }

        tExec += Quantum;
        primeiro.tRestante -= Quantum;
        tEspera += Quantum * listaProntos.size();

        if(primeiro.tRestante <= 0)
        {
            numProcesso--;
            tExec += primeiro.tRestante;
            tEspera += (primeiro.tRestante * int(listaProntos.size()));
            tRetorno += tExec - primeiro.tInicio;
        }

    }

    tRespostaM = (float)tResposta / (float)tamLista;
    tRetornoM = (float)tRetorno / (float)tamLista;
    tEsperaM = (float)tEspera / (float)tamLista;

    cout << fixed << setprecision(1);//
    cout << "RR " << tRetornoM << " " << tRespostaM << " " << tEsperaM << endl;



}





int main()
{

    vector <Processo> p, q, r;//Vetores para os três escalonamentos diferentes
    p = q = r = LeArquivo("arquivo.txt");
    FCFS(p);
    SJF(q);
    RR(r);
}
