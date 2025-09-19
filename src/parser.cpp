#include "compiler/parser.h"
#include "compiler/ast.h"
#include "compiler/token.h"
#include <algorithm>
#include <vector>

AST::Program Parser::parseProgram() {
  while (!isAtEnd()) {
    auto stmt = parseStatement();
    this->statements.push_back(std::unique_ptr<AST::Expr>());
  }
  return AST::Program(std::move(this->statements));
}
AST::Expr Parser::parseExpression() { return AST::Expr{}; }

// class Assign;
// class Binary;
// class Call;
// class Grouping;
// class Literal;
// class Variable;
//
AST::Expr Parser::parseStatement() {
  if (match<Let, Identifier>()) {
    return parseBinding();
  }
  if (match<Def>()) {
    return parseDefinition();
  }
  if (match<Extern>()) {
    return parseExtern();
  }
  if (match<Return>()) {
    return parseReturn();
  }
  throw new std::runtime_error("Incorrect Statement");
}
AST::Expr Parser::parseDefinition() {
  Identifier name;
  if (match<Identifier>()) {
    name = std::get<Identifier>(previous());
  }
  match<LParen>();
  match<RParen>();
  match<LBrace>();
  match<RBrace>();

  return AST::Definition{name, {}, std::unique_ptr<AST::Program>()};
}
AST::Expr Parser::parseBinding() { return AST::Expr{}; }
AST::Expr Parser::parseExtern() { return AST::Expr{}; }
AST::Expr Parser::parseReturn() { return AST::Expr{}; }
AST::Expr Parser::parseCall() { return AST::Expr{}; }
AST::Expr Parser::parseBinaryExpr() { return AST::Expr{}; }
AST::Expr Parser::parseGrouping() { return AST::Expr{}; }
AST::Expr Parser::parseRands() { return AST::Expr{}; }
AST::Expr Parser::parseRand() { return AST::Expr{}; }
AST::Expr Parser::parseOperator() { return AST::Expr{}; }

Token Parser::moveReadHead() {
  if (!isAtEnd())
    current++;
  return previous();
}
bool Parser::isAtEnd() { return check<EndOfFile>(); }
Token Parser::peek() { return this->tokens[this->current]; }
Token Parser::previous() { return this->tokens[this->current - 1]; }
