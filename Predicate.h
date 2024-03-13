#include <string>
#include <vector>
#include "Parameter.h"
#pragma once

using namespace std;

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

        std::string getId() {
            return id;
        }

        void setId(std::string id) {
            this->id = id;
        }

        vector<string> getParameters() {
            vector<string> output;
            for (Parameter p : parameters) {
                output.push_back(p.toString());
            }
            return output;
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