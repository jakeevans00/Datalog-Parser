#include <set>
#pragma once

using namespace std;

class Node {

 private:

  set<int> adjacentNodeIDs;
  int postOrder;

 public:

  void addEdge(int adjacentNodeID) {
    adjacentNodeIDs.insert(adjacentNodeID);
  }

  string toString() {
    string output;
    for (set<int>::iterator it = adjacentNodeIDs.begin(); it != adjacentNodeIDs.end(); ++it) {
        output += "R" + to_string(*it) + ",";
    }

    return output;
  }

};