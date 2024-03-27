#include <string>

class Rule {
    private:
        Predicate headPredicate;
        std::vector<Predicate> predicates;
    public:
        Rule(Predicate headPredicate) : headPredicate(headPredicate) {}

        void addPredicate(Predicate p) {
            predicates.push_back(p);
        }

        Predicate getHeadPredicate() {
            return headPredicate;
        }

        std::vector<Predicate> getBodyPredicates() {
            return predicates;
        }

        std::string toString() {
            std::string output = headPredicate.toString() + " :- ";
            for (unsigned int i = 0; i < predicates.size(); i++) {
                output += predicates.at(i).toString();
                if (i != predicates.size() - 1) {
                    output += ",";
                }
            }
            output += ".";
            return output;
        }
        
};