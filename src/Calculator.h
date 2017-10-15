#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <tuple>
#include <vector>
#include <stack>
#include <iostream>
#include "Token.h"

class Calculator
{
public:
    Calculator() = default;
    std::tuple<double, bool> calculate(std::vector<Token>& tokens);

private:
    void division(std::stack<double>& operands);
    void summation(std::stack<double>& operands);
    void subtraction(std::stack<double>& operands);
    void multiplication(std::stack<double>& operands);
    void addUnaryOperations(std::vector<Token>& tokens);
    bool transformToRPN(std::vector<Token>& tokens); // RPN - Reverse Polish notation

    std::vector<Token> rpn;
};

#endif
