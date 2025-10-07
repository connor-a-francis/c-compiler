#include "../src/ast_printer.cpp"
#include "compiler/ast.h"
#include "compiler/parser.h"
#include "compiler/token.h"
#include "gtest/gtest.h"
#include <cassert>
#include <gtest/gtest.h>
#include <vector>

using enum TokenType;

typedef std::vector<Token> tokenStream;
typedef std::vector<std::shared_ptr<Expr>> program;

void test(tokenStream input, program expected);

TEST(ParserTest, ParserBuilds) { Parser result({{END_OF_FILE, 0, 0, 1}}); }
TEST(ParserTest, ParserReadsDef) {
  // def hello() {}
  test(

      {Token(DEF, 0, 0, 3), Token(IDENTIFIER, 0, 4, 5, std::string("hello")),
       Token(L_PAREN, 0, 9, 1), Token(R_PAREN, 0, 10, 1),
       Token(L_BRACE, 0, 12, 1), Token(R_BRACE, 0, 13, 1),
       Token(END_OF_FILE, 0, 14, 1)},
      {std::make_shared<Definition>(
          Definition(std::make_shared<Token>(TokenType::IDENTIFIER, 0, 4, 5,
                                             string("hello")),
                     {}, {}))});
}

TEST(ParserTest, ParserReadsExtern) {
  // extern hello;
  test({Token(EXTERN, 0, 0, 6),
        Token(IDENTIFIER, 0, 7, 5, std::string("hello")), Token(EOL, 0, 12, 1),
        Token(END_OF_FILE, 0, 13, 1)},
       {std::make_shared<Extern>(Extern(std::make_shared<Token>(
           TokenType::IDENTIFIER, 0, 7, 5, string("hello"))))});
}

TEST(ParserTest, ParserReadsDefAndExtern) {
  // extern hello;
  // def goodbye() {}
  test({Token(EXTERN, 0, 0, 6),

        Token(IDENTIFIER, 0, 7, 5, std::string("hello")), Token(EOL, 0, 12, 1),
        Token(DEF, 1, 0, 3), Token(IDENTIFIER, 1, 4, 7, std::string("goodbye")),
        Token(L_PAREN, 1, 11, 1), Token(R_PAREN, 1, 12, 1),
        Token(L_BRACE, 1, 14, 1), Token(R_BRACE, 1, 15, 1),
        Token(END_OF_FILE, 1, 16, 1)},
       {std::make_shared<Extern>(Extern(std::make_shared<Token>(
            TokenType::IDENTIFIER, 0, 7, 5, string("hello")))),
        std::make_shared<Definition>(
            Definition(std::make_shared<Token>(TokenType::IDENTIFIER, 1, 4, 7,
                                               string("goodbye")),
                       {}, {}))});
}

TEST(ParserTest, ParserReadsMath) {

  // let a=(b+c)-d*e/(f+g);

  test({Token(LET, 0, 0, 3),
        Token(IDENTIFIER, 0, 4, 1, std::string("a")),
        Token(EQ, 0, 5, 1),
        Token(L_PAREN, 0, 6, 1),
        Token(IDENTIFIER, 0, 7, 1, std::string("b")),
        Token(ADD, 0, 8, 1),
        Token(IDENTIFIER, 0, 9, 1, std::string("c")),
        Token(R_PAREN, 0, 10, 1),
        Token(SUB, 0, 11, 1),
        Token(IDENTIFIER, 0, 12, 1, std::string("d")),
        Token(MUL, 0, 13, 1),
        Token(IDENTIFIER, 0, 14, 1, std::string("e")),
        Token(DIV, 0, 15, 1),
        Token(L_PAREN, 0, 16, 1),
        Token(IDENTIFIER, 0, 17, 1, std::string("f")),
        Token(ADD, 0, 18, 1),
        Token(IDENTIFIER, 0, 19, 1, std::string("g")),
        Token(R_PAREN, 0, 20, 1),
        Token(EOL, 0, 21, 1),
        Token(END_OF_FILE, 0, 22, 1)},

       {

           std::make_shared<Assignment>(std::make_shared<Variable>(
               IDENTIFIER, 0, 4, 1, std::string("a"),

               std::make_shared<Binary>(

                   std::make_shared<Token>(SUB, 0, 5, 1),

                   std::make_shared<Grouping>(std::make_shared<Binary>(
                       std::make_shared<Token>(ADD, 0, 8, 1),
                       std::make_shared<Variable>(IDENTIFIER, 0, 7, 1,
                                                  std::string("b")),
                       std::make_shared<Variable>(IDENTIFIER, 0, 9, 1,
                                                  std::string("c")))),

                   std::make_shared<Binary>(

                       std::make_shared<Token>(DIV, 0, 15, 1),

                       std::make_shared<Binary>(
                           std::make_shared<Token>(MUL, 0, 13, 1),
                           std::make_shared<Variable>(0, 12, 1,
                                                      std::string("d")),
                           std::make_shared<Variable>(IDENTIFIER, 0, 14, 1,
                                                      std::string("e"))),

                       std::make_shared<Grouping>(std::make_shared<Binary>(
                           std::make_shared<Token>(ADD, 0, 18, 1),
                           std::make_shared<Variable>(IDENTIFIER, 0, 17, 1,
                                                      std::string("f")),
                           std::make_shared<Variable>(IDENTIFIER, 0, 19, 1,
                                                      std::string("g"))))

                           ))))

       }

  );
}

void test(tokenStream input, program expected) {
  std::ostringstream input_string;
  std::ostringstream expected_string;
  AstPrinter(input_string).print(Parser(input).parseProgram()),
      AstPrinter(expected_string).print(expected);
  cout << expected_string.str() << std::endl;
  ASSERT_EQ(input_string.str(), expected_string.str());
}
