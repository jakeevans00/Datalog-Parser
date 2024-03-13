#include "Database.h"
#include <algorithm>
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

                vector<int> columnsToKeep;
                vector<string> queryParameters;
                Scheme newParameters;

                for (int i = 0; i < q.getParameters().size(); i++) {
                    string currParam = q.getParameters().at(i);

                    if (currParam.at(0) != '\'') {
                        if (!relation.getScheme().find(currParam)) {
                            newParameters.push_back(currParam);
                        } else {
                            auto it = find(queryParameters.begin(), queryParameters.end(), currParam);
                            if (it == queryParameters.end()) {
                                columnsToKeep.push_back(i);
                            }
                            queryParameters.push_back(currParam);
                        }
                    }
                }
         
                Relation result = relation.evaluateQuery(q);
                Relation projectedResult = result.project(columnsToKeep);
                Relation renamedResult = result.rename(newParameters);

                cout << q.toString() << "? ";
                if (result.getTuples().size() > 0) {
                    cout << "Yes(" << result.getTuples().size() << ")" << endl;
                    if (columnsToKeep.size() > 0) {
                        cout << projectedResult.toString();
                    }
                    if (newParameters.size() > 0) {
                        cout << renamedResult.toString();
                    }
                } else {
                    cout << "No" << endl;
                }
            }
        }

        Database getDatabase() {
            return database;
        }
};