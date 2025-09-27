#pragma once

#include "token.h"
#include <vector>

class Lexer {
public:
    Lexer(std::vector<char> input){
        char_vec = input;
        char_index = 0;
        line_index = 0;
        new_line_index = 0;
        std::vector<Token> tokens;
        tokens.reserve(100000);
    }


    std::vector<Token> get_tokens();

private:
    Token get_tok();
    Token get_symbol();
    Token get_string();
    Token get_number();
    Token get_token_from_string(int start, int end);
    Token get_token_from_number_string(int start, int end);
    void iterate_through_char_vec();
    void skip_whitespace();
    void move_read_head();
    void move_lines(int new_lines);
    void skip_comment();
    char get_current();
    int get_line();
    int get_col();
    int get_col(int index);

    std::vector<char> char_vec;
    int char_index;
    int line_index;
    int new_line_index;
    std::vector<Token> tokens;
    
};
