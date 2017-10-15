#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <string>

enum class TokenType: int
{
    number = 0,
    summation,
    subtraction,
    multiplication,
    division,
    left_brace,
    right_brace
};

#endif
