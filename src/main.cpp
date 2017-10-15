#include <iostream>
#include "LexicalAnalyzer.h"
#include "Token.h"
#include "Calculator.h"

int main()
{
    std::string data = "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)";
    
    LexicalAnalyzer analyzer;
    bool parse_success = analyzer.parse_string(data);
    if (!parse_success) {
        std::cout << "\nbad_string\n";
        return 0;
    }
    std::vector<Token> tokens = analyzer.get_tokens();

    Calculator calc;
    double result;
    bool success;
    std::tie(result, success) = calc.calculate(tokens);

    if (success) {
        std::cout << result << std::endl;
    } else {
        std::cout << "\nbad_string\n";
    }
}
