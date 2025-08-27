#include <cassert>
#include <gtest/gtest.h>
#include <variant>
#include "compiler/lexer.h"
#include "compiler/token.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>


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

TEST(LexerTest, LexerBuilds) {
    std::vector<char> char_vec {'a'};
    Lexer result (char_vec);
}
TEST(LexerTest, LexerReadsEOF) {
    std::vector<char> char_vec {};
    Lexer lexer (char_vec);
    std::vector<Token> result = lexer.get_tokens();
    EXPECT_TRUE(std::holds_alternative<EndOfFile>(result[0]));
    EXPECT_EQ(result.size(), 1);
}
TEST(LexerTest, LexerReadsSpaceEOF) {
    std::vector<char> char_vec {' '};
    Lexer lexer (char_vec);
    auto result = hash_tokens(lexer.get_tokens());
    auto expected = hash_tokens({EndOfFile{}});
    EXPECT_EQ(result, expected);
}
TEST(LexerTest, LexerReadsDef) {
        std::string program = R"(def hello() {})";
        std::vector<char> input(program.begin(), program.end());
        auto result = hash_tokens(Lexer(input).get_tokens());
        auto expected = hash_tokens({
            Def{},
            Identifier("hello"),
            LParen{},
            RParen{},
            LBrace{},
            RBrace{},
            EndOfFile{},
        });
        EXPECT_EQ(result, expected);

}
TEST(LexerTest, LexerReadsExtern) {
    std::string program = R"(extern hello;)";
    std::vector<char> input(program.begin(), program.end());
    auto result = hash_tokens(Lexer(input).get_tokens());
    auto expected = hash_tokens({
        Extern{},
        Identifier("hello"),
        EOL{},
        EndOfFile{},
    });
        EXPECT_EQ(result, expected);

}
TEST(LexerTest, LexerSkipsComment) {
    std::string program = R"(extern hello
                          # skip me!
                          def goodbye() {})";

    std::vector<char> input(program.begin(), program.end());

    auto result = hash_tokens(Lexer(input).get_tokens());
    auto expected = hash_tokens({
            Extern{},
            Identifier("hello"),
            Def{},
            Identifier("goodbye"),
            LParen{},
            RParen{},
            LBrace{},
            RBrace{},
            EndOfFile{},
        });
        EXPECT_EQ(result, expected);
}
TEST(LexerTest, LexerReadsMath) {
    std::string program = R"(let a=(b+c)-d*e/(f+$);)";
    std::vector<char> input(program.begin(), program.end());
    auto result = hash_tokens(Lexer(input).get_tokens());

    auto expected = hash_tokens({
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
        EXPECT_EQ(result, expected);
}
TEST(LexerTest, LexerReadsDefAndImpl) {
    
    std::string program = R"(
        def hello() {
            let a = b + c;
        }
    )";

    std::vector<char> input(program.begin(), program.end());
    auto result = hash_tokens(Lexer(input).get_tokens());

    auto expected = hash_tokens({
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
        EXPECT_EQ(result, expected);
}
TEST(LexerTest, LexerReadsNumbers) {


}
TEST(LexerTest, LexerHatesWeirdNumbers) {}




/*
    #[test]
    fn lexer_reads_numbers() {
        let program: Vec<char> = r###"
        def hellodef() {
            let a = 45 + 69.2;
        }
        "###
        .chars()
        .collect();
        let result = Lexer::new(program).get_tokens();
        let expected = vec![
            Token::Def,
            Token::Identifier("hellodef".to_string()),
            Token::LParen,
            Token::RParen,
            Token::LBrace,
            Token::Let,
            Token::Identifier("a".to_string()),
            Token::Eq,
            Token::Number(45f32),
            Token::Add,
            Token::Number(69.2),
            Token::EOL,
            Token::RBrace,
            Token::EOF,
        ];
        assert_eq!(result, expected)
    }
    #[test]
    #[should_panic]
    fn lexer_hates_weird_numbers() {
        let program: Vec<char> = r###"
        def hello() {
            let a = 45 + 69.2.3;
        }
        "###
        .chars()
        .collect();
        let _ = Lexer::new(program).get_tokens();
    }
}
*/
