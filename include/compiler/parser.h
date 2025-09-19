#pragma once

#include "token.h"
#include "ast.h"
#include <vector>

class Parser {
public:
    Parser(std::vector<Token> token_input){
        current = 0;
        tokens = token_input;
        statements.clear();
        tokens.reserve(100000);
        statements.reserve(100000);
    }
    AST::Program parseProgram();

private:
    int current;
    std::vector<std::unique_ptr<AST::Expr>> statements;
    std::vector<Token> tokens;
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
    template <typename... Ts>
    bool match() {
        if ((check<Ts>() || ...)) {  // fold expression
            moveReadHead();
            return true;
        }
        return false;
    }
    template <typename T>
    bool check() {
        return std::holds_alternative<T>(peek());
    }
    bool checkPrevious(Token type);
};
