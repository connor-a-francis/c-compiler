#include "compiler/parser.h"
#include "compiler/token_type.h"
#include "compiler/parse_error.h"
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Expr>> Parser::parseProgram() {
    while(!isAtEnd() && !check(TokenType::R_BRACE)) {
            statements.push_back(parseStatement());
    }

    return statements;

}

// int current;
// std::vector<std::shared_ptr<Expr>> statements;
// std::vector<Token> tokens;

std::shared_ptr<Expr> Parser::parseStatement() {
    try {
    if (match({TokenType::DEF})) {
        return parseDefinition();
    }
    if (match({TokenType::LET, TokenType::IDENTIFIER})) {
        return parseBinding();
    }
    if (match({TokenType::EXTERN})) {
        return parseExtern();
    }
    if (match({TokenType::RETURN})) {
        return parseReturn();
    }
    return std::shared_ptr<Expr>();
    } catch (parse_error e) {
        throw e;
    }
}

// <expression> ::= <LITERAL> | <binaryExpr> | <IDENTIFIER> | <call> | <grouping>
std::shared_ptr<Expr> Parser::parseExpression() {
    return std::shared_ptr<Expr>();
}

// <definition> ::= DEF <IDENTIFIER> LP <params> RP LB <program> RB
std::shared_ptr<Expr> Parser::parseDefinition() {
    if (!match({TokenType::IDENTIFIER})) {
        throw parse_error(previous(), "missing function name");
    }

    auto name = previous();
    auto params = parseParams();

    if (!match({TokenType::L_PAREN})) {
        throw parse_error(previous(), "missing opening parenthesis");
    }
    if (!match({TokenType::R_PAREN})) {
        throw parse_error(previous(), "missing closing parenthesis");
    }
    if (!match({TokenType::L_BRACE})) {
        throw parse_error(previous(), "missing opening brace");
    }

    auto body = parseProgram();

    if (!match({TokenType::R_BRACE})) {
        throw parse_error(previous(), "missing closing brace");
    }
    return std::make_shared<Definition>(std::make_shared<Token>(name), params, body);
}

std::shared_ptr<Expr> Parser::parseBinding() {
// <binding> ::= LET <IDENTIFIER> EQ <expression> EOL
    return std::shared_ptr<Expr>();
}

std::shared_ptr<Expr> Parser::parseExtern() {
// <extern> ::= EXTERN <expression> EOL
 if (!match({TokenType::IDENTIFIER})) {
        throw parse_error(peek(), "missing function name");
    }

    auto name = previous();

    if (!match({TokenType::EOL})) {
        throw parse_error(peek(), "unexpected token after extern");
    }

    return std::make_shared<Extern>(std::make_shared<Token>(name));
}

std::shared_ptr<Expr> Parser::parseReturn() {
// <return> ::= RETURN <expression> EOL
    return std::shared_ptr<Expr>();
}

std::shared_ptr<Expr> Parser::parseCall() {
// <call> ::= <IDENTIFIER> LP <rands> RP
    return std::shared_ptr<Expr>();
}

std::shared_ptr<Expr> Parser::parseBinaryExpr() {
// <binaryExpr> ::= <expression> <operator> <expression>
    return std::shared_ptr<Expr>();
}

std::shared_ptr<Expr> Parser::parseGrouping() {
// <grouping> ::= LP <expression> RP
    return std::shared_ptr<Expr>();
}

std::vector<shared_ptr<Expr>> Parser::parseRands() {
// <rands> ::= <expression> <rand>*
    return {std::shared_ptr<Expr>()};
}


std::vector<shared_ptr<Token>> Parser::parseParams() {
    std::vector<shared_ptr<Token>> params;
    if (!match({TokenType::IDENTIFIER})) {
        return params;
    }
    while (match({TokenType::COMMA})) {
        if (!match({TokenType::IDENTIFIER})) { 
            throw parse_error(previous(), "identifier expected");
        }
        params.push_back(std::make_shared<Token>(previous()));
    }
    return params;
}

std::shared_ptr<Expr> Parser::parseOperator() {
// <operator> ::= ADD | MIN | MUL | DIV
    return std::shared_ptr<Expr>();
}

Token Parser::moveReadHead() {
  if (!isAtEnd())
    current++;
  return previous();
}
bool Parser::isAtEnd() { return peek().type == TokenType::END_OF_FILE; }
Token Parser::peek() { return tokens[current]; }
Token Parser::previous() { return tokens[current - 1]; }
bool Parser::match(std::vector<TokenType> types) {
  for (auto &type : types) {
    if (check(type)) {
      moveReadHead();
      return true;
    }
  }
  return false;
}
bool Parser::check(TokenType type) { return peek().type == type; }
bool Parser::checkPrevious(TokenType type) { return previous().type == type; }

void Parser::handle_error(parse_error e) {
    throw parse_error(e);
}

