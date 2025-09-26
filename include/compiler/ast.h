#pragma once

#include <vector>
#include "token.h"
#include "visitor.h"

class AST_Node {
public:
    AST_Node() = default;
    virtual ~ AST_Node() = default;
    virtual void accept(Visitor* v) = 0;
};


class Expr : public AST_Node, public std::enable_shared_from_this<Expr> {
public:
    Expr() = default;
    ~Expr() override = default;
};

class Literal : public Expr {
public:
    std::shared_ptr<Token> tok;
    Literal(std::shared_ptr<Token> t);
    void accept(Visitor* v) override;
};

class Binary : public Expr {
public:
    std::shared_ptr<Token> op;
    std::shared_ptr<Expr> lhs;
    std::shared_ptr<Expr> rhs;
    Binary(std::shared_ptr<Token> op, std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
    void accept(Visitor* v) override;
};

class Grouping : public Expr {
public:
    std::shared_ptr<Expr> exp;
    Grouping(std::shared_ptr<Expr> exp);
    void accept(Visitor* v) override;
};

class Variable : public Expr {
public:
    std::shared_ptr<Token> name;
    Variable(std::shared_ptr<Token> t);
    void accept(Visitor* v) override;
};

class Assignment : public Expr {
public:
    std::shared_ptr<Token> name;
    std::shared_ptr<Expr> expr;
    Assignment(std::shared_ptr<Token> name, std::shared_ptr<Expr> expr);
    void accept(Visitor* v) override;
};

class Definition : public Expr {
public:
    std::shared_ptr<Token> name;
    std::vector<std::shared_ptr<Token>> rands;
    std::vector<std::shared_ptr<Expr>> body;
    Definition(std::shared_ptr<Token> name, std::vector<std::shared_ptr<Token>> rands, std::vector<std::shared_ptr<Expr>> body);
    void accept(Visitor* v) override;
};


class Call : public Expr {
public:
    std::shared_ptr<Expr> callee;
    std::shared_ptr<Token> paren;
    std::shared_ptr<std::vector<std::shared_ptr<Expr>>> arguments;
    Call(std::shared_ptr<Expr> callee, std::shared_ptr<Token> paren, std::shared_ptr<std::vector<std::shared_ptr<Expr>>> arguments);
    void accept(Visitor* v) override;
};

class Stmt : public AST_Node, public std::enable_shared_from_this<Stmt> {
public:
    Stmt() = default;
    ~Stmt() override = default;
};

