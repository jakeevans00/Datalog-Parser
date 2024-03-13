#include <string>
#include <vector>
#pragma once

using namespace std;

class Scheme {

private:

  vector<string> names;

public:
  Scheme() {}
  Scheme(vector<string> names) : names(names) { }

  unsigned size() const {
    return names.size();
  }

  void push_back(const string& name) {
    names.push_back(name);
  }

  int findIndex(const string& name) const {
    for (int i = 0; i < names.size(); i++) {
      if (names.at(i) == name) {
        return i;
      }
    }
    return -1;
  }

  bool find(const string& name) const {
    for (const string& n : names) {
      if (n == name) {
        return true;
      }
    }
    return false;
  }

  const string& at(int index) const {
    return names.at(index);
  }

};