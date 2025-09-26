#pragma once
#include <string>
#include <any>
#include "token_type.h"

class Token {
public:
    Token() = default;
    Token(TokenType type): type(std::move(type)) {}
    Token(TokenType type, std::any literal): type(std::move(type)), literal(std::move(literal)) {}
    std::string toString() const;
    std::string literalToString() const;
    std::string typeToString() const;
    TokenType type;
    std::any literal;
};
