#include <map>
#include <algorithm>
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

  // dfsForest to get the post order of the reverse graph

  stack<int> dfsForest() {
    stack<int> postOrder;
    set<int> visited;

    for (auto& pair: nodes) {
      if (visited.find(pair.first) == visited.end())
        dfs(pair.first, visited, postOrder);
    }

    return postOrder;
  }

  void dfs(int nodeID, set<int>& visited, stack<int>& postOrder) {
    visited.insert(nodeID);

    for (int edge: nodes[nodeID].getEdges()) {
      if (visited.find(edge) == visited.end())
        dfs(edge, visited, postOrder);
    }

    postOrder.push(nodeID);
  }

  // dfs to get the strongly connected components

  vector<vector<int>> dfsForest(stack<int>& postOrder) {
    vector<vector<int>> sccs;
    set<int> visited;

    while (!postOrder.empty()) {
      int nodeID = postOrder.top(); // fix this?
      postOrder.pop();

      if (visited.find(nodeID) == visited.end()) {
        vector<int> scc;
        dfs(nodeID, visited, scc);
        sort(scc.begin(), scc.end());
        sccs.push_back(scc);
      }
    }

    return sccs;
  }

  void dfs(int nodeID, set<int>& visited, vector<int>& scc) {
    visited.insert(nodeID);
    scc.push_back(nodeID);

    for (int edge: nodes[nodeID].getEdges()) {
      if (visited.find(edge) == visited.end())
        dfs(edge, visited, scc);
    }
  }


};