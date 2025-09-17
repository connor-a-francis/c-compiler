#include "compiler/ast.h"

class AstPrinter : public AST::ExprVisitor<std::string> {
  std::string print(AST::Expr exp) { return exp.accept(*this); }
  std::string visitAssignExpr(Assign &expr) {
    return "assign";
  }
  std::string visitBinaryExpr(Binary &expr) {
    return "binary";
  }
  std::string visitCallExpr(Call &expr) {
    return "call";
  }
  std::string visitGroupingExpr(Grouping &expr) {
    return "grouping";
  }
  std::string visitLiteralExpr(Literal &expr) {
    return "literal";
  }
  std::string visitVariableExpr(Variable &expr) {
    return "variable";
  }
};
