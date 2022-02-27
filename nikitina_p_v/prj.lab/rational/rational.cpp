#include "rational.h"
#include <iostream>


Rational::Rational(const int num, const int denum = 1) : numerator(num), denominator(denum) {
    if (!denum) throw NullDenominator("Знаменатель не может быть нулем\n");
    normalize();
}

int Rational::num() const {
    return numerator;
}

int Rational::denum() const {
    return denominator;
}

Rational Rational::operator-() const {
    return Rational(-numerator, denominator);
}

Rational& Rational::operator+=(const Rational& rhs) {
    numerator = numerator * rhs.denominator + rhs.numerator * denominator;
    denominator *= rhs.denominator;
    normalize();
    return *this;
};

Rational& Rational::operator-=(const Rational& rhs) {
    *this += (-rhs);
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (!rhs.numerator) throw NullDenominator("Деление на нуль");
    *this *= Rational(rhs.denominator, rhs.numerator);
    return *this;
}

bool Rational::operator==(const Rational& rhs) const {
    return (numerator == rhs.numerator && denominator == rhs.denominator);
}

bool Rational::operator!=(const Rational& rhs) const {
    return !(*this == rhs);
}

bool Rational::operator<(const Rational& rhs) const {
    return numerator * rhs.denominator < denominator * rhs.numerator;
}

bool Rational::operator<=(const Rational& rhs) const {
    return (*this == rhs) || (*this < rhs);
}

bool Rational::operator>(const Rational& rhs) const {
    return rhs < *this;
}

bool Rational::operator>=(const Rational& rhs) const{
    return (*this == rhs) || (*this > rhs);
}

Rational::operator double() const {
    return 1.0 * this->numerator / this->denominator;
}

std::istream& Rational::read_from(std::istream& istrm) {
    int num, denum;
    char c;
    istrm >> std::noskipws;
    istrm >> num >> c >> denum;
    istrm >> std::skipws;
    if (c != '/') throw;
    if (denum <= 0) throw NullDenominator("Некорректный знаменатель");
    *this = Rational(num, denum);
    return istrm;
}

std::ostream& Rational::write_to(std::ostream& ostrm) const {
    ostrm << numerator << '/' << denominator;
    return ostrm;
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

Rational operator+(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs) += rhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs) -= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs) *= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs) /= rhs;
}

std::istream& operator>>(std::istream& istrm, Rational& r) {
    return r.read_from(istrm);
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& r) {
    return r.write_to(ostrm);
}
