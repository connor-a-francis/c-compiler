#pragma once

#include "token.h"
#include <vector>
#include <variant>
#include<iostream>

class Lexer {
public:
    // Public methods (interface)
    Lexer(std::vector<char> input){
        char_vec = input;
        char_index = 0;
        std::vector<Token> tokens;
        tokens.reserve(100000);
    }


    std::vector<Token> get_tokens();

private:
    Token get_tok();
    Token get_symbol(char c);
    Token get_string();
    Token get_number();
    void skip_whitespace();
    void move_read_head();
    void skip_comment();
    char get_current();

    // Private member variables (data)
    std::vector<char> char_vec;
    int char_index;
    std::vector<Token> tokens;
    
};

