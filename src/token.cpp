#include <string>
#include <any>
#include "compiler/token.h"

using enum TokenType;

    std::string Token::toString() const {
        return "Token(" + typeToString() + ", " +  literalToString() + "line: " + std::to_string(line) + ", col: " + std::to_string(col) + ", length: " + std::to_string(length) + ")";
    }

    std::string Token::literalToString() const {
        switch (type) {
            case IDENTIFIER:
                return "literal: " + std::any_cast<std::string>(literal) + ", ";
            case NUMBER:
                return "literal: " + std::to_string(std::any_cast<float>(literal)) + ", ";
            case MISC:
                return "literal: " + std::string(1, std::any_cast<char>(literal)) + ", ";
            case END_OF_FILE:
            case ADD:
            case SUB:
            case MUL:
            case DIV:
            case EOL:
            case DEF:
            case LET:
            case EXTERN:
            case RETURN:
            case EQ:
            case L_PAREN:
            case R_PAREN:
            case L_BRACE:
            case R_BRACE:
            default:
                return "";
        }
    }

    std::string Token::typeToString() const {
        switch (type) {
            case IDENTIFIER:
                return "Identifier";
            case NUMBER:
                return "Number";
            case END_OF_FILE:
                return "EOF";
            case EOL:
                return "EOL";
            case ADD:
                return "Add";
            case SUB:
                return "Sub";
            case MUL:
                return "Mul";
            case DIV:
                return "Div";
            case EQ:
                return "Operator";
            case DEF:
                return "Def";
            case LET:
                return "Let";
            case EXTERN:
                return "Extern";
            case RETURN:
                return "Keyword";
            case L_PAREN:
                return "Left Paren";
            case R_PAREN:
                return "Right Paren";
            case L_BRACE:
                return "Left Brace";
            case R_BRACE:
                return "Right Brace";
            default:
                return "Misc";
        }
    }
