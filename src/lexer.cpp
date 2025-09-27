#include "compiler/lexer.h"
#include "compiler/token.h"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using enum TokenType;
char EOF_ = '\x1B';

std::vector<Token> Lexer::get_tokens() {
  if (char_vec.size() == 0) {
    return {Token(END_OF_FILE, get_line(), get_col(), 1)};
  }

  iterate_through_char_vec();
  return tokens;
};

void Lexer::iterate_through_char_vec() {
  do {
    tokens.push_back(get_tok());
  } while (tokens.back().type != END_OF_FILE);
}

Token Lexer::get_tok() {
  skip_whitespace();

  char c = get_current();
  Token t;

  if (c == EOF_) {
    return {Token(END_OF_FILE, get_line(), get_col(), 1)};
  } else if (isdigit(c) || c == '.') {
    t = get_number();
  } else if (c == '#') {
    skip_comment();
    t = get_tok();
  } else if (isalpha(c)) {
    t = get_string();
  } else {
    t = get_symbol();
    move_read_head();
  }
  return t;
};

Token Lexer::get_symbol() {
  char c = get_current();
  TokenType t;
  std::any lit;
  switch (c) {
  case '=':
    t = EQ;
    break;
  case ';':
    t = EOL;
    break;
  case '(':
    t = L_PAREN;
    break;
  case ')':
    t = R_PAREN;
    break;
  case ',':
    t = COMMA;
    break;
  case '{':
    t = L_BRACE;
    break;
  case '}':
    t = R_BRACE;
    break;
  case '+':
    t = ADD;
    break;
  case '-':
    t = SUB;
    break;
  case '*':
    t = MUL;
    break;
  case '/':
    t = DIV;
    break;
  default:
    t = MISC;
    lit = c;
  }
  return {t, get_line(), get_col(), 1, lit};
};

Token Lexer::get_string() {
  int start = char_index;

  char cur = get_current();
  while ((isalnum(cur)) && cur != EOF_) {
    move_read_head();
    cur = get_current();
  }

  return get_token_from_string(start, char_index);
};

Token Lexer::get_number() {
  int start = char_index;

  char cur = get_current();
  while (isdigit(cur) || cur == '.') {
    move_read_head();
    cur = get_current();
  }
  return get_token_from_number_string(start, char_index);
};

Token Lexer::get_token_from_string(int start, int end) {
  auto ptr = char_vec.begin();
  std::string curr_string(ptr + start, ptr + end);
  std::any literal = "";
  TokenType type;

  if (curr_string == "let") {
    type = LET;
  } else if (curr_string == "def") {
    type = DEF;
  } else if (curr_string == "extern") {
    type = EXTERN;
  } else if (curr_string == "return") {
    type = RETURN;
  } else {
    type = IDENTIFIER;
    literal = std::string(char_vec.data() + start, end - start);
  }
  if (type == IDENTIFIER) {
    return Token(type, get_line(), get_col(start), end - start, literal);
  }
  return Token(type, get_line(), get_col(start), end - start);
}

Token Lexer::get_token_from_number_string(int start, int end) {
  float res;
  std::stringstream ss(std::string(char_vec.data() + start, end - start));
  ss >> res;

  if (ss.fail() or !ss.eof()) {
    std::cerr << "Fatal Error: Invalid Float Conversion" << std::endl;
    exit(EXIT_FAILURE);
  }
  return {Token(NUMBER, get_line(), get_col(start), end - start, res)};
}

void Lexer::skip_whitespace() {
  int new_lines = 0;
  while (isspace(get_current())) {
    char c = get_current();
    if (c == '\r' || c == '\n') {
      new_lines++;
    }
    move_read_head();
  }
  if (new_lines) {
    move_lines(new_lines);
  }
};

void Lexer::move_read_head() { char_index++; };

void Lexer::skip_comment() {
  char cur = get_current();
  while ((cur != EOF_) && (cur != '\n') && (cur != '\r')) {
    move_read_head();
    cur = get_current();
  }
};

char Lexer::get_current() {
  return (char_index >= char_vec.size()) ? EOF_ : char_vec[char_index];
};

int Lexer::get_line() { return line_index; };

int Lexer::get_col(int index) { return index - new_line_index; };

int Lexer::get_col() { return get_col(char_index); };

void Lexer::move_lines(int new_lines) {
  line_index += new_lines;
  new_line_index = char_index;
}
