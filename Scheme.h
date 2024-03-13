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

  const string& at(int index) const {
    return names.at(index);
  }

};