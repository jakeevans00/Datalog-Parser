#include <string>
#include "Scheme.h"
#include "Tuple.h"
#include <set>
#pragma once

using namespace std;

class Relation {
    private:
        string name;
        Scheme scheme;
        set<Tuple> tuples;
    
    public: 
        Relation () {}
        Relation(const string& name, const Scheme& scheme)
        : name(name), scheme(scheme) {}

        void addTuple(const Tuple& tuple) {
            tuples.insert(tuple);
        }

        void addTuples(const set<Tuple>& tuples) {
            for (const auto& tuple : tuples) {
                addTuple(tuple);
            }
        }

        void deleteTuple(const Tuple& tuple) {
            tuples.erase(tuple);
        }

        set<Tuple> getTuples() const {
            return tuples;
        }

        string getName() const {
            return name;
        }

        Scheme getScheme() const {
            return scheme;
        }

        string toString() const {
            stringstream out;
            
            for (const auto& tuple : tuples) {
                out << "  ";
                for (int i = 0; i < scheme.size(); ++i) {
                    if (i != 0) out << ", ";
                    out << scheme.at(i) + '=';
                    out << tuple.at(i);
                }
            out << "\n";
            }

                
            return out.str();
        }

        // Relational Algebra Operations

        Relation select(int index, const string& value) const {
            Relation result(name, scheme);
            result.addTuples(tuples);

            for (const auto& tuple : tuples) {
                if (tuple.at(index) != value) {
                    result.deleteTuple(tuple);
                }
            }
     
            return result;
        }

        Relation select(int index, int index2) const {
            Relation result(name, scheme);
            result.addTuples(tuples);

            for (const auto& tuple : result.getTuples()) {
                if (tuple.at(index) != tuple.at(index2)) {
                    result.deleteTuple(tuple);
                } 
            }
            return result;
        }

        Relation project(const vector<int>& indices) const {
            Scheme newScheme;
            for (int i : indices) {
                if (!newScheme.find(scheme.at(i))) {
                    newScheme.push_back(scheme.at(i));
                }
            }
            
            Relation result(name, newScheme);
            for (const auto& tuple : tuples) {
                Tuple newTuple;
                for (int i : indices) {
                    newTuple.push_back(tuple.at(i));
                }
                result.addTuple(newTuple);
            }
            return result;
        }

        Relation project_2(vector<string> columns) const {
            Scheme newScheme;
            for (string& col : columns) {
                if (!newScheme.find(col)) {
                    newScheme.push_back(col);
                }
            }
            
            Relation result(name, newScheme);
            for (const auto& tuple : tuples) {
                Tuple newTuple;
                for (string& col : columns) {
                    newTuple.push_back(tuple.at(scheme.findIndex(col)));
                }
                result.addTuple(newTuple);
            }
            return result;
        }

        Relation rename(const Scheme& newScheme) const {
            Relation result(name, newScheme);
            result.addTuples(tuples);
            return result;
        }

        Relation join(const Relation& right) {
            const Relation& left = *this;
            Relation result;
            result.scheme = left.scheme;
            vector<pair<int, int>> matchingColumns;


            for (unsigned i = 0; i < left.scheme.size(); i++) {
                for (unsigned j = 0; j < right.scheme.size(); j++) {
                    if (left.scheme.at(i) == right.scheme.at(j)) {
                        matchingColumns.push_back(make_pair(i, j));
                    }
                }
            }

            vector<string> uniqueColumns;

            for (unsigned i = 0; i < right.scheme.size(); i++) {
                bool unique = true;
                for (const auto& pair : matchingColumns) {
                    if (pair.second == i) {
                        unique = false;
                    }
                }
                if (unique) {
                    uniqueColumns.push_back(right.scheme.at(i));
                }
            }

            for (unsigned i = 0; i < uniqueColumns.size(); i++) {
                result.scheme.push_back(uniqueColumns.at(i));
            }

            for (auto& leftTuple : left.tuples) {
                for (auto& rightTuple : right.tuples) {
                    if (joinable(left.scheme, right.scheme, leftTuple, rightTuple)) {
                        Tuple newTuple = leftTuple;
                        for (unsigned i = 0; i < right.scheme.size(); i++) {
                            bool unique = true;
                            for (const auto& pair : matchingColumns) {
                                if (pair.second == i) {
                                    unique = false;
                                }
                            }
                            if (unique) {
                                newTuple.push_back(rightTuple.at(i));
                            }
                        }
                        result.addTuple(newTuple);
                    }
                }
            }

            return result;
        }

        set<Tuple> unite(const Relation& right) {
            set<Tuple> result;

            for (const auto& tuple : right.tuples) {
                auto insertionResult = tuples.insert(tuple);
                if (insertionResult.second) {
                    result.insert(tuple);
                }
            }

            return result;
        }

        static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
            for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {        
                for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                    if (leftScheme.at(leftIndex) == rightScheme.at(rightIndex) && leftTuple.at(leftIndex) != rightTuple.at(rightIndex)) {
                        return false;
                    }
                }
            }
   
            return true;
      }
};