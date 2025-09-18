#include "compiler/parser.h"
#include "compiler/ast.h"
#include "compiler/token.h"
#include <type_traits>
#include <variant>
#include <vector>

AST::Expr Parser::parseProgram() { 

  return Expr{};

}
AST::Expr Parser::parseExpression() { 
  return Expr{};
}


// class Assign;
// class Binary;
// class Call;
// class Grouping;
// class Literal;
// class Variable;
//
AST::Expr Parser::parseStatement() { return Expr{}; }
AST::Expr Parser::parseDefinition() { return Expr{}; }
AST::Expr Parser::parseBinding() { return Expr{}; }
AST::Expr Parser::parseExtern() { return Expr{}; }
AST::Expr Parser::parseReturn() { return Expr{}; }
AST::Expr Parser::parseCall() { return Expr{}; }
AST::Expr Parser::parseBinaryExpr() { return Expr{}; }
AST::Expr Parser::parseGrouping() { return Expr{}; }
AST::Expr Parser::parseRands() { return Expr{}; }
AST::Expr Parser::parseRand() { return Expr{}; }
AST::Expr Parser::parseOperator() { return Expr{}; }

bool Parser::match(std::initializer_list<Token> types) {
    for (auto type : types) {
        if (check(type)) {
            moveReadHead();
            return true;
        }
    }
    return false;
}
Token Parser::moveReadHead() {
    if (!isAtEnd()) current++;
    return previous();
  }

bool Parser::isAtEnd() {
    return std::holds_alternative<EndOfFile>(peek());
  }

Token Parser::peek() {
    return this->tokens[this->current];
  }
bool Parser::check(Token type) {
    return std::is_same<decltype(peek()), decltype(type)>::value;
  }

Token Parser::previous() {
    return this->tokens[this->current - 1];
  }
