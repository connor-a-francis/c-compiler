#include "gtest/gtest.h"
#include <cassert>
#include <gtest/gtest.h>
#include "compiler/parser.h"
#include "compiler/token.h"
#include "compiler/ast.h"
#include "../src/ast_printer.cpp"
#include <vector>

using enum TokenType;

typedef std::vector<Token> tokenStream;
typedef std::vector<std::shared_ptr<Expr>> program;

void test(tokenStream input, program expected);

TEST(ParserTest, ParserBuilds)
{
    Parser result({{END_OF_FILE, 0, 0, 1}});
}
TEST(ParserTest, ParserReadsDef)
{
// def hello() {}
  test(
    
       {Token(DEF, 0, 0, 3), Token(IDENTIFIER, 0, 4, 5, std::string("hello")),
        Token(L_PAREN, 0, 9, 1), Token(R_PAREN, 0, 10, 1),
        Token(L_BRACE, 0, 12, 1), Token(R_BRACE, 0, 13, 1),
        Token(END_OF_FILE, 0, 14, 1)},
       {std::make_shared<Definition>(Definition(std::make_shared<Token>(TokenType::IDENTIFIER, 0, 4, 5, string("hello")), {}, {}))}
       );
}

TEST(ParserTest, ParserReadsExtern) {
    // extern hello;
  test(
       {Token(EXTERN, 0, 0, 6),
        Token(IDENTIFIER, 0, 7, 5, std::string("hello")), Token(EOL, 0, 12, 1),
        Token(END_OF_FILE, 0, 13, 1)},
       {std::make_shared<Extern>(Extern(std::make_shared<Token>(TokenType::IDENTIFIER, 0, 7, 5, string("hello"))))});
        
}
void test(tokenStream input, program expected) {
  std::ostringstream input_string;
  std::ostringstream expected_string;
  AstPrinter(input_string).print(Parser(input).parseProgram()), AstPrinter(expected_string).print(expected);
  cout << expected_string.str() << std::endl;
  ASSERT_EQ(input_string.str(), expected_string.str());
}


