#include "compiler/lexer.h"
#include "compiler/token.h"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

char EOF_ = '\x1B';


std::vector<Token> Lexer::get_tokens() {
  if (this->char_vec.size() == 0) {
    return {EndOfFile{}};
  }
  do {this->tokens.push_back(this->get_tok());}
  while (!std::holds_alternative<EndOfFile>(this->tokens.back()));
  return this->tokens;
};

Token Lexer::get_tok() {
  this->skip_whitespace();

  char c = this->get_current();

  if (c == EOF_) {
    return {EndOfFile{}};
  } else if (isdigit(c) || c == '.') {
    return this->get_number();
  } else if (c == '#') {
    this->skip_comment();
    return this->get_tok();
  } else if (isalpha(c)) {
    return this->get_string();
  } else {
    this->move_read_head();
    return this->get_symbol(c);
  }
};

Token Lexer::get_symbol(char c) {
  Token t;
  switch (c) {
  case '=':
    t = Eq{};
    break;
  case ';':
    t = EOL{};
    break;
  case '(':
    t = LParen{};
    break;
  case ')':
    t = RParen{};
    break;
  case '{':
    t = LBrace{};
    break;
  case '}':
    t = RBrace{};
    break;

  case '+':
    [[fallthrough]];
  case '-':
    [[fallthrough]];
  case '*':
    [[fallthrough]];
  case '/':
    t = Op{c};
    break;
  default:
    t = Misc{c};
  }
  return t;
};

Token Lexer::get_string() {
  int start = this->char_index;

  char cur = this->get_current();
  while ((isalnum(cur)) && cur != EOF_) {
    this->move_read_head();
    cur = this->get_current();
  }

  return get_token_from_string(start, this->char_index);
};

Token Lexer::get_token_from_string(int start, int end) {
  auto vec_ptr = this->char_vec.begin();
  std::string curr_string(vec_ptr + start, vec_ptr + end);

  if (curr_string == "let") {
    return {Let{}};
  } else if (curr_string == "def") {
    return {Def{}};
  } else if (curr_string == "extern") {
    return {Extern{}};
  } else if (curr_string == "return") {
    return {Return{}};
  } else {
    return Identifier{
        std::string_view(this->char_vec.data() + start, end - start)};
  }
}

Token Lexer::get_number() {
  std::string number_string;

  char cur = this->get_current();
  while (isdigit(cur) || cur == '.') {
    number_string.push_back(cur);
    this->move_read_head();
    cur = this->get_current();
  }
  return get_token_from_number_string(number_string);
};

Token Lexer::get_token_from_number_string(std::string number_string) {
  float res;
  std::stringstream ss(number_string);
  ss >> res;

  if (ss.fail() or !ss.eof()) {
    std::cerr << "Fatal Error: Invalid Conversion" << std::endl;
    exit(EXIT_FAILURE);
  }
  return {Number{res}};
}

void Lexer::skip_whitespace() {
  while (isspace(this->get_current())) {
    this->move_read_head();
  }
};

void Lexer::move_read_head() { this->char_index += 1; };

void Lexer::skip_comment() {
  char cur = this->get_current();
  while ((cur != EOF_) && (cur != '\n') && (cur != '\r')) {
    this->move_read_head();
    cur = this->get_current();
  }
};

char Lexer::get_current() {
  return (this->char_index >= this->char_vec.size()) ? EOF_ : this->char_vec[this->char_index];
};
