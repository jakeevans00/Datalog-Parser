#include <string>

class Parameter {
    private:
        std::string value;
    public:
        Parameter(std::string value) : value(value) {}
        std::string toString() {
            return value;
        }
        std::string getValue() {
            return value;
        }
        void setValue(std::string value) {
            this->value = value;
        }

        std::string getType() {
            if (value.at(0) == '\'') {
                return "STRING";
            }
            else {
                return "ID";
            }
        }
};