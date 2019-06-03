//
// Created by alejandro on 6/2/19.
//

#include <vector>
#include <iostream>
#include <iomanip>
#include "estado.h"
#include <queue>

#ifndef PARCIAL_AUTOMATA_H
#define PARCIAL_AUTOMATA_H
using namespace std;
class automata
{
public:
    typedef std::vector<estado *> listaEstados;

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
    estado *getEstado(int value)
    {
        for (int i = 0; i < estados.size(); i++)
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
        auto currNode = getEstado(value);
        auto prevNode = currNode;
        container.push(currNode);
        if (!container.empty)
        {
            prevNode = currNode;
            currNode = container.front();
            container.pop();
            vector<estado *> listAdjs = currNode->getListaIncluye();
            for (auto i = listAdjs.begin(); i != listAdjs.end(); ++i)
            {

                if (!frequented[(*i)->getListaIncluye() - 1])
                {
                    bfsAutomata->juntarEstados(*prevNode, ,*currNode);
                    container.push(*i);
                    frequented[(*i)->getData() - 1] = true;
                }
            }
        }
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

                if (_transicion->inicio == _estado && _transicion->inicio != _transicion->final)
                {
                    std::cout << std::setw(5) << _transicion->final->nombreEstado << " ";
                }
                else if (_transicion->inicio == _transicion->final)
                {
                    std::cout << std::setw(5) << "L" << ' ';
                }
            }
            std::cout << std::endl;
        }
    }

    automata *getPowerAutomata()
    {
        auto powerAutomata = new automata();

        return powerAutomata;
    };

private:
    listaEstados estados;
};

#endif //PARCIAL_AUTOMATA_H
