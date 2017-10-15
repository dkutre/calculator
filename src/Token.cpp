#include "Token.h"

Token::Token(std::string str, TokenType type)
    : data(str)
    , type(type)
{}

const std::string& Token::get_data() const
{
    return data;
}

const TokenType& Token::get_type() const
{
    return type;
}
