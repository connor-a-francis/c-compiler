// Token.h
#pragma once
#include <variant>
#include <string_view>



struct EndOfFile {};
struct EOL {};
struct Def {};
struct Let {};
struct Extern {};
struct Return {};
struct Eq {};
struct LParen {};
struct RParen {};
struct LBrace {};
struct RBrace {};

struct Op {
    char op;
};

struct Identifier {
    std::string_view name;
};

struct Number {
    float value;
};

struct Misc {
    char val;
};

using Token = std::variant<
    EndOfFile,
    Op,
    EOL,
    Def,
    Let,
    Extern,
    Return,
    Eq,
    LParen,
    RParen,
    LBrace,
    RBrace,
    Identifier,
    Number,
    Misc
>;

template<class... Ts> 
struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts> 
overloaded(Ts...) -> overloaded<Ts...>;
