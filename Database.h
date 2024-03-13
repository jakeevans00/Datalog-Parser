#include "Relation.h"
#pragma once

class Database {
    private:
        vector<Relation> relations;

    public:
        void addRelation(const Relation& relation) {
            relations.push_back(relation);
        }

        Relation& getRelation(const string& name) {
            for (Relation& relation : relations) {
                if (relation.getName() == name) {
                    return relation;
                }
            }
            throw std::runtime_error("Relation not found");
        }

        Relation getRelationCopy(const string& name) {
            for (const Relation& relation : relations) {
            if (relation.getName() == name) {
                return relation;
            }
            }
            throw std::runtime_error("Relation not found");
        }

        void addTuple(const string& name, const Tuple& tuple) {
            getRelation(name).addTuple(tuple);
        }

};