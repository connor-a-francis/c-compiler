#include "src/ast_printer.cpp"
#include "compiler/ast.h"
#include "compiler/parser.h"
#include "compiler/token.h"
#include "gtest/gtest.h"
#include <cassert>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

TEST(ParserTest, ParserBuilds) { 
  AstPrinter printer(std::cout);
  std::vector<std::shared_ptr<Expr>> exprs {
    std::make_shared<Definition>(
      std::make_shared<Token>(TokenType::IDENTIFIER, std::string("hello")),
      std::make_shared<Token>(TokenType::IDENTIFIER, std::string("a")),
      std::vector<std::shared_ptr<Expr>>{
        std::make_shared<Assignment>(
          std::make_shared<Token>(TokenType::IDENTIFIER, std::string("a")),
          std::make_shared<Binary>(
            std::make_shared<Token>(TokenType::ADD),
            std::make_shared<Variable>(
              std::make_shared<Token>(TokenType::IDENTIFIER, std::string("b"))),
            std::make_shared<Variable>(
              std::make_shared<Token>(TokenType::NUMBER, float(4.0)))))
      }
    )
  };
  printer.print(exprs);
  ASSERT_EQ(false, true);


}
