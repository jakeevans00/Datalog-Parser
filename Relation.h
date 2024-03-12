#include <string>
#include "Scheme.h"
#include "Tuple.h"
#include <set>

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

        string toString() const {
            stringstream out;
            
            for (const auto& tuple : tuples) {
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

            for (const auto& tuple : tuples) {
                if (tuple.at(index) == value) {
                    result.addTuple(tuple);
                }
            }
            
            return result;
        }
};