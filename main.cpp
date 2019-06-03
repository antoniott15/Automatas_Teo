#include <iostream>
#include "automata.h"

int main() {

    automata test;

    test.nuevoEstado(0);
    test.nuevoEstado(1);
    test.nuevoEstado(2);
    test.nuevoEstado(3);

    test.juntarEstados(0,'a',1);
    test.juntarEstados(0,'b',1);
    test.juntarEstados(1,'a',1);
    test.juntarEstados(1,'b',2);
    test.juntarEstados(2,'a',2);
    test.juntarEstados(3,'a',3);
    test.juntarEstados(2,'b',3);
    test.juntarEstados(3,'b',0);

    test.printAutomata();

    automata* powerTest = test.getPowerAutomata();

    for(estado* _estado: powerTest->getEstados()) {
        for (estado *_estado2: _estado->getListaIncluye()) {
            std::cout << _estado2->getNombre();
        }
        std::cout << std::endl;
    }

    return 0;
}