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


TEST(LexerTest, LexerBuilds) {
    Lexer result ({'a'});
}
TEST(LexerTest, LexerReadsEOF) {
    test("", {EndOfFile{}});
}
TEST(LexerTest, LexerReadsSpaceEOF) {
    test(" ", {EndOfFile{}});
}
TEST(LexerTest, LexerReadsDef) {
        test(R"(def hello() {})", {
            Def{},
            Identifier("hello"),
            LParen{},
            RParen{},
            LBrace{},
            RBrace{},
            EndOfFile{},
        });
}
TEST(LexerTest, LexerReadsExtern) {
    test(R"(extern hello;)", {
        Extern{},
        Identifier("hello"),
        EOL{},
        EndOfFile{},
    });
}
TEST(LexerTest, LexerSkipsComment) {
    test(R"(extern hello
                          # skip me!
                          def goodbye() {})", {
            Extern{},
            Identifier("hello"),
            Def{},
            Identifier("goodbye"),
            LParen{},
            RParen{},
            LBrace{},
            RBrace{},
            EndOfFile{}
        });
}
TEST(LexerTest, LexerReadsMath) {
    test(R"(let a=(b+c)-d*e/(f+$);)", {
            Let{},
            Identifier("a"),
            Eq{},
            LParen{},
            Identifier("b"),
            Op('+'),
            Identifier("c"),
            RParen{},
            Op('-'),
            Identifier("d"),
            Op('*'),
            Identifier("e"),
            Op('/'),
            LParen{},
            Identifier("f"),
            Op('+'),
            Misc('$'),
            RParen{},
            EOL{},
            EndOfFile{}
        });
}

TEST(LexerTest, LexerReadsDefAndImpl) {
    test(R"(
        def hello() {
            let a = b + c;
        }
        )", {
            Def{},
            Identifier("hello"),
            LParen{},
            RParen{},
            LBrace{},
            Let{},
            Identifier("a"),
            Eq{},
            Identifier("b"),
            Op('+'),
            Identifier("c"),
            EOL{},
            RBrace{},
            EndOfFile{},
    });
}
TEST(LexerTest, LexerReadsNumbers) {
    test(R"(
        def hellodef() {
            let a = 45 + 69.2;
        }
        )", {
            Def{},
            Identifier("hellodef"),
            LParen{},
            RParen{},
            LBrace{},
            Let{},
            Identifier("a"),
            Eq{},
            Number(45.0),
            Op{'+'},
            Number(69.2),
            EOL{},
            RBrace{},
            EndOfFile{},
        });
}
TEST(LexerTest, LexerCrashesWithMultipleDecimals) {
    test_crashes(R"(
        def hello() {
            let a = 45 + 69.2.3;
        }
    )", "Fatal Error: Invalid Conversion");
}
// Utility Functions
struct TokenHasher {
    std::string operator()(EndOfFile) const { return "EOF"; }
    std::string operator()(Let) const { return "Let"; }
    std::string operator()(Def) const { return "Def"; }
    std::string operator()(Return) const { return "Return"; }
    std::string operator()(Extern) const { return "Extern"; }
    std::string operator()(Identifier id) const { return "Id(" + std::string(id.name) + ")"; }
    std::string operator()(Number n) const {
        return "Num(" + std::to_string(n.value) + ")";
    }
    std::string operator()(Op op) const { return std::string("Op(") + op.op + ")"; }
    std::string operator()(EOL) const { return "EOL"; }
    std::string operator()(Eq) const { return "Eq"; }
    std::string operator()(LParen) const { return "LParen"; }
    std::string operator()(RParen) const { return "RParen"; }
    std::string operator()(LBrace) const { return "LBrace"; }
    std::string operator()(RBrace) const { return "RBrace"; }
    std::string operator()(Misc m) const { return std::string("Misc(") + m.val + ")"; }
};

std::vector<std::string> hash_tokens(const std::vector<Token> &tokens) {
    std::vector<std::string> hashed;
    for (const auto &tok : tokens) {
        hashed.push_back(std::visit(TokenHasher{}, tok));
    }
    return hashed;
}

void test(std::string program, std::vector<Token> expected_input) {
        std::vector<char> input(program.begin(), program.end());
        auto result = hash_tokens(Lexer(input).get_tokens());
        auto expected = hash_tokens(expected_input);
        ASSERT_EQ(result, expected);
}

void test_crashes(std::string program, std::string msg) {
        std::vector<char> input(program.begin(), program.end());
        ASSERT_DEATH(Lexer(input).get_tokens(), msg);
}
