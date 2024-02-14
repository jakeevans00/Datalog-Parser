#include <string>
#include <vector>
#include "Parameter.h"
#pragma once

class Predicate {
    private:
        std::string id;
        std::vector<Parameter> parameters;
    public:
        Predicate(std::string id) : id(id) {}
        Predicate(std::string id, std::vector<Parameter> parameters) : id(id), parameters(parameters) {}

        void addParameter(Parameter p) {
            parameters.push_back(p);
        }

        void setId(std::string id) {
            this->id = id;
        }

        std::vector<Parameter> getParameters() {
            return parameters;
        }

        std::string toString() {
            std::string output = id + "(";
            for (unsigned int i = 0; i < parameters.size(); i++) {
                output += parameters.at(i).toString();
                if (i != parameters.size() - 1) {
                    output += ",";
                }
            }
            output += ")";
            return output;
        }
};