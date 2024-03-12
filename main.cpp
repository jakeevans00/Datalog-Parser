#include <string>
#include <fstream>
#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Relation.h"
#include "Tuple.h"

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

    vector<string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
      {"'42'", "'Ann'", "'CS'"},
      {"'32'", "'Bob'", "'CS'"},
      {"'64'", "'Ned'", "'EE'"},
      {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
      Tuple tuple(value);
      cout << tuple.toString(scheme) << endl;
      relation.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();

    Relation result = relation.select(2, "'CS'");

    cout << "select Major='CS' result:" << endl;
    cout << result.toString();

  return 0;

}