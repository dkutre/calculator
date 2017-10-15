#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "TokenType.h"


class Token
{
public:
    Token(std::string str, TokenType type);
    // Token(char* str, Token)
    Token() = default;
    Token(const Token&) = default;
    const std::string& get_data() const;
    const TokenType& get_type() const;

private:
    std::string data;
    TokenType type;
};



#endif
