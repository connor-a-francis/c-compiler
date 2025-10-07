#pragma once
#include <memory>

class Assignment;
class Binary; 
class Call; 
class Grouping;
class Literal;
class Variable;
class Extern;
class Definition;
class Expr;


class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit_Assignment(std::shared_ptr<Assignment>) = 0;
    virtual void visit_Binary(std::shared_ptr<Binary>) = 0;
    virtual void visit_Call(std::shared_ptr<Call>) = 0;
    virtual void visit_Grouping(std::shared_ptr<Grouping>) = 0;
    virtual void visit_Literal(std::shared_ptr<Literal>) = 0;
    virtual void visit_Variable(std::shared_ptr<Variable>) = 0;
    virtual void visit_Extern(std::shared_ptr<Extern>) = 0;
    virtual void visit_Definition(std::shared_ptr<Definition>) = 0;
};


