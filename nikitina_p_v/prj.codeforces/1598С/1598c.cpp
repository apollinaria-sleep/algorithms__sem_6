/*
Средняя задача: https://codeforces.com/problemset/problem/1598/C
Примерное время выполнения: 1 час 10 минут
*/
#include <iostream>
#include <vector>
#include <map>


int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> numbers(n);
        std::map<int, int> count;
        
        long long sum = 0;
        for (int& number : numbers) {
            std::cin >> number;

            sum += number;
            count[number] += 1;
        }

        if (2 * sum % n) {
            std::cout << 0 << '\n';
            continue;
        }

        long long answer = 0;
        for (int& number : numbers) {
            long long need_number = 2 * sum / n - number;
            if (count.count(need_number)) {
                answer += count[need_number];
            }
            if (need_number == number) {
                answer--;
            }
        }

        std::cout << answer / 2 << '\n';
    }

    return 0;
}
