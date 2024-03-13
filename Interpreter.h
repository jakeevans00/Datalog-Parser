#include "Database.h"
#include <algorithm>
#include <map>
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
            for (Predicate query : datalogProgram.getQueries()) {

                // Get relation with same name as query
                Relation relationCopy = database.getRelationCopy(query.getId());
                
                vector<string> parameters = query.getParameters();
                vector<int> columnIndexes;
                vector<string> newColumnNames;
            
                for (int i = 0; i < parameters.size(); ++i) {
                    string value = parameters.at(i);

                    if (value.at(0) == '\'') {
                        relationCopy = relationCopy.select(i, value);
                    } else {
                        auto it = std::find(newColumnNames.begin(), newColumnNames.end(), value);

                        if (it == newColumnNames.end()) { // only add if not already in newColumnNames
                            columnIndexes.push_back(i);
                            newColumnNames.push_back(value);
                        } else {
                            int j = i + 1;
                            for (int k = 0; k < newColumnNames.size(); ++k) {
                                if (newColumnNames.at(k) == value) {
                                    j = columnIndexes.at(k); // stored index of column name's first occurence
                                    break;
                                }
                            }
                            relationCopy = relationCopy.select(i, j);
                        }
                    }
                }

                // for (int i = 0; i < mapSize; ++i) {
                //     cout << columnIndexes[i] << " " << newColumnNames[i] << endl;
                // }

                // cout << "Relation after select: \n" << relationCopy.toString();
                Relation projected = relationCopy.project(columnIndexes);
                // cout << "Relation after project: \n" << projected.toString();
                Relation renamed = projected.rename(newColumnNames);
                // cout << "Relation after rename: \n" << renamed.toString();
         
                cout << query.toString() << "? ";
                if (relationCopy.getTuples().size() > 0) {
                    cout << "Yes(" << relationCopy.getTuples().size() << ")" << endl;
                    if (newColumnNames.size() > 0) {
                        cout << renamed.toString();
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