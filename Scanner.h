#pragma once
#include <string>
#include "Token.h"
#include <cctype>
#include <vector>
#include <unordered_map>

class Scanner {
    private:
        std::string input;
        int lineNumber;
        std::vector<Token> tokens;
        std::unordered_map<std::string, TokenType> keywords = {
            {"Schemes", SCHEMES},
            {"Facts", FACTS},
            {"Rules", RULES},
            {"Queries", QUERIES}
        };

    public:
        Scanner(std::string input) : input(input), lineNumber(1) {}

        void scanTokens(); 
        void scanString();
        void scanComment();
        void scanID();

        const std::vector<Token>& getTokens() const {
            return tokens;
        }

        std::size_t getTokenLength() {
            return tokens.size();
        }
};

void Scanner::scanID() {
    std::string str = "";
    if (!input.empty()) {
        str += input.at(0);
        input = input.substr(1);
    }
    while(!input.empty() && isalnum(input.at(0))) {
        str += input.at(0);
        input = input.substr(1);
    }

    if (str.length() >= 1) {
        if (keywords.find(str) != keywords.end()) {
            Token t = Token(keywords[str], str, lineNumber);
            tokens.push_back(t);
            return;
        } else {
            Token t = Token(ID, str, lineNumber);
            tokens.push_back(t);
            return;
        }
    } 
    return;
}

void Scanner::scanComment() {
    std::string str = "";
    if (!input.empty()) {
        str += input.at(0);
        input = input.substr(1);
    }

    while (!input.empty() && input.at(0) != '\n') {
        str += input.at(0);
        input = input.substr(1);
    }
    // Remove comments from output

    //Token t = Token(COMMENT, str, lineNumber);
    //tokens.push_back(t);

    if (!input.empty()) {
        return;
    }
    else {
        Token t2 = Token(END_F, "", lineNumber);
        tokens.push_back(t2);
    }

    return;
}

void Scanner::scanString() {
    std::string str = "";
    int startLine = lineNumber;

    if (!input.empty()) {
        str+= input.at(0);
        input = input.substr(1);   
    }

    while (!input.empty() && input.at(0) != '\'') {
        if (input.at(0) == '\n') {
            lineNumber++;
        }
        str += input.at(0);
        input = input.substr(1);
    }

    if (!input.empty()) {
        str += input.at(0);
        input = input.substr(1);

        Token t = Token(STRING, str, startLine);
        tokens.push_back(t);
        return;
    }
    else {
        Token t = Token(UNDEFINED, str, startLine);
        tokens.push_back(t);
        return;
    }
    return;
}

void Scanner::scanTokens() {
    while (true) {
        if (input.empty()) {
            Token t = Token(END_F, "", lineNumber);
            tokens.push_back(t);
            return;
        } else if (input.at(0) == '\n') {
            lineNumber++;
        } else if (input.at(0) == '\'') {
            scanString();
            continue;
        } else if (input.at(0) == ',') {
            Token t = Token(COMMA, ",", lineNumber);
            tokens.push_back(t);
        } else if (input.at(0) == '.') {
            Token t = Token(PERIOD, ".", lineNumber);
            tokens.push_back(t);
        } else if (input.at(0) == '?') {
            Token t = Token(Q_MARK, "?", lineNumber);
            tokens.push_back(t);
        } else if (input.at(0) == '(') {
            Token t = Token(LEFT_PAREN, "(", lineNumber);
            tokens.push_back(t);
        } else if (input.at(0) == ')') {
            Token t = Token(RIGHT_PAREN, ")", lineNumber);
            tokens.push_back(t);
        } else if (input.at(0) == ':') {
            if (input.at(1) == '-') {
                Token t = Token(COLON_DASH, ":-", lineNumber);
                tokens.push_back(t);
                input = input.substr(1);
            } else {
                Token t = Token(COLON, ":", lineNumber);
                tokens.push_back(t);
            }
        } else if (input.at(0) == '*') {
            Token t = Token(MULTIPLY, "*", lineNumber);
            tokens.push_back(t);
        } else if (input.at(0) == '+') {
            Token t = Token(ADD, "+", lineNumber);
            tokens.push_back(t);
        } else if (input.at(0) == '#') {
            scanComment();
            continue;
        } else if (isalpha(input.at(0))) {
            scanID();
            continue;
        } else if (isspace(input.at(0))) {
            input = input.substr(1);
            continue;
        } else {
            Token t = Token(UNDEFINED, input.substr(0,1), lineNumber);
            tokens.push_back(t);
        }
        if (!input.empty()) {
            input = input.substr(1);
        }

    }
    return;
}       

