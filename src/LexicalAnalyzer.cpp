#include "LexicalAnalyzer.h"

void LexicalAnalyzer::clear()
{
    tokens.clear();
}

bool is_digit(const char& s)
{
    if ('0' <= s && s <= '9') {
        return true;
    } else {
        return false;
    }
}

std::string read_number(std::string::iterator& it, std::string::iterator end)
{
    std::string number;
    while (is_digit(*it) && it != end) {
        number.push_back(*it);
        it++;
    }
    if (*it == ',' || *it == '.') {
        number.push_back('.');
        it++;
    }
    while (is_digit(*it) && it != end) {
        number.push_back(*it);
        it++;
    }
    it--;
    return number;
}

bool LexicalAnalyzer::parse_string(std::string& str)
{
    for (auto it = str.begin(); it != str.end(); it++) {
        if ('0' <= *it && *it <= '9') {
            std::string token_data = read_number(it, str.end());
            tokens.push_back(Token(token_data, TokenType::number));
        } else if (*it == '+') {
            tokens.push_back(Token(std::string("+"), TokenType::summation));
        } else if (*it == '-') {
            tokens.push_back(Token(std::string("-"), TokenType::subtraction));
        } else if (*it == '*') {
            tokens.push_back(Token(std::string("*"), TokenType::multiplication));
        } else if (*it == '/') {
            tokens.push_back(Token(std::string("/"), TokenType::division));
        } else if (*it == '(') {
            tokens.push_back(Token(std::string("("), TokenType::left_brace));
        } else if (*it == ')') {
            tokens.push_back(Token(std::string(")"), TokenType::right_brace));
        } else if (*it == ' ') {

        } else {
            return false;
        }
    }
    return true;
}


std::vector<Token> LexicalAnalyzer::get_tokens()
{
    return tokens;
}
