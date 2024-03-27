#include <vector>
#include "Predicate.h"
#include "Rule.h"
#include <set>

using namespace std;

class DatalogProgram {
    private:
        std::vector<Predicate> schemes;
        std::vector<Predicate> facts;
        std::vector<Predicate> queries;
        std::vector<Rule> rules;
        std::set<std::string> domain;

    public:
        void addScheme(Predicate p) {
            schemes.push_back(p);
        }

        vector<Predicate> getSchemes() {
            return schemes;
        }

        void addFact(Predicate p) {
            facts.push_back(p);
            for (Parameter param : p.getParameters()) {
                domain.insert(param.toString());
            }
        }

        vector<Predicate> getFacts() {
            return facts;
        }

        void addQuery(Predicate p) {
            queries.push_back(p);
        }

        vector<Predicate> getQueries() {
            return queries;
        }

        void addRule(Rule r) {
            rules.push_back(r);
        }

        vector<Rule> getRules() {
            return rules;
        }

        std::string toString() {
            std::string output = "Schemes(" + std::to_string(schemes.size()) + "):\n";
            for (Predicate p : schemes) {
                output += "  " + p.toString() + '\n';
            }
            output += "Facts(" + std::to_string(facts.size()) + "):\n";
            for (Predicate p : facts) {
                output += "  " + p.toString() + ".\n";
            }
            output += "Rules(" + std::to_string(rules.size()) + "):\n";
            for (Rule r : rules) {
                output += "  " + r.toString() + '\n';
            }
            output += "Queries(" + std::to_string(queries.size()) + "):\n";
            for (Predicate p : queries) {
                output += "  " + p.toString() + "?\n";
            }
            output += "Domain(" + std::to_string(domain.size()) + "):\n";
            for (std::string s : domain) {
                output += "  " +  s + '\n';
            }
            return output;
        }
};