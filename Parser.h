#include <vector>
#include "Token.h"
#include <iostream>
#include <string>
#include "DatalogProgram.h"
#include "Predicate.h"

class Parser {
    private:
        std::vector<Token> tokens;
        DatalogProgram dp;
        Token previousToken = Token(UNDEFINED, "", 0);
       
    public:

        void parse() {
            datalogProgram();
            if (tokens.size() != 0) {
                throwError();
            } 
        }

        DatalogProgram getDatalogProgram() {
            return dp;
        }

    // HELPER FUNCTIONS 

        TokenType tokenType() const {
            return tokens.at(0).getType();
        }

        std::string tokenName() const {
            return tokens.at(0).typeName(tokens.at(0).getType());
        }
        
        std::string tokenLine() const {
            std::string line = std::to_string(tokens.at(0).getLineNumber());
            return line;
        }

        void advanceToken() {
            previousToken = tokens.at(0);
            tokens.erase(tokens.begin());
        }

        void throwError() {
            std::cout << "Failure!" << std::endl;
            std::cout << "  " << "(" << tokenName() << "," << "\"" << tokens.at(0).getValue() << "\"," << tokenLine() << ")" << std::endl;
            exit(1);}

        Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

        void match(TokenType t) {
            if (tokens.at(0).getType() == t) {
                advanceToken();
            } else {
                throwError();
            }
        }

        // Grammar Rules 

        void datalogProgram() {
            if (tokenType() == SCHEMES) {
                match(SCHEMES);
                match(COLON);
                scheme();
                schemeList();
                match(FACTS);   
                match(COLON);
                factList();
                match(RULES);
                match(COLON);
                ruleList();
                match(QUERIES);
                match(COLON);
                query();
                queryList();
                match(END_F);
            } else {
                throwError();
            }
        }

        void fact() {
            if (tokenType() == ID) {
                match(ID);
                Predicate p = Predicate(previousToken.getValue());
                match(LEFT_PAREN);
                match(STRING);
                p.addParameter(Parameter(previousToken.getValue()));
                stringList(p);
                match(RIGHT_PAREN);
                match(PERIOD);
                dp.addFact(p);
            } else {
                throwError();
            }
        }

        void factList() {
            if (tokenType() == ID) {
                fact();
                factList();
            } else {
                return;
            }
        }

        Predicate headPredicate() {
            Predicate p = Predicate("");
            if(tokenType() == ID) {
                match(ID);
                p.setId(previousToken.getValue());
                match(LEFT_PAREN);
                match(ID);
                p.addParameter(Parameter(previousToken.getValue()));
                idList(p);
                match(RIGHT_PAREN);
            } else {
                throwError();
            }
            return p;
        }

        void idList(Predicate& p) {
            if (tokenType() == COMMA) {
                match(COMMA);   
                match(ID);
                p.addParameter(Parameter(previousToken.getValue()));
                idList(p);
            } else {
                return;
            }
        }

        void parameter(Predicate& p) {
            if (tokenType() == STRING) {
                match(STRING);
            } else if (tokenType() == ID) {
                match(ID);
            } else {
                throwError();
            }
            p.addParameter(Parameter(previousToken.getValue()));

        }

        void parameterList(Predicate& p) {
            if (tokenType() == COMMA) {
                match(COMMA);
                parameter(p);
                parameterList(p);
            } else {
                return;
            }
        }

        Predicate predicate() {
            Predicate p = Predicate("");
            if (tokenType() == ID) {
                match(ID);
                p.setId(previousToken.getValue());
                match(LEFT_PAREN);
                parameter(p);
                parameterList(p);
                match(RIGHT_PAREN);
            } else {
                throwError();
            }
            return p;
        
        }

        void predicateList(Rule& r) {
            if (tokenType() == COMMA) {
                match(COMMA);
                r.addBodyPredicate(predicate());
                predicateList(r);
            } else {
                return;
            }
        }

 
        void query() {
            Predicate p = predicate();
            if (tokenType() == Q_MARK) {
                match(Q_MARK);
                dp.addQuery(p);
            } else {
                throwError();
            }
        }

        void queryList() {
            if (tokenType() == ID) {
                query();
                queryList();
            } else {
                return;
            }
        }

        void rule() {
            Rule r = Rule(headPredicate());

            if (tokenType() == COLON_DASH) {
                match(COLON_DASH);
                r.addBodyPredicate(predicate());
                predicateList(r);
                match(PERIOD);
                dp.addRule(r);
            } else {
                throwError();
            }
        }

        void ruleList() {
            if (tokenType() == ID) {
                rule();
                ruleList();
            } else {
                return;
            }
        }
        
       void scheme() {
            if (tokenType() == ID) {
                match(ID);
                Predicate p = Predicate(previousToken.getValue());
                match(LEFT_PAREN);
                match(ID);
                p.addParameter(Parameter(previousToken.getValue()));
                idList(p);
                match(RIGHT_PAREN);
                dp.addScheme(p);
            } else {
                throwError();
            }
        }

        void schemeList(){
            if (tokenType() == ID) {
                scheme();
                schemeList();
            } else {
                return;
            }
        }

        void stringList(Predicate& p) {
            if (tokenType() == COMMA) {
                match(COMMA);
                match(STRING);
                p.addParameter(Parameter(previousToken.getValue()));
                stringList(p);
            } else {
                return;
            }
        }


};