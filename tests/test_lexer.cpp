#include "gtest/gtest.h"
#include <cassert>
#include <gtest/gtest.h>
#include <variant>
#include "compiler/lexer.h"
#include "compiler/token.h"
#include <string>
#include <vector>

void test(std::string program, std::vector<Token> expected_input);
void test_crashes(std::string program, std::string msg);

TEST(LexerTest, LexerBuilds)
{
    Lexer result({'a'});
}
TEST(LexerTest, LexerReadsEOF)
{
    test("", {TokenType::END_OF_FILE});
}
TEST(LexerTest, LexerReadsSpaceEOF)
{
    test(" ", {TokenType::END_OF_FILE});
}
TEST(LexerTest, LexerReadsDef)
{
    test(R"(def hello() {})", {
                                  TokenType::DEF,
                                  {TokenType::IDENTIFIER, std::string("hello")},
                                  TokenType::L_PAREN,
                                  TokenType::R_PAREN,
                                  TokenType::L_BRACE,
                                  TokenType::R_BRACE,
                                  TokenType::END_OF_FILE,
                              });
}
TEST(LexerTest, LexerReadsExtern)
{
    test(R"(extern hello;)", {
                                 TokenType::EXTERN,
                                 {TokenType::IDENTIFIER, std::string("hello")},
                                 TokenType::EOL,
                                 TokenType::END_OF_FILE,
                             });
}
TEST(LexerTest, LexerSkipsComment)
{
    test(R"(extern hello
                          # skip me!
                          def goodbye() {})",
         {TokenType::EXTERN,
          {TokenType::IDENTIFIER, std::string("hello")},
          TokenType::DEF,
          {TokenType::IDENTIFIER, std::string("goodbye")},
          TokenType::L_PAREN,
          TokenType::R_PAREN,
          TokenType::L_BRACE,
          TokenType::R_BRACE,
          TokenType::END_OF_FILE});
}
TEST(LexerTest, LexerReadsMath)
{
    test(R"(let a=(b+c)-d*e/(f+$);)", {TokenType::LET,
                                       {TokenType::IDENTIFIER, std::string("a")},
                                       TokenType::EQ,
                                       TokenType::L_PAREN,
                                       {TokenType::IDENTIFIER, std::string("b")},
                                       TokenType::ADD,
                                       {TokenType::IDENTIFIER, std::string("c")},
                                       TokenType::R_PAREN,
                                       TokenType::SUB,
                                       {TokenType::IDENTIFIER, std::string("d")},
                                       TokenType::MUL,
                                       {TokenType::IDENTIFIER, std::string("e")},
                                       TokenType::DIV,
                                       TokenType::L_PAREN,
                                       {TokenType::IDENTIFIER, std::string("f")},
                                       TokenType::ADD,
                                       {TokenType::MISC, '$'},
                                       TokenType::R_PAREN,
                                       TokenType::EOL,
                                       TokenType::END_OF_FILE});
}

TEST(LexerTest, LexerReadsDefAndImpl)
{
    test(R"(
        def hello() {
            let a = b + c;
        }
        )",
         {
             TokenType::DEF,
             {TokenType::IDENTIFIER, std::string("hello")},
             TokenType::L_PAREN,
             TokenType::R_PAREN,
             TokenType::L_BRACE,
             TokenType::LET,
             {TokenType::IDENTIFIER, std::string("a")},
             TokenType::EQ,
             {TokenType::IDENTIFIER, std::string("b")},
             TokenType::ADD,
             {TokenType::IDENTIFIER, std::string("c")},
             TokenType::EOL,
             TokenType::R_BRACE,
             TokenType::END_OF_FILE,
         });
}
TEST(LexerTest, LexerReadsNumbers)
{
    test(R"(
        def hellodef() {
            let a = 45 + 69.2;
        }
        )",
         {
             TokenType::DEF,
             {TokenType::IDENTIFIER, std::string("hellodef")},
             TokenType::L_PAREN,
             TokenType::R_PAREN,
             TokenType::L_BRACE,
             TokenType::LET,
             {TokenType::IDENTIFIER, std::string("a")},
             TokenType::EQ,
             {TokenType::NUMBER, (float)45.0},
             TokenType::ADD,
             {TokenType::NUMBER, (float)69.2},
             TokenType::EOL,
             TokenType::R_BRACE,
             TokenType::END_OF_FILE,
         });
}
TEST(LexerTest, LexerCrashesWithMultipleDecimals)
{
    test_crashes(R"(
        def hello() {
            let a = 45 + 69.2.3;
        }
    )",
                 "Fatal Error: Invalid Conversion");
}

void test(std::string program, std::vector<Token> expected_input)
{
    std::vector<char> input(program.begin(), program.end());
    auto result = Lexer(input).get_tokens();
    auto expected = expected_input;
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); i++)
    {
        ASSERT_EQ(result[i].type, expected[i].type);
        if (result[i].type == TokenType::IDENTIFIER)
        {
            ASSERT_EQ(std::any_cast<std::string>(result[i].literal), std::any_cast<std::string>(expected[i].literal));
        }
        else if (result[i].type == TokenType::NUMBER)
        {
            ASSERT_EQ(std::any_cast<float>(result[i].literal), std::any_cast<float>(expected[i].literal));
        }
        else if (result[i].type == TokenType::MISC)
        {
            ASSERT_EQ(std::any_cast<char>(result[i].literal), std::any_cast<char>(expected[i].literal));
        }
    }
}

void test_crashes(std::string program, std::string msg)
{
    std::vector<char> input(program.begin(), program.end());
    ASSERT_DEATH(Lexer(input).get_tokens(), msg);
}
