#include <vector>
#include <string>
#include "Scheme.h"
#pragma once

using namespace std;

class Tuple {

private:

  vector<string> values;

public:

  Tuple () {}

  Tuple(vector<string> values) : values(values) { }

  unsigned size() const {
    return values.size();
  }

  const string& at(int index) const {
    return values.at(index);
  }

  void push_back(const string& value) {
    values.push_back(value);
  }

  bool operator<(const Tuple t) const {
    return values < t.values;
  }

  string toString(const Scheme& scheme) const {
    const Tuple& tuple = *this;
    stringstream out;
    // fix the code to print "name=value" pairs
    for (unsigned i=0; i < scheme.size(); i++) {
      out << scheme.at(i);
      out << "=";
      out << tuple.at(i);
      if (i != scheme.size() - 1) // Check if it's not the last iteration
          out << ", ";
    }
  
    return out.str();
  }

  // TODO: add more delegation functions as needed

};