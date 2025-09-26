#pragma once

#include "parse_error.h"
#include "token.h"
#include "token_type.h"
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
    std::vector<std::shared_ptr<Expr>> parseProgram();

private:
    int current;
    std::vector<std::shared_ptr<Expr>> statements;
    std::vector<Token> tokens;

    std::shared_ptr<Expr> parseExpression();
    std::shared_ptr<Expr> parseStatement();
    std::shared_ptr<Expr> parseDefinition();
    std::shared_ptr<Expr> parseBinding();
    std::shared_ptr<Expr> parseExtern();
    std::shared_ptr<Expr> parseReturn();
    std::shared_ptr<Expr> parseCall();
    std::shared_ptr<Expr> parseBinaryExpr();
    std::shared_ptr<Expr> parseGrouping();
    std::vector<std::shared_ptr<Expr>> parseRands();
    std::vector<std::shared_ptr<Token>> parseParams();
    std::shared_ptr<Expr> parseOperator();
    Token moveReadHead();
    bool isAtEnd();
    Token peek();
    Token previous();
    bool match(std::vector<TokenType> types);
    void handle_error(parse_error e);
    bool check(TokenType type);
    bool checkPrevious(TokenType type);
};

