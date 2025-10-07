#pragma once

#include <stdexcept>
#include "compiler/token.h"
using namespace std;


class parse_error : public runtime_error {
    public :
       parse_error(Token tok, const std::string& msg) : runtime_error(msg), tok(std::move(tok)) { }
    private:
        Token tok;
};

