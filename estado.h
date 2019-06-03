//
// Created by alejandro on 6/2/19.
//



#ifndef PARCIAL_ESTADO_H
#define PARCIAL_ESTADO_H

#include <vector>
#include "transicion.h"

class estado{
public:
    friend class automata;
    typedef std::vector<transicion*> listaTransiciones;
    typedef std::vector<estado*> listaEstados;


    estado(int nombre):nombreEstado{nombre}{};

    ~estado(){transiciones.clear();}


    void nuevaTransicion(estado* inicio, char simbolo, estado* final){
        transiciones.push_back(new transicion(inicio, simbolo, final));
    };




    //FUNCIONES GET

    listaTransiciones getListaTransiciones(){
        return transiciones;
    }

    listaEstados getListaIncluye(){
        return incluye;
    }

private:
    int nombreEstado;
    listaTransiciones transiciones;
    listaEstados incluye;
};

#endif //PARCIAL_ESTADO_H
