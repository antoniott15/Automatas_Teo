//
// Created by alejandro on 6/2/19.
//

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "estado.h"

#ifndef PARCIAL_AUTOMATA_H
#define PARCIAL_AUTOMATA_H



class automata{
public:
    typedef std::vector<estado*> listaEstados;

    automata()=default;

    ~automata(){estados.clear();}

    void nuevoEstado(int nombre){estados.push_back(new estado(nombre));};


    void juntarEstados(int nombreInicial, char simbolo, int nombreFinal){

        estado* inicio= nullptr;
        estado* final= nullptr;

        for(estado* _estado : estados){
            if(_estado->nombreEstado == nombreInicial){
                inicio = _estado;
            }
            if(_estado->nombreEstado == nombreFinal){
                final = _estado;
            }
        }

        if(!inicio || !final){
            std::cout<<"Error de estados"<<std::endl;
            return;
        }
        if(inicio==final){
            inicio->nuevaTransicion(inicio,simbolo,final);
        }
        else {
            inicio->nuevaTransicion(inicio, simbolo, final);
            final->nuevaTransicion(inicio, simbolo, final);
        }
    };

    void printAutomata(){
        std::cout<<std::setw(5)<<"Estado\t"<<"|"<<std::setw(5)<<"\tTransicion"<<std::endl
                <<std::setw(5)<<"\t"<<"|\t"<<std::setw(5)<<"a"<<std::setw(5)<<"b"<<std::endl;

        for(estado* _estado : estados){
            std::cout<<std::setw(5)<<_estado->nombreEstado<<"\t|\t";

            for(transicion* _transicion : _estado->getListaTransiciones()){

                if(_transicion->inicio==_estado && _transicion->inicio !=_transicion->final){
                    std::cout<<std::setw(5)<<_transicion->final->nombreEstado<<" ";
                }
                else if(_transicion->inicio == _transicion->final){
                    std::cout<<std::setw(5)<<"L"<<' ';
                }
            }
            std::cout<<std::endl;
        }
    }

    automata* getPowerAutomata(){
        auto powerAutomata= new automata();
        unsigned int powerSize = pow(estados.size(),2);
        listaEstados incluye;
        for(estado* _estado: estados) {
            powerAutomata->estados.push_back(_estado);
        }

        for(unsigned int counter = 0; counter < powerSize; counter++){
            for (unsigned int i = 0;i<estados.size();i++){
                if(counter & (1<<i)){
                    incluye.push_back(estados[i]);
                }
            }
            if(incluye.size()<2){
                incluye.clear();
                continue;
            }
            powerAutomata->nuevoEstado(counter+estados.size());
            std::copy(incluye.begin(), incluye.end(), std::back_inserter(powerAutomata->estados.back()->incluye));
            incluye.clear();
        }





        return powerAutomata;
    };


    listaEstados getEstados(){
        return estados;
    }

private:
    listaEstados estados;
};

#endif //PARCIAL_AUTOMATA_H
