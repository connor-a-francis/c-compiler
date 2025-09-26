#pragma once

#include "token.h"
#include <vector>

class Lexer {
public:
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
    Token get_token_from_string(int start, int end);
    Token get_token_from_number_string(std::string number_string);
    void skip_whitespace();
    void move_read_head();
    void skip_comment();
    char get_current();

    std::vector<char> char_vec;
    int char_index;
    std::vector<Token> tokens;
    
};
