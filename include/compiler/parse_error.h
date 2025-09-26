#pragma once

#include <stdexcept>
using namespace std;


class parse_error : public runtime_error {
    public :
       parse_error(const std::string& msg) : runtime_error(msg) {
    }
};

