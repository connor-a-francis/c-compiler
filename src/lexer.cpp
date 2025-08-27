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
  while (true) {
    Token token = this->get_tok();
    this->tokens.push_back(token);
    if (std::holds_alternative<EndOfFile>(token)) {
      break;
    }
  }
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
  int start_index = this->char_index;
  while ((isalnum(this->get_current())) && this->get_current() != EOF_) {
    this->move_read_head();
  }
  int end_index = this->char_index;

  std::string curr_string(this->char_vec.begin() + start_index,
                          this->char_vec.begin() + end_index);

  if (curr_string == "let") {
    return {Let{}};
  } else if (curr_string == "def") {
    return {Def{}};
  } else if (curr_string == "extern") {
    return {Extern{}};
  } else if (curr_string == "return") {
    return {Return{}};

  } else {
    int length = end_index - start_index;
    const char *start_ptr = this->char_vec.data() + start_index;
    return Identifier{std::string_view(start_ptr, length)};
  }
};

Token Lexer::get_number() {
  std::string number_string;

  while (isdigit(this->get_current()) || this->get_current() == '.') {
    number_string.push_back(this->get_current());
    this->move_read_head();
  }

  float res;
  std::stringstream ss(number_string);
  ss >> res;

  if (ss.fail()) {
    std::cerr << "Fatal Error: Invalid Conversion" << std::endl;
    exit(EXIT_FAILURE);
  }
  return {Number{res}};
};

void Lexer::skip_whitespace() {
  while (isspace(this->get_current())) {
    this->move_read_head();
  }
};
void Lexer::move_read_head() { this->char_index += 1; };

void Lexer::skip_comment() {
  while ((this->get_current() != EOF_) && (this->get_current() != '\n') &&
         (this->get_current() != '\r')) {
    this->move_read_head();
  }
};
char Lexer::get_current() {
  if (this->char_index >= this->char_vec.size() ) {
    return EOF_;
  } else {
    return this->char_vec[this->char_index];
  }
};