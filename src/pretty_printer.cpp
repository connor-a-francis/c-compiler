#include "compiler/ast.h"
#include <string>

class AstPrinter : public AST::ExprVisitor {
public:
    AST::VisitResult visitExpr(AST::Expr& expr) override {
        return "expr";
    }
    AST::VisitResult visitProgram(AST::Program& expr) override {
        std::string s = "Program(";
        for (auto& e : expr.statements) {
            s += std::get<std::string>(e->accept(*this)) + ", ";
        }
        if (!expr.statements.empty()) s.erase(s.size() - 2); // remove last comma
        s += ")";
        return s;
    }

    AST::VisitResult visitAssignExpr(AST::Assign& expr) override {
        std::string s = "Assign(name: " + std::string(expr.name.name) + ", value: ";
        s += std::get<std::string>(expr.value->accept(*this)) + ")";
        return s;
    }

    AST::VisitResult visitBinaryExpr(AST::Binary& expr) override {
        std::string s = "Binary(left: ";
        s += std::get<std::string>(expr.left->accept(*this)) + ", op: " + expr.op.op + ", right: ";
        s += std::get<std::string>(expr.right->accept(*this)) + ")";
        return s;
    }

    AST::VisitResult visitCallExpr(AST::Call& expr) override {
        std::string s = "Call(callee: " + std::string(expr.callee.name) + ", args: (";
        for (auto& arg : expr.arguments) {
            s += std::get<std::string>(arg->accept(*this)) + ", ";
        }
        if (!expr.arguments.empty()) s.erase(s.size() - 2);
        s += "))";
        return s;
    }

    AST::VisitResult visitGroupingExpr(AST::Grouping& expr) override {
        std::string s = "Grouping(" + std::get<std::string>(expr.expression->accept(*this)) + ")";
        return s;
    }

    AST::VisitResult visitLiteralExpr(AST::Literal& expr) override {
        return std::to_string(expr.value);
    }

    AST::VisitResult visitVariableExpr(AST::Variable& expr) override {
        return "Variable(" + std::string(expr.name.name) + ")";
    }

    AST::VisitResult visitDefinition(AST::Definition& expr) override {
        std::string s = "Definition(name: " + std::string(expr.name.name) + ", rands: (";
        for (auto& r : expr.rands) {
            s += std::get<std::string>(r->accept(*this)) + ", ";
        }
        if (!expr.rands.empty()) s.erase(s.size() - 2);
        s += "), impl: ";
        s += std::get<std::string>(expr.impl->accept(*this)) + ")";
        return s;
    }
};

