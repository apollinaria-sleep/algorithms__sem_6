#ifndef UNTITLED5_RATIONAL_H
#define UNTITLED5_RATIONAL_H

#include <iostream>
#include <exception>
#include <string>
#include <string_view>


class NullDenominator : public std::exception {
public:
    explicit NullDenominator(std::string_view error) : m_error{error} {}
    const char* what() const noexcept override {
        return m_error.c_str();;
    }
private:
    std::string m_error;
};

class Rational {
public:
    Rational() = default;
    Rational(const Rational& other) = default;
    Rational(Rational&& other) = default;
    Rational(const int num, const int den = 1) : numerator(num), denominator(den) {
        if (!den) throw NullDenominator("Знаменатель не может быть нулем\n");
        normalize();
    }

    ~Rational() = default;

    int RationalNum() const;
    int RationalDen() const;

    Rational operator-() const;

    Rational& operator+=(const Rational& right);
    Rational& operator-=(const Rational& right);
    Rational& operator*=(const Rational& right);
    Rational& operator/=(const Rational& right);

    bool operator==(const Rational& right) const;
    bool operator<(const Rational& right) const;

    Rational& operator=(const Rational& right) = default;

    explicit operator double() const;

private:
    int Gcd(int a, int b) const;
    void normalize();

private:
    int numerator = 0;
    int denominator = 1;
};

Rational operator+(const Rational& left, const Rational& right);
Rational operator-(const Rational& left, const Rational& right);
Rational operator*(const Rational& left, const Rational& right);
Rational operator/(const Rational& left, const Rational& right);

bool operator!=(const Rational& left, const Rational& right);
bool operator>(const Rational& left, const Rational& right);
bool operator<=(const Rational& left, const Rational& right);
bool operator>=(const Rational& left, const Rational& right);

std::ostream& operator<<(std::ostream& ostr, const Rational& r);
std::istream& operator>>(std::istream& istr, Rational& r);


#endif //UNTITLED5_RATIONAL_H
