#include "compiler/visitor.h"
#include "compiler/ast.h"
#include <ostream>
#include <iostream>

class AstPrinter : public Visitor {
public:
    std::ostream& out;

    AstPrinter(std::ostream& output_stream) : out(output_stream) {
    }
    ~AstPrinter() override = default;

    void print(std::vector<std::shared_ptr<Expr>> exprs) {
        out << "Program(";
        out << "\r\n";
        for (auto& expr : exprs) {
            expr->accept(this);
            out << "\r\n";
        }
        out << ")";
    }

    void visit_Assignment(std::shared_ptr<Assignment> ptr) override {
        out << "Assign(name: ";
        out << ptr->name->toString();
        out << ", value: ";
        ptr->expr->accept(this);
    }
    void visit_Binary(std::shared_ptr<Binary> ptr) override {
        out << "Binary(left: ";
        ptr->lhs->accept(this);
        out << ", operation:" << ptr->op->toString();
        out << ", right: ";
        ptr->rhs->accept(this);
    }
    void visit_Call(std::shared_ptr<Call> ptr) override {
        out << "Call(callee: ";
        ptr->callee->accept(this);
        out << ", args: (";
        for (auto& arg : *(ptr->arguments)) {
            arg->accept(this);
            if (&arg != &ptr->arguments->back()) {
                out << ", ";
            }
        }
        out << "))";
    }
    void visit_Grouping(std::shared_ptr<Grouping> ptr) override {
        out << "Grouping(callee: ";
        ptr->exp->accept(this);
        out << ")";
    }
    void visit_Literal(std::shared_ptr<Literal> ptr) override {
        out << "Literal(" << ptr->tok->toString() << ")";
    }
    void visit_Variable(std::shared_ptr<Variable> ptr) override {
        out << "Variable(" << ptr->name->toString() << ")";
    }
    void visit_Extern(std::shared_ptr<Extern> ptr) override {
        out << "Extern(" << ptr->name->toString() << ")";
    }
    void visit_Definition(std::shared_ptr<Definition> ptr) override {
        out << "Definition(name: " << ptr->name->toString() << ", operands: (";
        for (auto& r : ptr->rands) {
            out << r->toString();
            if (&r != &ptr->rands.back()) {
                out << ", ";
            }
        }
        out << "), body: (";
        for (auto& b : ptr->body) {
            b->accept(this);
            if (&b != &ptr->body.back()) {
                out << ", ";
            }
        }
        out << "))";
    }

};
