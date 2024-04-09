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
#include "Graph.h"

// int main(int argc, char* argv[]) {
//     std::string input = argv[1];
//     std::ifstream file(input);

//     if (!file.is_open()) {
//         std::cout << "File not found" << std::endl;
//         return 1;
//     }
    
//     std::stringstream fileContents;
//     fileContents << file.rdbuf();

//     file.close();

//     Scanner s = Scanner(fileContents.str());
//     s.scanTokens();
//     std::vector<Token> tokens = s.getTokens();

//     Parser p = Parser(tokens);
//     p.parse();

//     DatalogProgram dp = p.getDatalogProgram();
//     // std::cout << p.getDatalogProgram().toString();

//     Interpreter i = Interpreter(dp);
//     i.createDatabase();
//     i.interpretQueries();

//   return 0;

// }
int main(int argc, char* argv[]) {


  pair<string,vector<string>> ruleNames[] = {
    { "A", { "B", "C" } },
    { "B", { "A", "D" } },
    { "B", { "B" } },
    { "E", { "F", "G" } },
    { "E", { "E", "F" } },
  };

  vector<Rule> rules;

  for (auto& rulePair : ruleNames) {
    string headName = rulePair.first;
    Rule rule = Rule(Predicate(headName));
    vector<string> bodyNames = rulePair.second;
    for (auto& bodyName : bodyNames)
      rule.addBodyPredicate(Predicate(bodyName));
    rules.push_back(rule);
  }

  vector<Graph> graphs = Interpreter::makeGraphs(rules);
  Graph forwardGraph = graphs[0];
  cout << forwardGraph.toString();

  return 0;

}