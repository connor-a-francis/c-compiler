#pragma once
#include "token_type.h"
#include <any>
#include <string>

class Token {
public:
  Token() = default;
  Token(TokenType type, int line, int col, int length)
      : type(std::move(type)), line(std::move(line)), length(std::move(length)),
        col(std::move(col)) {}
  Token(TokenType type, int line, int col, int length, std::any literal)
      : type(std::move(type)), line(std::move(line)), length(std::move(length)),
        col(std::move(col)), literal(std::move(literal)) {}
  std::string toString() const;
  std::string literalToString() const;
  std::string typeToString() const;
  TokenType type;
  int line;
  int length;
  int col;
  std::any literal;
};
