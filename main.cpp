#include <iostream>
#include "automata.h"
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdexcept>
int main()
{
  int cantNodos, op;
  srand(time(NULL));
  long compTime;
  struct timeval start;
  struct timeval finish;
  double Time;
  automata test;

  cout << "********SyncroWord********" << endl;
  cout << "Desea generar la prueba? " << endl;
  cout << "1) Si\n2) No\n"
       << endl;
  cin >> op;
  if (op == 1)
  {
    test.nuevoEstado(1);
    test.nuevoEstado(2);
    test.nuevoEstado(3);
    test.nuevoEstado(4);

    test.juntarEstados(1, 'a', 2);
    test.juntarEstados(1, 'b', 2);
    test.juntarEstados(2, 'a', 2);
    test.juntarEstados(2, 'b', 3);
    test.juntarEstados(3, 'a', 3);
    test.juntarEstados(4, 'a', 4);
    test.juntarEstados(3, 'b', 4);
    test.juntarEstados(4, 'b', 1);
    cantNodos = 4;
  }

  if (op == 2)
  {
    cout << "Ingrese la cantidad de nodos, con 0 se generaran la cantidad de nodos aleatoriamente: " << endl;
    cin >> cantNodos;

    if (cantNodos == 0)
    {
      cantNodos = rand() % 100 + 1;
    }

    for (int i = 1; i <= cantNodos; i++)
    {
      test.nuevoEstado(i);
    }

    for (int i = 1; i <= cantNodos; i++)
    {
      int newNumber = rand() % cantNodos + 1;
      test.juntarEstados(i, 'a', newNumber);
    }
    for (int i = 1; i <= cantNodos; i++)
    {
      int newNumber = rand() % cantNodos + 1;
      test.juntarEstados(i, 'b', newNumber);
    }
  }

  test.printAutomata();
  test.writeOn("input.txt", cantNodos);
  auto testPoly = test;

  std::cout << "\n\n"
            << "POWER TEST"
            << "\n";
  gettimeofday(&start, 0);
  automata *powerTest = test.getPowerAutomata(cantNodos);

  std::cout << "\n\n";

  for (estado *_estado : powerTest->getEstados())
  {
    std::cout << _estado->getNombre() << " ";
    for (estado *_estado2 : _estado->getListaIncluye())
    {
      std::cout << _estado2->getNombre() << " ";
    }
    std::cout << "\n";
  }

  std::cout << "\n\n";

  powerTest->printAutomata();

  std::cout << "Tiene palabra sincronizadora: " << (powerTest->polinomial() ? " Si" : " No") << endl;
  if (powerTest->polinomial())
  {
    auto bfs = powerTest->BFS(cantNodos);
    bfs->printAutomata();
    auto resetWord = powerTest->reset(bfs, powerTest->polinomial());
  }
  else
  {
    throw std::invalid_argument("No existe palabra de sincronizacion");
  }

  gettimeofday(&finish, 0);

  compTime = (finish.tv_sec - start.tv_sec) * 1000000;
  compTime = compTime + (finish.tv_usec - start.tv_usec);
  Time = compTime / 1000000.0;

  std::cout << "Time execution: " << Time << endl;
  return 0;
}
