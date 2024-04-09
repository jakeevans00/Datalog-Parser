#include "Database.h"
#include "Graph.h"
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
            addRelations();
            addFacts();
        }

        static vector<Graph> makeGraphs(const vector<Rule>& rules) {
            Graph graph(rules.size());
            Graph reverseGraph(rules.size());
            
            for (unsigned int i = 0; i < rules.size(); ++i) {
                //cout << "from rule R" << i << ": " << rules.at(i).toString() << endl;
                for (Predicate bodyPredicate : rules.at(i).getBodyPredicates()) {
                    //cout << "from body predicate: " << bodyPredicate.toString() << endl;
                    for (unsigned int j = 0; j < rules.size(); ++j) {
                        //cout << "to rule R" << j << ": " << rules.at(j).toString() << endl;
                        if (rules.at(j).getHeadPredicate().getId() == bodyPredicate.getId()) {
                            graph.addEdge(i, j);
                            reverseGraph.addEdge(j, i);
                            //cout << "dependency found: (R" << i << ", R" << j << ")" << endl;
                        }
                    }
                }
            }
            // add code to add edges to the graph for the rule dependencies
            vector<Graph> graphs;
            graphs.push_back(graph);
            graphs.push_back(reverseGraph);

            return graphs;
        }
        void interpretQueries() {
            cout << "Query Evaluation" << endl;
            for (Predicate query : datalogProgram.getQueries()) {
                interpretQuery(query);
            }        
        }
        void evaluateRules(vector<vector<int>> sccs) {
            cout << "Rule Evaluation" << endl;       
            set<Tuple> newTuples;

            for (auto& scc : sccs) {
                bool changed = true;
                bool trivial = false;
                int passes = 0;

                string sccString = "";
                for (int ruleIndex : scc) {
                    sccString += "R" + to_string(ruleIndex) + ",";
                }

                cout << "SCC: " << sccString.substr(0, sccString.size() - 1) << endl;

                while (changed) {
                    changed = false;
                    passes++;
                    newTuples.clear();

                    if (scc.size() == 1) {
                        Rule rule = datalogProgram.getRules().at(scc.at(0));
                        string head = rule.getHeadPredicate().getId();
                        trivial = true;

                        for (Predicate bodyPredicate : rule.getBodyPredicates()) {
                            if (head == bodyPredicate.getId()) {
                                trivial = false;
                                break;
                            }
                        }
                    }

                    for (int ruleIndex : scc) {
                        Rule rule = datalogProgram.getRules().at(ruleIndex);
                        cout << rule.toString() << endl; 
                        vector<Relation> resultingRelations;

                        for (Predicate bodyPredicate : rule.getBodyPredicates()) {
                            Relation result = interpretPredicate(bodyPredicate);
                            resultingRelations.push_back(result);
                        }

                        Relation joined = resultingRelations.at(0);  
                        for (unsigned int i = 1; i < resultingRelations.size(); ++i) {
                            joined = joined.join(resultingRelations.at(i));
                        }

                        Relation projected = joined.project(rule.getHeadPredicate().getParameters());
                        Relation renamed = projected.rename(rule.getHeadPredicate().getParameters());

                        Relation& headRelation = database.getRelation(rule.getHeadPredicate().getId());
                        newTuples = headRelation.unite(renamed);

                        if (newTuples.size() > 0 ) {
                            changed = true;
                            for (auto& tuple : newTuples) {
                                cout << "  " << tuple.toString(headRelation.getScheme()) << endl;
                            }
                        }

                        if (trivial) {
                            changed = false;
                        }
                    }   
                }
                cout << passes << " passes: " <<  sccString.substr(0, sccString.size() - 1) << endl; 
            }
            cout << endl;
        }

        void interpretQuery(Predicate query) {
            Relation relationCopy = database.getRelationCopy(query.getId());
                
            vector<string> parameters = query.getParameters();
            vector<int> columnIndexes;
            vector<string> newColumnNames;
        
            for (unsigned int i = 0; i < parameters.size(); ++i) {
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
                        for (unsigned k = 0; k < newColumnNames.size(); ++k) {
                            if (newColumnNames.at(k) == value) {
                                j = columnIndexes.at(k); // stored index of column name's first occurence
                                break;
                            }
                        }
                        relationCopy = relationCopy.select(i, j);
                    }
                }
            }


            Relation projected = relationCopy.project(columnIndexes);
            Relation renamed = projected.rename(newColumnNames);
        
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
        

        Database getDatabase() const {
            return database;
        }

    private:
        void addRelations() {
            for (Predicate p : datalogProgram.getSchemes()) {
                Scheme scheme(p.getParameters());
                Relation relation(p.getId(), scheme);
                database.addRelation(relation);
            }
        }

        void addFacts() {
            for (Predicate p : datalogProgram.getFacts()) {
                Tuple tuple(p.getParameters());
                database.addTuple(p.getId(), tuple);
            }
        }

        
        

        Relation interpretPredicate(Predicate predicate) {
            Relation relationCopy = database.getRelationCopy(predicate.getId());

            vector<string> parameters = predicate.getParameters();
            vector<int> columnIndexes;
            vector<string> newColumnNames;
        
            for (unsigned int i = 0; i < parameters.size(); ++i) {
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
                        for (unsigned k = 0; k < newColumnNames.size(); ++k) {
                            if (newColumnNames.at(k) == value) {
                                j = columnIndexes.at(k); // stored index of column name's first occurence
                                break;
                            }
                        }
                        relationCopy = relationCopy.select(i, j);
                    }
                }
            }


            Relation projected = relationCopy.project(columnIndexes);
            Relation renamed = projected.rename(newColumnNames);

            return renamed;
        }
        
};