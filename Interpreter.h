#include "Database.h"
#pragma once

class Interpreter {
    private:
        Database database;
        DatalogProgram datalogProgram;

    public:
        Interpreter(const DatalogProgram& dp) : datalogProgram(dp) {}

        void createDatabase() {
            for (Predicate p : datalogProgram.getSchemes()) {
                Scheme scheme(p.getParameters());
                Relation relation(p.getId(), scheme);
                database.addRelation(relation);
            }

            for (Predicate p : datalogProgram.getFacts()) {
                Tuple tuple(p.getParameters());
                database.addTuple(p.getId(), tuple);
            }

            // TO DO - evaluate rules and queries
            // for (Rule r : datalogProgram.getRules()) {
            //     Relation relation = evaluateRule(r);
            //     database.addRelation(relation);
            // }
        }

        void interpret() {
            createDatabase();
            for (Predicate q : datalogProgram.getQueries()) {

                Relation relation = database.getRelation(q.getId());
         
                Relation result = relation.evaluateQuery(q);
                // vector<int> indices;
                // Relation projectedResult = result.project();

                cout << q.toString() << "? ";
                if (result.getTuples().size() > 0) {
                    cout << "Yes(" << result.getTuples().size() << ")" << endl;
                } else {
                    cout << "No" << endl;
                }
            }
        }

        Database getDatabase() {
            return database;
        }
};