#ifndef PARCIAL_TRANSICION_H
#define PARCIAL_TRANSICION_H

class estado;
class automata;
struct transicion
{
    estado *inicio;
    char simbolo;
    estado *final;

    transicion(estado *inicio, char simbolo, estado *final) : inicio{inicio}, simbolo{simbolo}, final{final} {}
    char getSimbol() { return simbolo; }
    estado *getInicio()
    {
        return inicio;
    }
    estado *getFinal() { return final; }
};
extern transicion tran;
#endif //PARCIAL_TRANSICION_H
