#pragma once

enum class TokenType {
    END_OF_FILE,
    ADD,
    SUB,
    DIV,
    MUL,
    EOL,
    DEF,
    LET,
    EXTERN,
    RETURN,
    EQ,
    L_PAREN,
    R_PAREN,
    L_BRACE,
    R_BRACE,
    IDENTIFIER,
    NUMBER,
    MISC
};