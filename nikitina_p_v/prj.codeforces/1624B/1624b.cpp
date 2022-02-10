/*
Простая задача: https://codeforces.com/problemset/problem/1624/B
Примерное время выполнения: 30 минут
*/
#include <iostream>

bool IsInt(double number) {
    return int(number) == number;
}

bool IsArithmeticProgression(double a, double b, double c) {
    double m_a = (b - (c - b)) / a;
    double m_b = (c - (c - a) / 2) / b;
    double m_c = (b + (b - a)) / c;
    if ((m_a >= 1 && IsInt(m_a)) || (m_b >= 1 && IsInt(m_b)) || (m_c >= 1 && IsInt(m_c))) {
        return true;
    }
    return false;
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        double a, b, c;
        std::cin >> a >> b >> c;

        std::cout << (IsArithmeticProgression(a, b, c) ? "YES\n" : "NO\n");
    }

    return 0;
}
