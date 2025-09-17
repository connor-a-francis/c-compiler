#ifndef AST
#define AST

#include <vector>
#include <memory>
#include "token.h"
namespace AST {

class Assign;
class Binary;
class Call;
class Grouping;
class Literal;
class Variable;

template <typename R>
class ExprVisitor {
public:
    virtual R visitAssignExpr(Assign& expr) = 0;
    virtual R visitBinaryExpr(Binary& expr) = 0;
    virtual R visitCallExpr(Call& expr) = 0;
    virtual R visitGroupingExpr(Grouping& expr) = 0;
    virtual R visitLiteralExpr(Literal& expr) = 0;
    virtual R visitVariableExpr(Variable& expr) = 0;
    virtual ~ExprVisitor() = default;
};

class Expr {
public:
    template <typename R>
    R accept(ExprVisitor<R>& visitor) {
        return _accept(visitor);
    }
    template <typename R>
    R _accept(ExprVisitor<R>& visitor) {
        return _accept(&visitor);
    }

    virtual ~Expr() = default;
};

class Assign : public Expr {
public:
    Token name;
    std::unique_ptr<Expr> value;

    Assign(Token name, std::unique_ptr<Expr> value)
        : name(std::move(name)), value(std::move(value)) {}

    template <typename R>
    R _accept(ExprVisitor<R>& visitor) {
        return visitor.visitAssignExpr(*this);
    }
};

class Binary : public Expr {
public:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

    template <typename R>
    R _accept(ExprVisitor<R>& visitor) {
        return visitor.visitBinaryExpr(*this);
    }
};

class Call : public Expr {
public:
    std::unique_ptr<Expr> callee;
    Token closing_paren;
    std::vector<std::unique_ptr<Expr>> arguments;

    Call(std::unique_ptr<Expr> callee, Token paren, std::vector<std::unique_ptr<Expr>> arguments)
        : callee(std::move(callee)), closing_paren(std::move(paren)), arguments(std::move(arguments)) {}

    template <typename R>
    R _accept(ExprVisitor<R>& visitor) {
        return visitor.visitCallExpr(*this);
    }
};


class Grouping : public Expr {
public:
    std::unique_ptr<Expr> expression;

    Grouping(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    template <typename R>
    R _accept(ExprVisitor<R>& visitor) {
        return visitor.visitGroupingExpr(*this);
    }
};

class Literal : public Expr {
public:
    int value; 

    Literal(int value) : value(std::move(value)) {}

    template <typename R>
    R _accept(ExprVisitor<R>& visitor) {
        return visitor.visitLiteralExpr(*this);
    }
};

class Variable : public Expr {
public:
    Token name;

    Variable(Token name) : name(std::move(name)) {}

    template <typename R>
    R _accept(ExprVisitor<R>& visitor) {
        return visitor.visitVariableExpr(*this);
    }
};

}
#endif 
