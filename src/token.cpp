#include <string>
#include <any>
#include "compiler/token.h"

    std::string Token::toString() const {
        return "Token(" + typeToString() + ", " + literalToString() + ")";
    }

    std::string Token::literalToString() const {
        switch (type) {
            case TokenType::IDENTIFIER:
                return std::any_cast<std::string>(literal);
            case TokenType::NUMBER:
                return std::to_string(std::any_cast<float>(literal));
            case TokenType::MISC:
                return std::string(1, std::any_cast<char>(literal));
            case TokenType::END_OF_FILE:
                return "EOF";
            case TokenType::ADD:
                return "+";
            case TokenType::SUB:
                return "-";
            case TokenType::MUL:
                return "*";
            case TokenType::DIV:
                return "/";
            case TokenType::EOL:
                return ";";
            case TokenType::DEF:
                return "def";
            case TokenType::LET:
                return "let";
            case TokenType::EXTERN:
                return "extern";
            case TokenType::RETURN:
                return "return";
            case TokenType::EQ:
                return "=";
            case TokenType::L_PAREN:
                return "(";
            case TokenType::R_PAREN:
                return ")";
            case TokenType::L_BRACE:
                return "{";
            case TokenType::R_BRACE:
                return "}";
            default:
                return "UNKNOWN";
        }
    }

    std::string Token::typeToString() const {
        switch (type) {
            case TokenType::IDENTIFIER:
                return "Identifier";
            case TokenType::NUMBER:
                return "Literal";
            case TokenType::MISC:
                return "Misc";
            case TokenType::END_OF_FILE:
                return "EOF";
            case TokenType::EOL:
                return "EOL";
            case TokenType::ADD:
            case TokenType::SUB:
            case TokenType::MUL:
            case TokenType::DIV:
            case TokenType::EQ:
                return "Operator";
            case TokenType::DEF:
            case TokenType::LET:
            case TokenType::EXTERN:
            case TokenType::RETURN:
                return "Keyword";
            case TokenType::L_PAREN:
            case TokenType::R_PAREN:
            case TokenType::L_BRACE:
            case TokenType::R_BRACE:
                return "Delimiter";
            default:
                return "UNKNOWN";
        }
    }
