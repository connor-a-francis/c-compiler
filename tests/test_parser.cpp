#include "../src/pretty_printer.cpp"
#include "compiler/ast.h"
#include "compiler/parser.h"
#include "compiler/token.h"
#include "gtest/gtest.h"
#include <cassert>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

void test(std::vector<Token> input, AST::Program expected_input);
void test_crashes(std::string program, std::string msg);

TEST(ParserTest, ParserBuilds) { Parser result{{Identifier{"a"}}}; }

TEST(ParserTest, ParserParsesEmpty) { test({EndOfFile{}}, AST::Program({})); }
TEST(ParserTest, ParserParsesDEF){test(
    {
        Def{},
        Identifier("hello"),
        LParen{},
        RParen{},
        LBrace{},
        RBrace{},
        EndOfFile{},
    },
    std::make_unique<AST::Program>(std::vector<std::unique_ptr<AST::Expr>>({
        std::make_unique<AST::Definition>(
            Identifier("hello"),
            std::vector<std::unique_ptr<AST::Expr>>{}, // empty body
            std::unique_ptr<AST::Program>{}

            )})));

} // TEST(ParserTest, LexerReadsExtern) {
  //     test(R"(extern hello;)", {
  //         Extern{},
  //         Identifier("hello"),
  //         EOL{},
  //         EndOfFile{},
  //     });
  // }
  // TEST(ParserTest, LexerSkipsComment) {
  //     test(R"(extern hello
  //                           # skip me!
  //                           def goodbye() {})", {
  //             Extern{},
  //             Identifier("hello"),
  //             Def{},
  //             Identifier("goodbye"),
  //             LParen{},
  //             RParen{},
  //             LBrace{},
  //             RBrace{},
  //             EndOfFile{}
  //         });
  // }
  // TEST(ParserTest, LexerReadsMath) {
  //     test(R"(let a=(b+c)-d*e/(f+$);)", {
  //             Let{},
  //             Identifier("a"),
  //             Eq{},
  //             LParen{},
  //             Identifier("b"),
  //             Op('+'),
  //             Identifier("c"),
  //             RParen{},
  //             Op('-'),
  //             Identifier("d"),
  //             Op('*'),
  //             Identifier("e"),
  //             Op('/'),
  //             LParen{},
  //             Identifier("f"),
  //             Op('+'),
  //             Misc('$'),
  //             RParen{},
  //             EOL{},
  //             EndOfFile{}
  //         });
  // }
  //
  // TEST(ParserTest, LexerReadsDefAndImpl) {
  //     test(R"(
  //         def hello() {
  //             let a = b + c;
  //         }
  //         )", {
  //             Def{},
  //             Identifier("hello"),
  //             LParen{},
  //             RParen{},
  //             LBrace{},
  //             Let{},
  //             Identifier("a"),
  //             Eq{},
  //             Identifier("b"),
  //             Op('+'),
  //             Identifier("c"),
  //             EOL{},
  //             RBrace{},
  //             EndOfFile{},
  //     });
  // }
  // TEST(ParserTest, LexerReadsNumbers) {
  //     test(R"(
  //         def hellodef() {
  //             let a = 45 + 69.2;
  //         }
  //         )", {
  //             Def{},
  //             Identifier("hellodef"),
  //             LParen{},
  //             RParen{},
  //             LBrace{},
  //             Let{},
  //             Identifier("a"),
  //             Eq{},
  //             Number(45.0),
  //             Op{'+'},
  //             Number(69.2),
  //             EOL{},
  //             RBrace{},
  //             EndOfFile{},
  //         });
  // }
  // TEST(ParserTest, LexerCrashesWithMultipleDecimals) {
  //     test_crashes(R"(
  //         def hello() {
  //             let a = 45 + 69.2.3;
  //         }
  //     )", "Fatal Error: Invalid Conversion");
  // }
  // Utility Functions
std::basic_string<char> hash_AST(AST::Program p) {
  auto s = std::get<std::basic_string<char>>(AstPrinter().visitProgram(p));
  return s;
}

void test(std::vector<Token> input, std::unique_ptr<AST::Program> expected_input) {
  Parser p(input);
  auto res = std::make_unique<AST::Program>(p.parseProgram());
  auto result = hash_AST(*res);
  auto expected = hash_AST(*expected_input);
  ASSERT_EQ(result, expected.append("1"));
}
