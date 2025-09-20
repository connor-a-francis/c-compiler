#include "compiler/ast.h"

#include <utility>

void Literal::accept(Visitor *v) {
    v->visit_Literal(static_pointer_cast<Literal>(shared_from_this()));
}

Literal::Literal(std::shared_ptr<Token> t) : tok(move(t))
{

}

void Assignment::accept(Visitor *v) {
    v->visit_Assignment(static_pointer_cast<Assignment>(shared_from_this()));
}

Assignment::Assignment(std::shared_ptr<Token> name, std::shared_ptr<Expr> expr) : name(move(name)), expr(move(expr))
{

}

void Definition::accept(Visitor *v) {
    v->visit_Definition(static_pointer_cast<Definition>(shared_from_this()));
}

Definition::Definition(std::shared_ptr<Token> name, std::shared_ptr<Token> rands, std::vector<std::shared_ptr<Expr>> body) : name(move(name)), rands({move(rands)}), body(move(body))
{

}
void Call::accept(Visitor *v) {
    v->visit_Call(static_pointer_cast<Call>(shared_from_this()));
}

Call::Call(std::shared_ptr<Expr> callee, std::shared_ptr<Token> paren, std::shared_ptr<std::vector<std::shared_ptr<Expr>>> arguments) : callee(move(callee)), paren(move(paren)), arguments(move(arguments))
{

}

void Binary::accept(Visitor *v) {
    v->visit_Binary(static_pointer_cast<Binary>(shared_from_this()));
}

Binary::Binary(std::shared_ptr<Token> op, std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : op(move(op)), lhs(move(lhs)), rhs(move(rhs))
{

}

void Grouping::accept(Visitor *v) {
    v->visit_Grouping(static_pointer_cast<Grouping>(shared_from_this()));
}

Grouping::Grouping(std::shared_ptr<Expr> exp) : exp(move(exp))
{

}

void Variable::accept(Visitor *v) {
    v->visit_Variable(static_pointer_cast<Variable>(shared_from_this()));
}

Variable::Variable(std::shared_ptr<Token> t) : name(move(t))
{

}