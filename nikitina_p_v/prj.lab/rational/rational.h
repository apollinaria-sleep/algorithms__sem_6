#pragma once
#ifndef RATIONAL_RATIONAL_HEAD_H_2022_03_03
#define RATIONAL_RATIONAL_HEAD_H_2022_03_03

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
    Rational(const Rational&) = default;
    Rational(Rational&&) = default;
    Rational(const int num);
    Rational(const int num, const int denum);
    Rational& operator=(const Rational&) = default;
    Rational& operator=(Rational&&) noexcept = default;
    ~Rational() = default;

    int num() const;
    int denum() const;

    Rational operator-() const;

    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;

    explicit operator double() const;

    std::istream& read_from(std::istream& istrm);
    std::ostream& write_to(std::ostream& ostrm) const;
private:
    int Gcd(int a, int b) const;
    void normalize();

private:
    int numerator = 0;
    int denominator = 1;
};

std::istream& operator>>(std::istream& istrm, Rational& r);
std::ostream& operator<<(std::ostream& ostrm, const Rational& r);

Rational operator+(const Rational& left, const Rational& right);
Rational operator-(const Rational& left, const Rational& right);
Rational operator*(const Rational& left, const Rational& right);
Rational operator/(const Rational& left, const Rational& right);

#endif#pragma once
#ifndef RATIONAL_RATIONAL_HEAD_H_2022_03_03
#define RATIONAL_RATIONAL_HEAD_H_2022_03_03

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
    Rational(const Rational&) = default;
    Rational(Rational&&) = default;
    Rational(const int num);
    Rational(const int num, const int denum);
    Rational& operator=(const Rational&) = default;
    Rational& operator=(Rational&&) noexcept = default;
    ~Rational() = default;

    int num() const;
    int denum() const;

    Rational operator-() const;

    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;

    explicit operator double() const;

    std::istream& read_from(std::istream& istrm);
    std::ostream& write_to(std::ostream& ostrm) const;
private:
    int Gcd(int a, int b) const;
    void normalize();

private:
    int numerator = 0;
    int denominator = 1;
};

std::istream& operator>>(std::istream& istrm, Rational& r);
std::ostream& operator<<(std::ostream& ostrm, const Rational& r);

Rational operator+(const Rational& left, const Rational& right);
Rational operator-(const Rational& left, const Rational& right);
Rational operator*(const Rational& left, const Rational& right);
Rational operator/(const Rational& left, const Rational& right);

#endif
