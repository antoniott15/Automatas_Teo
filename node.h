#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

template <typename V>
class DsjSet;
template <typename V>
class Node
{
public:
  //typedef typename G::edge edge;
  typedef vector<Node *> NodeSeq;
  typedef unordered_map<Node *, bool> dictNodeAdj;
  typedef typename NodeSeq::iterator NodeIte;

  //EdgeSeq edges;
  Node() {}
  Node(V data, double x, double y)
  {
    this->data = data;
    this->x = x;
    this->y = y;

    rank = 0;
    parent = this;
    countNodeAdj = 0;
  }

  NodeSeq getNodesAdj()
  {
    return nodesAdj;
  }
  void insertNodeAdj(Node *nodeAdj)
  {
    nodesAdj.push_back(nodeAdj);
    countNodeAdj++;
  }
  template <class>
  friend class DsjSet;

  void removeNodeAdj(Node *nodeAdj)
  {
    ni = nodesAdj.begin();
    while (ni != nodesAdj.end())
    {
      if ((*ni) == nodeAdj)
      {
        nodesAdj.erase(ni);
        countNodeAdj--;
        return;
      }
      ni++;
    }
  }
  V getData() { return data; };
  double getX() { return x; }
  double getY() { return y; }
  int getCountNodesAdj() { return countNodeAdj; }

private:
  V data;
  NodeSeq nodesAdj;
  dictNodeAdj dict;
  NodeIte ni;
  int countNodeAdj;
  double x;
  double y;

protected:
  Node<V> *parent;
  int rank;
};

#endif
