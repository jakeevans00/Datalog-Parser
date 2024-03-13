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
        set<Tuple> resultTuples;
    
    public: 
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

        string printVariables() {
            stringstream out;

            for (const auto& tuple : resultTuples) {
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

        Relation evaluateQuery(Predicate query) const {
            Relation result(name, scheme);
            result.addTuples(tuples);
            
            vector<string> parameters = query.getParameters();
            vector<int> indices;
           
            for (int i = 0; i < parameters.size(); ++i) {
                if (parameters.at(i).at(0) == '\'') {
                    result = result.select(i, parameters.at(i), result);
                } else {
                    bool found = false;
                    indices.push_back(i);

                    for (int j = i; j < scheme.size(); ++j) {
                        if (parameters.at(i) == scheme.at(j)) {
                            result = result.select(i, j, result);
                            found = true;
                        }
                    }   
                }
            }
            return result;
        }

        Relation select(int index, const string& value, Relation result) const {

            for (const auto& tuple : tuples) {
                if (tuple.at(index) != value) {
                    result.deleteTuple(tuple);
                }
            }
     
            return result;
        }

        Relation select(int index, int index2, Relation result) const {
            for (const auto& tuple : tuples) {
                if (tuple.at(index) != tuple.at(index2)) {
                    result.deleteTuple(tuple);
                } 
            }
            return result;
        }

        Relation rename(const Scheme& newScheme) const {
            Relation result(name, newScheme);
            result.addTuples(tuples);
            return result;
        }

        vector<int> getIndices(const vector<string>& parameters) const {
            vector<int> indices;
            for (int i = 0; i < parameters.size(); ++i) {
                for (int j = 0; j < scheme.size(); ++j) {
                    if (parameters.at(i) == scheme.at(j)) {
                        indices.push_back(j);
                    }
                }
            }
            return indices;
        }
        
        Relation project(const vector<int>& indices) const {
            Scheme newScheme;
            for (int i : indices) {
                newScheme.push_back(scheme.at(i));
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
};