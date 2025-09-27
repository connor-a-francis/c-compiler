#include <string>
#include <any>
#include "compiler/token.h"

    std::string Token::toString() const {
        return "Token(" + typeToString() + ", " +  literalToString() + "line: " + std::to_string(line) + ", col: " + std::to_string(col) + ", length: " + std::to_string(length) + ")";
    }

    std::string Token::literalToString() const {
        switch (type) {
            case TokenType::IDENTIFIER:
                return "literal: " + std::any_cast<std::string>(literal) + ", ";
            case TokenType::NUMBER:
                return "literal: " + std::to_string(std::any_cast<float>(literal)) + ", ";
            case TokenType::MISC:
                return "literal: " + std::string(1, std::any_cast<char>(literal)) + ", ";
            case TokenType::END_OF_FILE:
            case TokenType::ADD:
            case TokenType::SUB:
            case TokenType::MUL:
            case TokenType::DIV:
            case TokenType::EOL:
            case TokenType::DEF:
            case TokenType::LET:
            case TokenType::EXTERN:
            case TokenType::RETURN:
            case TokenType::EQ:
            case TokenType::L_PAREN:
            case TokenType::R_PAREN:
            case TokenType::L_BRACE:
            case TokenType::R_BRACE:
            default:
                return "";
        }
    }

    std::string Token::typeToString() const {
        switch (type) {
            case TokenType::IDENTIFIER:
                return "Identifier";
            case TokenType::NUMBER:
                return "Number";
            case TokenType::MISC:
                return "Misc";
            case TokenType::END_OF_FILE:
                return "EOF";
            case TokenType::EOL:
                return "EOL";
            case TokenType::ADD:
                return "Add";
            case TokenType::SUB:
                return "Sub";
            case TokenType::MUL:
                return "Mul";
            case TokenType::DIV:
                return "Div";
            case TokenType::EQ:
                return "Operator";
            case TokenType::DEF:
                return "Def";
            case TokenType::LET:
                return "Let";
            case TokenType::EXTERN:
                return "Extern";
            case TokenType::RETURN:
                return "Keyword";
            case TokenType::L_PAREN:
                return "Left Paren";
            case TokenType::R_PAREN:
                return "Right Paren";
            case TokenType::L_BRACE:
                return "Left Brace";
            case TokenType::R_BRACE:
                return "Right Brace";
            default:
                return "UNKNOWN";
        }
    }
