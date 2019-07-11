#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "estado.h"
#include <queue>
#include <list>
#include <map>
#include <string>

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

    automata *getPowerAutomata()
    {
        auto powerAutomata = new automata();
        unsigned int powerSize = pow(estados.size(), 2);
        listaEstados incluye;

        for (estado *_estado : estados)
        {
            powerAutomata->estados.push_back(_estado);
            powerAutomata->getEstados().back()->incluye.push_back(_estado);
        }

        for (unsigned int counter = 0; counter < powerSize; counter++)
        {
            for (unsigned int i = 0; i < estados.size(); i++)
            {
                if (counter & (1 << i))
                {
                    incluye.push_back(estados[i]);
                }
            }
            if (incluye.size() < 2)
            {
                incluye.clear();
                continue;
            }
            powerAutomata->nuevoEstado(counter + estados.size());
            std::copy(incluye.begin(), incluye.end(), std::back_inserter(powerAutomata->estados.back()->incluye));
            incluye.clear();
        }

        listaEstados apunta;
        bool match;
        int matches;

        for (estado *_estado : powerAutomata->estados)
        { //_estado itera sobre todos los estados del power set
            if (_estado->incluye.size() < 2)
            { //Se revisa que no sea un singleton
                continue;
            }

            for (char letra : lenguajeAutomata)
            { //transicion para cada letra

                for (estado *_incluye : _estado->incluye)
                { //por cara incluye dentro del estado

                    for (transicion *_transicion : _incluye->transiciones)
                    { //por cada transicion dentro de los incluye

                        if (_transicion->simbolo == letra && std::find(apunta.begin(), apunta.end(), _transicion->final) == apunta.end())
                        {

                            apunta.push_back(_transicion->final); //Todos los estados a los que apunta el _estado actual con la letra actual se meten a apunta
                        }
                    }
                }

                for (estado *_estadoFinal : powerAutomata->estados)
                { //se compara los nombres de la lista de estados apunta con los nombres de los incluye de todos los estados
                    match = true;
                    matches = 0;
                    if (apunta.size() == _estadoFinal->incluye.size())
                    { //Calcular numero de matches

                        for (estado *estadoApunta : apunta)
                        {
                            for (estado *finalIncluye : _estadoFinal->incluye)
                            {
                                if (estadoApunta->getNombre() == finalIncluye->getNombre())
                                {
                                    matches++;
                                    break;
                                }
                            }
                        }
                        if (matches != _estadoFinal->incluye.size())
                        {
                            match = false;
                        }
                    }
                    else
                    {
                        continue;
                    }

                    if (match)
                    {
                        _estado->nuevaTransicion(_estado, letra, _estadoFinal);
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
        return nullptr;
    }
    automata *BFS(int value)
    {
        estado *root;
        automata *powerAutomata = getPowerAutomata();
        /*       for (auto i = powerAutomata->estados.begin(); i != powerAutomata->estados.end(); i++)
        {

            cout << "incluye" << endl;
            cout << (*i)->incluye.size() << endl;
            root = (*i);
        }
*/
        auto bfsAutomata = new automata();
        int size = powerAutomata->estados.size();

        map<int, bool> frequented;
        for (auto i = powerAutomata->estados.begin(); i != powerAutomata->estados.end(); i++)
        {
            frequented.insert(pair<int, bool>((*i)->getNombre(), false));
        }

        queue<estado *> container;
        auto currNode = getValue(value);
        container.push(currNode);

        while (!container.empty())
        {
            currNode = container.front();
            container.pop();
            if (!frequented[currNode->getNombre()])
            {
                bool exist1 = false;
                for (estado *_estadocheck : bfsAutomata->estados)
                {
                    if (_estadocheck->getNombre() == currNode->getNombre())
                        exist1 = true;
                }
                if (!exist1)
                {
                    bfsAutomata->nuevoEstado(currNode->getNombre());
                }

                frequented[currNode->getNombre()] = true;
                for (transicion *_transicion : currNode->transiciones)
                {
                    if (!frequented[_transicion->final->getNombre()])
                    {

                        container.push(_transicion->final);
                        bool exist = false;
                        for (estado *_estadocheck : bfsAutomata->estados)
                        {
                            if (_estadocheck->getNombre() == _transicion->final->getNombre())
                                exist = true;
                        }
                        if (!exist)
                        {
                            bfsAutomata->nuevoEstado(_transicion->final->getNombre());
                            bfsAutomata->juntarEstados(currNode->getNombre(), _transicion->simbolo, _transicion->final->getNombre());
                        }
                    }
                }
            }
        }
        reset(bfsAutomata);
        return bfsAutomata;
    }

    string reset(automata *bfs)
    {
        vector<estado *> estadosOn = bfs->getEstados();
        string syncroWord;


            for (auto *_estado: estados)
            {
                cout << _estado->getNombre() << " " << _estado->incluye.size() << endl;
                for (transicion *_transicion : (_estado->getListaTransiciones()))
                {
                    if (_estado->transiciones.size() == 2)
                    {
                        syncroWord = syncroWord + _transicion->simbolo;
                    }

                }
            }
            cout << "Sync word" << endl;
            cout << syncroWord << endl;
            return syncroWord;
    }

    void printAutomata()
    {
        std::cout << std::setw(5) << "Estado\t"
                  << "|" << std::setw(5) << "\tTransicion" << std::endl;
        for (estado *_estado : estados)
        {
            std::cout << std::setw(5) << _estado->nombreEstado << "\t|\t";

            for (transicion *_transicion : _estado->getListaTransiciones())
            {
                std::cout << std::setw(5) << _transicion->simbolo << _transicion->final->nombreEstado << ' ';
            }
            std::cout << std::endl;
        }
    }

    void writeOn(string nameOf, int numberOfElements)
    {
        ofstream File;
        int width = 1200;
        int heigh = 1200;
        int i = 50;
        int j = 100;
        File.open(nameOf);
        File << numberOfElements << endl;
        for (estado *_estado : estados)
        {
            i = i + 100 + (width / numberOfElements);
            if (i > width)
            {
                i = 50;
                j = j + 75 + (heigh / numberOfElements);
            }
            File << _estado->nombreEstado << " " << i << " " << j << endl;
        }
        File << endl;
        for (estado *_estado : estados)
        {
            for (transicion *_transicion : _estado->getListaTransiciones())
            {
                File << _estado->nombreEstado << " " << _transicion->final->nombreEstado << " " << _transicion->simbolo << "\n";
            }
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
    lenguaje lenguajeAutomata = {'a', 'b'};
};

#endif //PARCIAL_AUTOMATA_H
