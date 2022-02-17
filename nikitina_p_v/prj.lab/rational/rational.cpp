#include "rational.h"
#include <iostream>


int Rational::RationalNum() const {
    return numerator;
}

int Rational::RationalDen() const {
    return denominator;
}

Rational Rational::operator-() const {
    return Rational(-numerator, denominator);
}

Rational& Rational::operator+=(const Rational& right) {
    numerator = numerator * right.denominator + right.numerator * denominator;
    denominator *= right.denominator;
    normalize();
    return *this;
};

Rational& Rational::operator-=(const Rational& right) {
    *this += (- right);
    return *this;
}

Rational& Rational::operator*=(const Rational& right) {
    numerator *= right.numerator;
    denominator *= right.denominator;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& right) {
    if (!right.numerator) throw NullDenominator("Деление на нуль");
    *this *= Rational(right.denominator, right.numerator);
    return *this;
}

bool Rational::operator==(const Rational& right) const {
    return (numerator == right.numerator && denominator == right.denominator);
}

bool Rational::operator<(const Rational& right) const {
    return numerator * right.denominator < denominator * right.numerator;
}

Rational::operator double() const {
    return 1.0 * this->numerator / this->denominator;
}

int Rational::Gcd(int a, int b) const {
    while (a && b) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }
    return a + b;
}

void Rational::normalize() {
    int gcd = Gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;

    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

Rational operator+(const Rational& left, const Rational& right) {
    return Rational(left) += right;
}

Rational operator-(const Rational& left, const Rational& right) {
    return Rational(left) -= right;
}

Rational operator*(const Rational& left, const Rational& right) {
    return Rational(left) *= right;
}

Rational operator/(const Rational& left, const Rational& right) {
    return Rational(left) /= right;
}

bool operator!=(const Rational& left, const Rational& right) {
    return !(left == right);
}

bool operator>(const Rational& left, const Rational& right) {
    return right < left;
}

bool operator<=(const Rational& left, const Rational& right) {
    return (left == right) || (left < right);
}

bool operator>=(const Rational& left, const Rational& right) {
    return (left == right) || (left > right);
}

std::ostream& operator<<(std::ostream& ostr, const Rational& r) {
    ostr << r.RationalNum() << '/' << r.RationalDen();
    return ostr;
}

std::istream& operator>>(std::istream& istr, Rational& r) {
    int num, den;
    istr >> num >> den;
    r = Rational(num, den);
    return istr;
}
