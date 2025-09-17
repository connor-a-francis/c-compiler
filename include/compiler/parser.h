#pragma once

#include "token.h"
#include "ast.h"
#include <vector>

class Parser {
public:
    Parser(std::vector<Token> token_input){
        current = 0;
        std::vector<Token> tokens = token_input;
        tokens.reserve(100000);
    }

private:
    int current;
    std::vector<Token> tokens;
    AST::Expr expression();
    AST::Expr assign();
    AST::Expr binary();
    AST::Expr call();
    AST::Expr grouping();
    AST::Expr literal();
    AST::Expr variable();
    
};

