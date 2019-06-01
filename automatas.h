#ifndef Automata_H
#define Automata_H

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>

#include "node.h"
#include "edge.h"

using namespace std;
template <typename GV, typename GE>
class Automata
{
public:
  void readFile(string);
  typedef Node<GV> node;
  typedef Edge<GE, GV> edge;
  typedef vector<node *> NodeSeq;
  typedef list<edge *> EdgeSeq;
  typedef set<node *> NodeSet;
  typedef unordered_map<GV, node *> dictNode;
  typedef map<pair<GV, GV>, edge *> dictGetEdge;
  typedef map<pair<GV, GV>, bool> dictEdges;
  typedef map<pair<GV, GV>, GE> matrixAdj;
  typedef typename NodeSeq::iterator NodeIte;
  typedef typename EdgeSeq::iterator EdgeIte;

  Automata(bool dirg, bool pondg) : dir(dirg), pond(pondg) { size = 0; }

  ~Automata()
  {
    while (edges.empty())
    {
      edges.pop_back();
    }
  }

  bool insertNode(GV value, double x, double y)
  {
    if (!dict[value])
    {
      node *n = new node(value, x, y);
      nodes.push_back(n);
      dict[value] = n;
      size++;
      return true;
    }
    return false;
  }
  bool removeNode(GV value)
  {

    if (!dict[value])
      throw printf("Nodo no existe en el grafo\n");

    ni = nodes.begin();
    while (ni != nodes.end())
    {
      if ((*ni)->getData() == value)
      {
        nodes.erase(ni, ni + 1);

        for (auto x : nodes)
          removeEdge(value, x->getData());

        delete dict[value];
        dict[value] = nullptr;
        size--;
        return true;
      }
      ni++;
    }
    return false;
  }

  bool insertEdge(GV node1, GV node2)
  {
    if (pond)
      throw printf("Debe ingresar un peso para la arista\n");

    if (!dictE[make_pair(node1, node2)])
    {

      edge *e = new edge(dict[node1], dict[node2]);

      edges.push_back(e);
      dictE[make_pair(node1, node2)] = 1;

      node *n1 = dict[node1];
      node *n2 = dict[node2];
      mAdj[make_pair(node1, node2)] = 1;
      n1->insertNodeAdj(n2);
      if (!dir)
      {
        dictE[make_pair(node2, node1)] = 1;
        mAdj[make_pair(node2, node1)] = 1;
        n2->insertNodeAdj(n1);
      }
      return true;
    }
    return false;
  }
  bool insertEdge(GE edgeV, GV node1, GV node2)
  {
    if (!pond)
      throw printf("No debe ingresar un peso para la arista\n");

    if (!dictE[make_pair(node1, node2)])
    {

      edge *e = new edge(edgeV, dict[node1], dict[node2]);
      ei = edges.begin();

      while (ei != edges.end() && (*ei)->getData() > edgeV)
        ei++;

      edges.insert(ei, e);
      dictE[make_pair(node1, node2)] = 1;

      mAdj[make_pair(node1, node2)] = edgeV;
      node *n1 = dict[node1];
      node *n2 = dict[node2];
      n1->insertNodeAdj(n2);
      if (!dir)
      {
        dictE[make_pair(node2, node1)] = 1;
        n2->insertNodeAdj(n1);
        mAdj[make_pair(node2, node1)] = edgeV;
      }
      return true;
    }
    return false;
  }
  bool removeEdge(GV node1, GV node2)
  {
    ei = edges.begin();
    if (!dictE[make_pair(node1, node2)] || (!dir && !dictE[make_pair(node2, node1)]))
      throw printf("Arista no existe en el grafo\n");

    while (ei != edges.end())
    {
      if ((*ei)->nodes[0]->getData() == node1 && (*ei)->nodes[1]->getData() == node2)
      {

        edge *edgetmp = (*ei);
        node *n1 = (*ei)->nodes[0];
        node *n2 = (*ei)->nodes[1];
        n1->removeNodeAdj(n2);

        if (!dir)
        {
          n2->removeNodeAdj(n1);
          dictE[make_pair(node2, node1)] = false;
        }
        edges.erase(ei);
        delete edgetmp;
        dictE[make_pair(node1, node2)] = false;
        return true;
      }
      if (!dir && (*ei)->nodes[1]->getData() == node1 && (*ei)->nodes[0]->getData() == node2)
      {
        edge *edgetmp = (*ei);
        node *n1 = (*ei)->nodes[1];
        node *n2 = (*ei)->nodes[0];
        n1->removeNodeAdj(n2);
        n2->removeNodeAdj(n1);
        edges.erase(ei);
        delete edgetmp;
        dictE[make_pair(node1, node2)] = false;
        dictE[make_pair(node2, node1)] = false;
        return true;
      }
      ei++;
    }
    return false;
  }
  node *findNode(GV node1)
  {
    return dict[node1];
  }
  edge *findEdge(GV node1, GV node2)
  {
    return dictE[make_pair(node1, node2)];
  }

  Automata *BFS(GV begining)
  {
    int count = 0;
    auto hasNode = dict[begining];
    if (hasNode)
    {
      auto bfsAutomata = new Automata(dir, pond);
      for (ni = nodes.begin(); ni != nodes.end(); ni++)
      {
        bfsAutomata->insertNode((*ni)->getData(), (*ni)->getX(), (*ni)->getY());
        count++;
      }

      bool *frequented = new bool[count];

      for (int i = 0; i < count; i++)
        frequented[i] = false;

      queue<node *> container;
      auto currNode = getNode(begining);
      container.push(currNode);
      while (!container.empty())
      {
        currNode = container.front();
        container.pop();
        vector<node *> listAdjs = currNode->getNodesAdj();
        ei = edges.begin();
        for (auto i = listAdjs.begin(); i != listAdjs.end() && ei != edges.end(); ++i, ++ei)
        {

          if (!frequented[(*i)->getData() - 1])
          {
            bfsAutomata->insertEdge((*ei)->getData(), currNode->getData(), (*i)->getData());
            container.push(*i);
            frequented[(*i)->getData() - 1] = true;
          }
        }
        frequented[currNode->getData() - 1] = true;
      }
      return bfsAutomata;
    }
    else
      throw out_of_range("No se enceuntra el nodo");
  }

  Automata *DFS(GV begining)
  {
    int count = 0;
    auto hasNode = dict[begining];
    if (hasNode)
    {
      auto bfsAutomata = new Automata(dir, pond);
      for (ni = nodes.begin(); ni != nodes.end(); ni++)
      {
        bfsAutomata->insertNode((*ni)->getData(), (*ni)->getX(), (*ni)->getY());
        count++;
      }

      bool *frequented = new bool[count];

      for (int i = 0; i < count; i++)
        frequented[i] = false;

      stack<node *> container;
      auto currNode = getNode(begining);
      container.push(currNode);
      while (!container.empty())
      {
        currNode = container.top();
        container.pop();
        vector<node *> listAdjs = currNode->getNodesAdj();
        ei = edges.begin();
        for (auto i = listAdjs.begin(); i != listAdjs.end() && ei != edges.end(); ++i)
        {
          if (!frequented[(*i)->getData() - 1])
          {
            bfsAutomata->insertEdge((*ei)->getData(), currNode->getData(), (*i)->getData());
            container.push(*i);
            frequented[(*i)->getData() - 1] = true;
          }
        }
        frequented[currNode->getData() - 1] = true;
      }
      return bfsAutomata;
    }
    throw out_of_range("No se enceuntra el nodo");
  }

  void print()
  {
    ni = nodes.begin();
    cout << "==========================";
    cout << "\n   Imprimiendo Nodes:" << endl;
    cout << "==========================\n";

    while (ni != nodes.end())
    {
      cout << "Vértice: " << (*ni)->getData();
      NodeSeq nodestmp = (*ni)->getNodesAdj();
      NodeIte ni2 = nodestmp.begin();
      cout << " | Vertices Adj: ";
      for (; ni2 != nodestmp.end(); ni2++)
      {
        cout << (*ni2)->getData() << " ";
      }
      cout << endl;
      cout << "-----------------------------" << endl;
      ni++;
    }
    cout << endl;
    cout << "==========================";
    cout << "\n   Imprimiendo Edges:" << endl;
    cout << "==========================\n";
    ei = edges.begin();
    while (ei != edges.end())
    {
      node **arr = (*ei)->getNodes();
      cout << "Vertices( " << arr[0]->getData() << ", " << arr[1]->getData() << ")";
      cout << "\t|\tPeso: " << (*ei)->getData() << endl;
      ei++;
    }
  }

private:
  NodeSeq nodes;
  EdgeSeq edges;
  dictNode dict;
  dictEdges dictE;
  dictGetEdge dictGetE;
  matrixAdj mAdj;
  int size;
  NodeIte ni;
  EdgeIte ei;
  bool dir;
  bool pond;

  node *getNode(GV value)
  {
    if (dict[value])
      return dict[value];
    return nullptr;
  }
};

template <typename GV, typename GE>
void Automata<GV, GE>::readFile(string fileName)
{
  fstream f(fileName);
  string line;
  int i, sizetmp;
  GV valueNode1, valueNode2;
  GE valueEdge;
  double pos1, pos2;
  if (f.is_open())
  {

    getline(f, line);
    string::size_type cs;
    sizetmp = stoi(line, &cs);

    for (i = 0; i < sizetmp; i++)
    {
      getline(f, line);
      stringstream s(line);
      s >> valueNode1 >> pos1 >> pos2;
      insertNode(valueNode1, pos1, pos2);
    }
    getline(f, line);
    while (getline(f, line))
    {
      stringstream s(line);
      s >> valueNode1 >> valueNode2 >> valueEdge;
      insertEdge(valueEdge, valueNode1, valueNode2);
    }
  }
}

#endif
