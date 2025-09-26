#include "compiler/ast.h"
#include "compiler/visitor.h"

#include <utility>

void Literal::accept(Visitor *v) {
    v->visit_Literal(static_pointer_cast<Literal>(shared_from_this()));
}

Literal::Literal(std::shared_ptr<Token> t) : tok(std::move(t))
{

}

void Assignment::accept(Visitor *v) {
    v->visit_Assignment(static_pointer_cast<Assignment>(shared_from_this()));
}

Assignment::Assignment(std::shared_ptr<Token> name, std::shared_ptr<Expr> expr) : name(std::move(name)), expr(std::move(expr))
{

}

void Definition::accept(Visitor *v) {
    v->visit_Definition(static_pointer_cast<Definition>(shared_from_this()));
}

Definition::Definition(std::shared_ptr<Token> name, std::vector<std::shared_ptr<Token>> rands, std::vector<std::shared_ptr<Expr>> body) : name(std::move(name)), rands(std::move(rands)), body(std::move(body))
{

}
void Call::accept(Visitor *v) {
    v->visit_Call(static_pointer_cast<Call>(shared_from_this()));
}

Call::Call(std::shared_ptr<Expr> callee, std::shared_ptr<Token> paren, std::shared_ptr<std::vector<std::shared_ptr<Expr>>> arguments) : callee(std::move(callee)), paren(std::move(paren)), arguments(std::move(arguments))
{

}

void Binary::accept(Visitor *v) {
    v->visit_Binary(static_pointer_cast<Binary>(shared_from_this()));
}

Binary::Binary(std::shared_ptr<Token> op, std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : op(std::move(op)), lhs(std::move(lhs)), rhs(std::move(rhs))
{

}

void Grouping::accept(Visitor *v) {
    v->visit_Grouping(static_pointer_cast<Grouping>(shared_from_this()));
}

Grouping::Grouping(std::shared_ptr<Expr> exp) : exp(std::move(exp))
{

}

void Variable::accept(Visitor *v) {
    v->visit_Variable(static_pointer_cast<Variable>(shared_from_this()));
}

Variable::Variable(std::shared_ptr<Token> t) : name(std::move(t))
{

}
