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

        Relation rename(const Scheme& newScheme) const {
            Relation result(name, newScheme);
            result.addTuples(tuples);
            return result;
        }
};