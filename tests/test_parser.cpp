// #include "gtest/gtest.h"
// #include <cassert>
// #include <gtest/gtest.h>
// #include "compiler/parser.h"
// #include "compiler/token.h"
// #include "compiler/ast.h"
// #include "../src/ast_printer.cpp"
// #include <vector>
// 
// typedef std::vector<Token> tokenStream;
// typedef std::vector<std::shared_ptr<Expr>> program;
// 
// void test(tokenStream input, program expected);
// 
// TEST(ParserTest, ParserBuilds)
// {
//     Parser result({TokenType::END_OF_FILE});
// }
// TEST(ParserTest, ParserReadsDef)
// {
// // def hello() {}
//   test({TokenType::DEF,
//        {TokenType::IDENTIFIER, std::string("hello")},
//         TokenType::L_PAREN,
//         TokenType::R_PAREN,
//         TokenType::L_BRACE,
//         TokenType::R_BRACE,
//         TokenType::END_OF_FILE},
// 
//        {std::make_shared<Definition>(Definition(std::make_shared<Token>(TokenType::IDENTIFIER, string("hello")), {}, {}))}
//        );
// }
// 
// 
// TEST(ParserTest, ParserReadsExtern)
// {
//   // extern hello;" 
// 
//     // test({TokenType::EXTERN,
//     //      {TokenType::IDENTIFIER, std::string("hello")},
//     //       TokenType::EOL,
//     //       TokenType::END_OF_FILE}
//     //       {std::make_shared<Extern>(Extern())}
//     //      );
// }
// 
// void test(tokenStream input, program expected) {
//   std::ostringstream input_string;
//   std::ostringstream expected_string;
//   AstPrinter(input_string).print(Parser(input).parseProgram()), AstPrinter(expected_string).print(expected);
//   cout << expected_string.str() << std::endl;
//   ASSERT_EQ(input_string.str(), expected_string.str());
// }
// 
// 
