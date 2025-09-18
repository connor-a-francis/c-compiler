#pragma once

#include "token.h"
#include "ast.h"
#include <vector>

class Parser {
public:
    Parser(std::vector<Token> token_input){
        current = 0;
        std::vector<Token> tokens = token_input;
        std::vector<Expr> statements;
        tokens.reserve(100000);
        statements.reserve(100000);
    }

private:
    int current;
    std::vector<Expr> statements;
    std::vector<Token> tokens;
    AST::Expr parseProgram();
    AST::Expr parseExpression();

    AST::Expr parseStatement();
    AST::Expr parseDefinition();
    AST::Expr parseBinding();
    AST::Expr parseExtern();
    AST::Expr parseReturn();
    AST::Expr parseCall();
    AST::Expr parseBinaryExpr();
    AST::Expr parseGrouping();
    AST::Expr parseRands();
    AST::Expr parseRand();
    AST::Expr parseOperator();
    Token moveReadHead();
    bool isAtEnd();
    Token peek();
    Token previous();
    bool match(std::initializer_list<Token> types);
    bool check(Token type);
};
