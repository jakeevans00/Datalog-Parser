#include <string>
#include <stack>
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

    Interpreter i = Interpreter(dp);
    i.createDatabase();
    
    vector<Graph> graphs = Interpreter::makeGraphs(dp.getRules());
    Graph forwardGraph = graphs[0];
    Graph reverseGraph = graphs[1];
    cout << "Dependency Graph\n";
    cout << forwardGraph.toString() << endl;

    // cout << "Reverse Graph\n";
    // cout << reverseGraph.toString() << endl;

    stack<int> postOrder = reverseGraph.dfsForest();
    // cout << "Postorder Numbers\n";

    vector<vector<int>> sccs = forwardGraph.dfsForest(postOrder);

    i.evaluateRules(sccs);
    i.interpretQueries();

  return 0;
}
