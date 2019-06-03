#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "estado.h"
#include <queue>
#include <list>

#ifndef PARCIAL_AUTOMATA_H
#define PARCIAL_AUTOMATA_H
using namespace std;
class automata
{
public:
    typedef estado Estado;
    typedef std::vector<estado *> listaEstados;
    typedef std::vector<transicion *> listaTransiciones;
    typedef std::vector<char> lenguaje;

    automata() = default;

    ~automata() { estados.clear(); }

    void nuevoEstado(int nombre) { estados.push_back(new estado(nombre)); };

    void juntarEstados(int nombreInicial, char simbolo, int nombreFinal)
    {

        estado *inicio = nullptr;
        estado *final = nullptr;

        for (estado *_estado : estados)
        {
            if (_estado->nombreEstado == nombreInicial)
            {
                inicio = _estado;
            }
            if (_estado->nombreEstado == nombreFinal)
            {
                final = _estado;
            }
        }

        if (!inicio || !final)
        {
            std::cout << "Error de estados" << std::endl;
            return;
        }
        else
        {
            inicio->nuevaTransicion(inicio, simbolo, final);
        }

    };

    void juntarEstados(estado *nombreInicial, char simbolo, estado *nombreFinal)
    {

        estado *inicio = nullptr;
        estado *final = nullptr;

        /* for (estado *_estado : estados)
        {
            if (_estado->nombreEstado == nombreInicial)
            {
                inicio = _estado;
            }
            if (_estado->nombreEstado == nombreFinal)
            {
                final = _estado;
            }
        }*/

        if (!inicio || !final)
        {
            std::cout << "Error de estados" << std::endl;
            return;
        }
        if (inicio == final)
        {
            inicio->nuevaTransicion(inicio, simbolo, final);
        }
        else
        {
            inicio->nuevaTransicion(inicio, simbolo, final);
            final->nuevaTransicion(inicio, simbolo, final);
        }
    };

    automata *getPowerAutomata()
    {
  auto powerAutomata= new automata();
        unsigned int powerSize = pow(estados.size(),2);
        listaEstados incluye;

        for(estado* _estado: estados) {
            powerAutomata->estados.push_back(_estado);
            powerAutomata->getEstados().back()->incluye.push_back(_estado);
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


        listaEstados apunta;
        bool match;
        int matches;

        for(estado* _estado: powerAutomata->estados) { //_estado itera sobre todos los estados del power set
            if (_estado->incluye.size() < 2) {//Se revisa que no sea un singleton
                continue;
            }

            for (char letra : lenguajeAutomata) {//transicion para cada letra

                for (estado *_incluye: _estado->incluye) {//por cara incluye dentro del estado

                    for (transicion *_transicion: _incluye->transiciones) {//por cada transicion dentro de los incluye

                        if (_transicion->simbolo == letra && std::find(apunta.begin(), apunta.end(), _transicion->final) == apunta.end()) {

                            apunta.push_back(_transicion->final);//Todos los estados a los que apunta el _estado actual con la letra actual se meten a apunta
                        }
                    }
                }


                for (estado *_estadoFinal: powerAutomata->estados) {//se compara los nombres de la lista de estados apunta con los nombres de los incluye de todos los estados
                    match = true;
                    matches = 0;
                    if(apunta.size()==_estadoFinal->incluye.size()) {//Calcular numero de matches

                        for(estado* estadoApunta : apunta){
                            for(estado* finalIncluye:_estadoFinal->incluye){
                                if(estadoApunta->getNombre()==finalIncluye->getNombre()){
                                    matches++;
                                    break;
                                }
                            }
                        }
                        if(matches!=_estadoFinal->incluye.size()){match=false;}
                    }
                    else{continue;}

                    if(match){
                        _estado->nuevaTransicion(_estado,letra,_estadoFinal);
                        break;
                    }

                }

                apunta.clear();
            }

        }

        return powerAutomata;
    }

    estado *getValue(int value)
    {
        for (int i = 0; estados.size(); i++)
        {
            if (value == estados[i]->nombreEstado)
            {
                return estados[i];
            }
        }
    }
    automata *BFS(int value)
    {
        auto bfsAutomata = new automata();
        int size = 0;
        for (int i = 0; i <= estados.size(); i++)
        {
            bfsAutomata->nuevoEstado(i);
            size++;
        }
        bool *frequented = new bool[size];
        for (int i = 0; i < size; i++)
            frequented[i] = false;

        queue<estado *> container;

        auto currNode = getValue(value);
        container.push(currNode);

        int i = 0;
        while (!container.empty())
        {
            currNode = container.front();
            container.pop();
            estado *_estado;
            for (transicion *_transicion : _estado->getListaTransiciones())
            {
                i++;
                if (!frequented[i])
                {
                    if (_transicion->inicio == _estado && _transicion->inicio != _transicion->final)
                    {
                        bfsAutomata->juntarEstados(_transicion->inicio->nombreEstado, i % 2 == 0 ? 'a' : 'b', _transicion->final->nombreEstado);
                        container.push(_transicion->inicio);
                        frequented[i] = true;
                    }
                }
            }
        }
        return bfsAutomata;
    }

    void printAutomata()
    {
        std::cout << std::setw(5) << "Estado\t"
                  << "|" << std::setw(5) << "\tTransicion" << std::endl
                  << std::setw(5) << "\t"
                  << "|\t" << std::setw(5) << "a" << std::setw(5) << "b" << std::endl;
        for (estado *_estado : estados)
        {
            std::cout << std::setw(5) << _estado->nombreEstado << "\t|\t";

            for (transicion *_transicion : _estado->getListaTransiciones())
            {
                    std::cout << std::setw(5) << _transicion->final->nombreEstado << ' ';

            }
            std::cout << std::endl;
        }
    }

    listaEstados getEstados()
    {
        return estados;
    }

    listaTransiciones getListaTransiciones()
    {
        return transiciones;
    }

private:
    listaEstados estados;
    listaTransiciones transiciones;
    lenguaje lenguajeAutomata = {'a','b'};
};

#endif //PARCIAL_AUTOMATA_H

