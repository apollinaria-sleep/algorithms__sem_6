#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.cpp"


TEST_CASE("init") {
    int num = rand() % 1000;
    int den = 1 + rand() % 1000;
    Rational number(num, den);
    CHECK(number.RationalNum() == num);
    CHECK(number.RationalDen() == den);

    Rational same = number;
    CHECK(number.RationalNum() == num);
    CHECK(number.RationalDen() == den);

    int normalize = 1 + rand() % 1000;
    Rational number_(num * normalize, den * normalize);
    CHECK(number.RationalNum() == number_.RationalNum());
    CHECK(number.RationalDen() == number_.RationalDen());

    Rational negative(num, (den > 0 ? (-den) : den));
    CHECK(negative.RationalDen() > 0);

    bool error = true;
    try {
        Rational null_den(num, 0);
    } catch (NullDenominator& e) {
        error = false;
    }
    CHECK(error);
}

TEST_CASE("comparison operations") {
    int num = rand() % 1000;
    int den = 1 + rand() % 1000;
    Rational min(num, den);
    Rational equal_min = min;
    Rational max(num + 25, den);

    CHECK(min == equal_min);
    CHECK(min != max);
    CHECK(min < max);
    CHECK(max > min);
    CHECK(min <= max);
    CHECK(max >= min);
}


TEST_CASE("arithmetic operations") {
    int a = rand() % 1000;
    int b = rand() % 1000 + 1;
    int c = rand() % 1000 + 1;
    int d = rand() % 1000 + 1;
    Rational left(a, b);
    Rational right(c, d);

    CHECK(left + right == Rational(a * d + b * c, b * d));
    CHECK(left * right == Rational(a * c, b * d));
    CHECK(left - right == Rational(a * d - b * c, b * d));
    CHECK(left / right == Rational(a * d, b * c));

    bool error = true;
    try {
        left /= Rational(0, b);
    } catch (NullDenominator& e) {
        error = false;
    }
    CHECK(error);
}