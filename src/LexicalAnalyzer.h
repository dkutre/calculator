#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <iostream>
#include <vector>
#include "Token.h"

class LexicalAnalyzer
{
public:
    LexicalAnalyzer() = default;
    bool parse_string(std::string& str);
    std::vector<Token> get_tokens();
    void clear();

private:
    std::vector<Token> tokens;
};

#endif
