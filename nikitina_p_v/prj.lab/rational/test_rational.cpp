#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rational/rational.h>


TEST_CASE("init") {
    Rational default_num;
    CHECK(default_num.num() == 0);
    CHECK(default_num.denum() == 1);

    Rational null_num(0, 2);
    CHECK(null_num.num() == 0);
    CHECK(null_num.denum() == 1);

    int num = rand() % 1000;
    int den = 1 + rand() % 1000;
    Rational number(num, den);
    CHECK(number.num() == num);
    CHECK(number.denum() == den);

    Rational same = number;
    CHECK(same.num() == num);
    CHECK(same.denum() == den);

    int normalize = 2 + rand() % 1000;
    Rational number_(num * normalize, den * normalize);
    CHECK(number.num() == number_.num());
    CHECK(number.denum() == number_.denum());

    Rational negative(num, (den > 0 ? (-den) : den));
    CHECK(negative.denum() > 0);

    bool error = false;
    try {
        Rational null_den(num, 0);
    } catch (Rational::NullDenominator& e) {
        error = true;
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

    bool error = false;
    try {
        left /= Rational(0, b);
    } catch (Rational::NullDenominator& e) {
        error = true;
    }
    CHECK(error);
}
