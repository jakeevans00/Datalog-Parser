#pragma once
#include <string>
#include <sstream>

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN,COLON,COLON_DASH,MULTIPLY,ADD,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,COMMENT,UNDEFINED,END_F
};

class Token {
    private:
        TokenType type;
        std::string value;
        int lineNumber;
        static const std::string typeNames[];

    public:
        Token(TokenType type, std::string value, int lineNumber)
        : type(type), value(value), lineNumber(lineNumber) {}
        

        std::string toString() const {
            std::stringstream out;
            std::string typeStr = typeName(this->type);
            out << "(" << typeStr << "," << "\"" << value << "\"" << "," << lineNumber << ")";
            return out.str();
        }
        
        int getLineNumber() const {
            return lineNumber;
        }

        TokenType getType() const {
            return type;
        }

        std::string getValue() const {
            return value;
        }
        std::string typeName(TokenType type) const {
            return typeNames[type];
        }   
};

const std::string Token::typeNames[] = {
    "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH", "MULTIPLY", "ADD",
    "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT", "UNDEFINED", "EOF"
};