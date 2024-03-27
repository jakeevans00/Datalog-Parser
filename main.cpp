#include <string>
#include <fstream>
#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Relation.h"
#include "Tuple.h"
#include "Interpreter.h"

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

    DatalogProgram dp = p.getDatalogProgram();
    // std::cout << p.getDatalogProgram().toString();

    Interpreter i = Interpreter(dp);
    i.createDatabase();
    i.interpretQueries();

  return 0;

}