#pragma once
#include <memory>
#include <string>
#include <vector>
#include <variant>
#include "token.h"

namespace AST {

// Allowed return types for visitors
using VisitResult = std::variant<std::string, int, double>;

// Forward declarations
class Assign;
class Binary;
class Call;
class Grouping;
class Literal;
class Variable;
class Definition;
class Program;
class Expr;

// Visitor interface
class ExprVisitor {
public:
    virtual VisitResult visitAssignExpr(Assign& expr) = 0;
    virtual VisitResult visitBinaryExpr(Binary& expr) = 0;
    virtual VisitResult visitCallExpr(Call& expr) = 0;
    virtual VisitResult visitGroupingExpr(Grouping& expr) = 0;
    virtual VisitResult visitLiteralExpr(Literal& expr) = 0;
    virtual VisitResult visitVariableExpr(Variable& expr) = 0;
    virtual VisitResult visitDefinition(Definition& expr) = 0;
    virtual VisitResult visitProgram(Program& expr) = 0;
    virtual VisitResult visitExpr(Expr& expr) = 0;
    virtual ~ExprVisitor() = default;
};

// Base AST node
class Expr {
public:
    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitExpr(*this);
    }
};

// Program node
class Program : public Expr {
public:
    std::vector<std::unique_ptr<Expr>> statements;

    explicit Program(std::vector<std::unique_ptr<Expr>> stmts)
        : statements(std::move(stmts)) {}

    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitProgram(*this);
    }
};

// Assign node
class Assign : public Expr {
public:
    Identifier name;
    std::unique_ptr<Expr> value;

    Assign(Identifier n, std::unique_ptr<Expr> v)
        : name(std::move(n)), value(std::move(v)) {}

    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitAssignExpr(*this);
    }
};

// Binary node
class Binary : public Expr {
public:
    std::unique_ptr<Expr> left;
    Op op;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> l, Op o, std::unique_ptr<Expr> r)
        : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}

    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitBinaryExpr(*this);
    }
};

// Call node
class Call : public Expr {
public:
    Identifier callee;
    Token closing_paren;
    std::vector<std::unique_ptr<Expr>> arguments;

    Call(Identifier c, Token paren, std::vector<std::unique_ptr<Expr>> args)
        : callee(std::move(c)), closing_paren(std::move(paren)), arguments(std::move(args)) {}

    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitCallExpr(*this);
    }
};

// Grouping node
class Grouping : public Expr {
public:
    std::unique_ptr<Expr> expression;

    explicit Grouping(std::unique_ptr<Expr> expr)
        : expression(std::move(expr)) {}

    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitGroupingExpr(*this);
    }
};

// Literal node
class Literal : public Expr {
public:
    int value;

    explicit Literal(int val) : value(val) {}

    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitLiteralExpr(*this);
    }
};

// Variable node
class Variable : public Expr {
public:
    Identifier name;

    explicit Variable(Identifier n) : name(std::move(n)) {}

    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitVariableExpr(*this);
    }
};

// Definition node
class Definition : public Expr {
public:
    Identifier name;
    std::vector<std::unique_ptr<Expr>> rands;
    std::unique_ptr<Program> impl;

    Definition(Identifier n, std::vector<std::unique_ptr<Expr>> r, std::unique_ptr<Program> i)
        : name(std::move(n)), rands(std::move(r)), impl(std::move(i)) {}

    VisitResult accept(ExprVisitor& visitor) {
        return visitor.visitDefinition(*this);
    }
};

} // namespace AST

