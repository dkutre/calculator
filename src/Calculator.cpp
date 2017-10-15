#include "Calculator.h"


int priority(const TokenType& type)
{
    switch (type){
        case TokenType::summation:
            return 1;
            break;
        case TokenType::subtraction:
            return 1;
            break;
        case TokenType::division:
            return 2;
            break;
        case TokenType::multiplication:
            return 2;
            break;
        default:
            return 0;
            break;
    }
}

bool isNumber(const std::vector<Token>::iterator& it)
{
    return (it->get_type() == TokenType::number);
}

bool isSummation(const std::vector<Token>::iterator& it)
{
    return (it->get_type() == TokenType::summation);
}

bool isSubtraction(const std::vector<Token>::iterator& it)
{
    return (it->get_type() == TokenType::subtraction);
}

bool isLeftBrace(const std::vector<Token>::iterator& it)
{
    return it->get_type() == TokenType::left_brace;
}

bool isRightBrace(const std::vector<Token>::iterator& it)
{
    return it->get_type() == TokenType::right_brace;
}

// x + -5 -> x + (0 - 5)
void Calculator::addUnaryOperations(std::vector<Token>& tokens)
{
    if (tokens.size() <= 2)
        return;
    std::vector<Token> processed_tokens;
    auto third = tokens.begin();
    auto first = third++;
    auto second = third++;

    if ((isSubtraction(first) || isSummation(first)) &&
        isNumber(second)
    ) {
        processed_tokens.push_back(Token("(", TokenType::left_brace));
        processed_tokens.push_back(Token("0", TokenType::number));
        processed_tokens.push_back(*first);
        processed_tokens.push_back(*second);
        processed_tokens.push_back(Token(")", TokenType::right_brace));
        first  += 2;
        second += 2;
        third  += 2;
    }


    processed_tokens.push_back(*first);
    processed_tokens.push_back(*second);

    while (third != tokens.end()) {
        if (isNumber(third) && !isLeftBrace(second) &&
            !isNumber(first) && !isRightBrace(first)
        ) {
            if (!processed_tokens.empty()) {
               processed_tokens.pop_back();
            }
            processed_tokens.push_back(Token("(", TokenType::left_brace));
            processed_tokens.push_back(Token("0", TokenType::number));
            processed_tokens.push_back(*second);
            processed_tokens.push_back(*third);
            processed_tokens.push_back(Token(")", TokenType::right_brace));
            first  += 1;
            second += 1;
            third  += 1;
        } else {
            processed_tokens.push_back(*third);
            first++;
            second++;
            third++;
        }
    }
    swap(tokens, processed_tokens);
}


bool Calculator::transformToRPN(std::vector<Token>& tokens)
{
    addUnaryOperations(tokens);

    std::stack<Token> operations;

    for (const Token& token: tokens) {
        auto type = token.get_type();
        switch (type) {
            case TokenType::number:
                rpn.push_back(token);
                break;
            case TokenType::left_brace:
                operations.push(token);
                break;
            case TokenType::right_brace:
                while (operations.top().get_type() != TokenType::left_brace) {
                    rpn.push_back(operations.top());
                    operations.pop();
                }
                if (operations.empty())
                    return false;
                operations.pop();
                break;
            default:
                if (!operations.empty()) {
                    auto type_top = operations.top().get_type();
                    while (priority(type) <= priority(type_top) &&
                           !operations.empty()
                    ) {
                        rpn.push_back(operations.top());
                        operations.pop();
                        if (!operations.empty())
                            type_top = operations.top().get_type();
                    }
                    operations.push(token);
                } else {
                    operations.push(token);
                }
                break;
        }
    }

    while (!operations.empty()) {
        rpn.push_back(operations.top());
        operations.pop();
    }
}

void print_stack(std::stack<double> stack)
{
    std::stack<double> temp;
    while (!stack.empty()) {
        temp.push(stack.top());
        stack.pop();
    }

    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}


std::tuple<double, bool> Calculator::calculate(std::vector<Token>& tokens)
{
    rpn.clear();
    transformToRPN(tokens);

    std::stack<double> operands;

    for (const Token& token: rpn) {
        auto type = token.get_type();
        switch (type) {
            case TokenType::number:
                operands.push(std::stod(token.get_data()));
                break;
            case TokenType::summation:
                if (operands.size() < 2)
                    return std::make_tuple(0, false);
                summation(operands);
                break;
            case TokenType::subtraction:
                if (operands.size() < 2)
                    return std::make_tuple(0, false);
                subtraction(operands);
                break;
            case TokenType::division:
                if (operands.size() < 2)
                    return std::make_tuple(0, false);
                division(operands);
                break;
            case TokenType::multiplication:
                if (operands.size() < 2)
                    return std::make_tuple(0, false);
                multiplication(operands);
                break;
            default:
                return std::make_tuple(0, false); // error;
                break;
        }
        // print_stack(operands);
    }

    // rounding
    int temp = operands.top() * 100;
    operands.pop();
    operands.push((double) temp / 100);

    return std::make_tuple(operands.top(), true);
}

std::tuple<double, double> get_last_pair(std::stack<double>& operands)
{
    if (operands.size() >= 2) {
        double a = operands.top();
        operands.pop();
        double b = operands.top();
        operands.pop();
        return std::make_tuple(a, b);
    } else {
        std::cout << "\nbad_string\n";
        return std::make_tuple(0, 0);
    }
}

void Calculator::summation(std::stack<double>& operands)
{
    double a = 0;
    double b = 0;
    std::tie(a, b) = get_last_pair(operands);
    operands.push(a + b);
}

void Calculator::subtraction(std::stack<double>& operands)
{
    double a = 0;
    double b = 0;
    std::tie(a, b) = get_last_pair(operands);
    operands.push(b - a);
}

void Calculator::division(std::stack<double>& operands)
{
    double a = 0;
    double b = 0;
    std::tie(a, b) = get_last_pair(operands);
    operands.push(b / a);
}

void Calculator::multiplication(std::stack<double>& operands)
{
    double a = 0;
    double b = 0;
    std::tie(a, b) = get_last_pair(operands);
    operands.push(a * b);
}
