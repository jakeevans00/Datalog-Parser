#include <string>
#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include <fstream>
#include "Parser.h"

int main(int argc, char* argv[]) {
    std::string input = argv[1];
    std::ifstream file(input);

    if (!file.is_open()) {
        std::cout << "File not found" << std::endl;
        return 1;
    }
    
    std::stringstream fileContents;
    fileContents << file.rdbuf();

    file.close();

    Scanner s = Scanner(fileContents.str());
    s.scanTokens();
    std::vector<Token> tokens = s.getTokens();

    Parser p = Parser(tokens);
    p.parse();
    std::cout << p.getDatalogProgram().toString();

    return 0;

}