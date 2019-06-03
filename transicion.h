//
// Created by alejandro on 6/2/19.
//

#ifndef PARCIAL_TRANSICION_H
#define PARCIAL_TRANSICION_H

class estado;

struct transicion
{
    estado *inicio;
    char simbolo;
    estado *final;

    transicion(estado *inicio, char simbolo, estado *final) : inicio{inicio}, simbolo{simbolo}, final{final} {}
};

#endif //PARCIAL_TRANSICION_H
