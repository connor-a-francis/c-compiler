#include "compiler/lexer.h"
#include "compiler/token.h"
#include "gtest/gtest.h"
#include <cassert>
#include <gtest/gtest.h>
#include <string>
#include <variant>
#include <vector>

using enum TokenType;

void test(std::string program, std::vector<Token> expected_input);
void test_crashes(std::string program, std::string msg);

TEST(LexerTest, LexerBuilds) { Lexer result({'a'}); }
TEST(LexerTest, LexerReadsEOF) { test("", {{END_OF_FILE, 0, 0, 1}}); }
TEST(LexerTest, LexerReadsSpaceEOF) { test(" ", {{END_OF_FILE, 0, 1, 1}}); }
TEST(LexerTest, LexerReadsDef) {
  test(R"(def hello() {})",
       {Token(DEF, 0, 0, 3), Token(IDENTIFIER, 0, 4, 5, std::string("hello")),
        Token(L_PAREN, 0, 9, 1), Token(R_PAREN, 0, 10, 1),
        Token(L_BRACE, 0, 12, 1), Token(R_BRACE, 0, 13, 1),
        Token(END_OF_FILE, 0, 14, 1)});
}
TEST(LexerTest, LexerReadsExtern) {
  test(R"(extern hello;)",
       {Token(EXTERN, 0, 0, 6),
        Token(IDENTIFIER, 0, 7, 5, std::string("hello")), Token(EOL, 0, 12, 1),
        Token(END_OF_FILE, 0, 13, 1)});
}
TEST(LexerTest, LexerSkipsComment) {
  test(R"(extern hello
                         # skip me!
                          def goodbye() {})",
       {Token(EXTERN, 0, 0, 6),
        Token(IDENTIFIER, 0, 7, 5, std::string("hello")), Token(DEF, 2, 0, 3),
        Token(IDENTIFIER, 2, 4, 7, std::string("goodbye")),
        Token(L_PAREN, 2, 11, 1), Token(R_PAREN, 2, 12, 1),
        Token(L_BRACE, 2, 14, 1), Token(R_BRACE, 2, 15, 1),
        Token(END_OF_FILE, 2, 16, 1)});
}
TEST(LexerTest, LexerReadsMath) {

  test(R"(let a=(b+c)-d*e/(f+$);)",
       {Token(LET, 0, 0, 3),
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
        Token(MISC, 0, 19, 1, '$'),
        Token(R_PAREN, 0, 20, 1),
        Token(EOL, 0, 21, 1),
        Token(END_OF_FILE, 0, 22, 1)});
}

TEST(LexerTest, LexerReadsDefAndImpl)
{
    test(R"(
        def hello(b, c) {
            return b + c;
        }
        )",
         {
             Token(DEF, 1, 0, 3),
             Token(IDENTIFIER, 1, 4, 5, std::string("hello")),
             Token(L_PAREN, 1, 9, 1),
             Token(IDENTIFIER, 1, 10, 1, std::string("b")),
             Token(COMMA, 1, 11, 1),
             Token(IDENTIFIER, 1, 13, 1, std::string("c")),
             Token(R_PAREN, 1, 14, 1),
             Token(L_BRACE, 1, 16, 1),
             Token(RETURN, 2, 0, 6),
             Token(IDENTIFIER, 2, 7, 1, std::string("b")),
             Token(ADD, 2, 9, 1),
             Token(IDENTIFIER, 2, 11, 1, std::string("c")),
             Token(EOL, 2, 12, 1),
             Token(R_BRACE, 3, 0, 1),
             Token(END_OF_FILE, 4, 0, 1),
         });
}
TEST(LexerTest, LexerReadsNumbers)
{
    test(R"(
        def hello() {
            let a = 45 + 69.2;
        }
        )",
         {
             Token(DEF, 1, 0, 3),
             Token(IDENTIFIER, 1, 4, 5, std::string("hello")),
             Token(L_PAREN, 1, 9, 1),
             Token(R_PAREN, 1, 10, 1),
             Token(L_BRACE, 1, 12, 1),
             Token(LET, 2, 0, 3),
             Token(IDENTIFIER, 2, 4, 1, std::string("a")),
             Token(EQ, 2, 6, 1),
             Token(NUMBER, 2, 8, 2, (float)45.0),
             Token(ADD, 2, 11, 1),
             Token(NUMBER, 2, 13, 4, (float)69.2),
             Token(EOL, 2, 17, 1),
             Token(R_BRACE, 3, 0, 1),
             Token(END_OF_FILE, 4, 0, 1),
         });
}

TEST(LexerTest, LexerCrashesWithMultipleDecimals)
{
    test_crashes(R"(
        def hello() {
            let a = 45 + 69.2.3;
        }
    )",
                 "Fatal Error: Invalid Float Conversion");
}

void test(std::string program, std::vector<Token> expected_input) {
  std::vector<char> input(program.begin(), program.end());
  auto result = Lexer(input).get_tokens();
  auto expected = expected_input;
  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); i++) {
    std::string s =
        result[i].toString() + " should be equal to " + expected[i].toString();
    ASSERT_EQ(result[i].type, expected[i].type) << s;
    ASSERT_EQ(result[i].line, expected[i].line) << s;
    ASSERT_EQ(result[i].col, expected[i].col) << s;
    ASSERT_EQ(result[i].length, expected[i].length) << s;

    if (result[i].type == IDENTIFIER) {
      ASSERT_EQ(std::any_cast<std::string>(result[i].literal),
                std::any_cast<std::string>(expected[i].literal))
          << s;
    } else if (result[i].type == NUMBER) {
      ASSERT_EQ(std::any_cast<float>(result[i].literal),
                std::any_cast<float>(expected[i].literal))
          << s;
    } else if (result[i].type == MISC) {
      ASSERT_EQ(std::any_cast<char>(result[i].literal),
                std::any_cast<char>(expected[i].literal))
          << s;
    }
  }
}

void test_crashes(std::string program, std::string msg) {
  std::vector<char> input(program.begin(), program.end());
  ASSERT_DEATH(Lexer(input).get_tokens(), msg);
}
