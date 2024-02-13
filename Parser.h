#include <vector>
#include "Token.h"
#include <iostream>

class Parser {
    private:
        std::vector<Token> tokens;
        int currentToken;

       
    public:
        TokenType tokenType() const {
            return tokens.at(0).getType();
        }

        void advanceToken() {
            tokens.erase(tokens.begin());
        }

        void throwError() {
            std::cout << "Failure!" << std::endl;
        }
        Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

        
};