#include <map>
#include "Node.h"

#pragma once

using namespace std;

class Graph {

 private:

  map<int,Node> nodes;

 public:

  Graph(int size) {
    for (int nodeID = 0; nodeID < size; nodeID++)
      nodes[nodeID] = Node();
  }

  void addEdge(int fromNodeID, int toNodeID) {
    nodes[fromNodeID].addEdge(toNodeID);
  }

  string toString() {
    string output;
    for (auto& pair: nodes) {
      output += "R" + to_string(pair.first) + ":" + pair.second.toString() + "\n";
    }

    return output;
  }
};