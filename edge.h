#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename E, typename V>
class Edge
{
public:
  typedef Node<V> node;
  node *nodes[2];
  Edge(node *node1, node *node2)
  {
    nodes[0] = node1;
    nodes[1] = node2;
    data = 1;
  }
  Edge(E valueEdge, node *node1, node *node2)
  {
    nodes[0] = node1;
    nodes[1] = node2;
    data = valueEdge;
  }

  E getData() { return data; } //Renombrar a Peso

  node **getNodes() { return nodes; }

  bool operator<(const Edge &other)
  {
    return other.data < this->data;
  }

private:
  E data;
};

#endif
