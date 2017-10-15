#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "LexicalAnalyzer.h"
#include "Calculator.h"


std::tuple<double, bool> calc_string(std::string str)
{
    LexicalAnalyzer analyzer;
    Calculator calc;
    analyzer.parse_string(str);
    auto tokens = analyzer.get_tokens();
    return calc.calculate(tokens);
}

TEST_CASE( "Complex braces" ) {
    REQUIRE( (calc_string("(((((0 - 1)))))") == std::make_tuple(-1, true)) );
    REQUIRE( (calc_string("((2) - (2))") == std::make_tuple(0, true)) );
    REQUIRE( (calc_string("(2) - (2)") != std::make_tuple(3, false)) );
    REQUIRE( (calc_string("(-15) - (-2) -16") == std::make_tuple(-29, true)) );
}


TEST_CASE( "Comlex expression" ) {
    REQUIRE( (calc_string("0") == std::make_tuple(0, true)) );
    REQUIRE( (calc_string("-1 + 5 - 3") == std::make_tuple(1, true)) );
    REQUIRE( (calc_string("1.1 + 2.1") == std::make_tuple(3.2, true)) );
    REQUIRE( (calc_string("-10 + (8 * 2.5) - (3 / 1,5)") == std::make_tuple(8, true)) );
    REQUIRE( (calc_string("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)") == std::make_tuple(11, true)) );
}

TEST_CASE( "Binary summation" ) {
    REQUIRE( (calc_string("0 + 1") == std::make_tuple(1, true)) );
    REQUIRE( (calc_string("2 + 2") == std::make_tuple(4, true)) );
    REQUIRE( (calc_string("2 + 2") != std::make_tuple(3, false)) );
    REQUIRE( (calc_string("-15 + 1") == std::make_tuple(-14, true)) );
}

TEST_CASE( "Binary subtraction" ) {
    REQUIRE( (calc_string("0 - 1") == std::make_tuple(-1, true)) );
    REQUIRE( (calc_string("2 - 2") == std::make_tuple(0, true)) );
    REQUIRE( (calc_string("2 - 2") != std::make_tuple(3, false)) );
    REQUIRE( (calc_string("-15 - -16") == std::make_tuple(1, true)) );
}

TEST_CASE( "Binary division" ) {
    REQUIRE( (calc_string("1 / 1") == std::make_tuple(1, true)) );
    REQUIRE( (calc_string("2 / 1") == std::make_tuple(2, true)) );
    REQUIRE( (calc_string("1 / 2") == std::make_tuple(0.5, true)) );
    REQUIRE( (calc_string("-1 / -1") == std::make_tuple(1, true)) );
}

TEST_CASE( "Binary multiplication" ) {
    REQUIRE( (calc_string("0 * 1") == std::make_tuple(0, true)) );
    REQUIRE( (calc_string("2 * 2") == std::make_tuple(4, true)) );
    REQUIRE( (calc_string("-2 * -2") != std::make_tuple(4, false)) );
    REQUIRE( (calc_string("0.5 * 2") == std::make_tuple(1, true)) );
}
