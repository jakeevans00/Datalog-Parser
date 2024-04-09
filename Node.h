#include <set>
#pragma once

using namespace std;

class Node {

 private:

  set<int> adjacentNodeIDs;

 public:

  void addEdge(int adjacentNodeID) {
    adjacentNodeIDs.insert(adjacentNodeID);
  }

  set<int> getEdges() {
    return adjacentNodeIDs;
  }

  string toString() {
    string output;
    for (set<int>::iterator it = adjacentNodeIDs.begin(); it != adjacentNodeIDs.end(); ++it) {
        output += "R" + to_string(*it) + ",";
    }

    return output.substr(0, output.size() - 1);
  }

};