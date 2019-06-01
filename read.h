#ifndef READ_H
#define READ_H

#include "automatas.h"
#include <fstream>
#include <sstream>
#include <string>

/**
 * Clase de ayuda para leer el grafo desde un archivo,
 * no es necesario que la utilicen, podrían implementar su lector
 * desde su grafo o algún otro lado
 **/
template <typename GV, typename GE>
class Read
{
private:
  Automata<GV, GE> g;

public:
  typedef Automata<GV, GE> automata;
  Read(string file)
  {
    fstream f(file);
    string line;
    int rows, i;
    GV valueNode1, valueNode2;
    GE valueEdge;

    double valuex, valuey;
    if (f.is_open())
    {
      getline(f, line);
      string::size_type cz = 0;
      rows = stoi(line, &cz);
      for (i = 0; i < rows; i++)
      {
        getline(f, line);
        stringstream s(line);
        s >> valueNode1 >> valuex >> valuey;
        g.insertNode(valueNode1, valuex, valuey);
      }

      while (getline(f, line))
      {
      }
    }
  }
  automata &getAutomata()
  {
    return g;
  }
};

#endif
