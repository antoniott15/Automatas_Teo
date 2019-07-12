#include <iostream>
#include "automata.h"
#include <stdlib.h> /* srand, rand */
#include <time.h>

int main()
{
  int cantNodos,op;
  srand(time(NULL));
  automata test;

  cout << "********SyncroWord********" <<endl;
  cout << "Desea generar la prueba? " << endl;
  cout << "1) Si\n2) No\n"<<endl;
  cin >> op;
  if(op==1){
    test.nuevoEstado(0);
    test.nuevoEstado(1);
    test.nuevoEstado(2);
    test.nuevoEstado(3);

    test.juntarEstados(0, 'a', 1);
    test.juntarEstados(0, 'b', 1);
    test.juntarEstados(1, 'a', 1);
    test.juntarEstados(1, 'b', 2);
    test.juntarEstados(2, 'a', 2);
    test.juntarEstados(3, 'a', 3);
    test.juntarEstados(2, 'b', 3);
    test.juntarEstados(3, 'b', 0);
  }
  
  if(op==2){
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

  auto testPoly = test;




  std::cout << std::endl
            << std::endl
            << "POWER TEST" << std::endl;

  automata *powerTest = test.getPowerAutomata();

  std::cout << std::endl
            << std::endl;

  for (estado *_estado : powerTest->getEstados())
  {
    std::cout << _estado->getNombre() << " ";
    for (estado *_estado2 : _estado->getListaIncluye())
    {
      std::cout << _estado2->getNombre();
    }
    std::cout << std::endl;
  }

  std::cout << std::endl
            << std::endl;



  powerTest->printAutomata();


    std::cout << "Tiene palabra sincronizadora: "<< (powerTest->polinomial()?" Si":" No")<<endl;

    auto bfs = powerTest->BFS();






  

    /*  cout << bfs->reset(19)<<endl;


  for (estado *_estado : powerTest->getEstados())
  {
    for (estado *_estado2 : _estado->getListaIncluye())
    {
      std::cout << _estado2->getNombre();
    }
    std::cout << std::endl;
  }
*/

    return 0;
}
