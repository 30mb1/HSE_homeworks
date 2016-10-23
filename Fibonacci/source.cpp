#include<algorithm>
#include<iomanip>
#include<iostream>
#include<string>
#include<vector>
const int base = 1000 * 1000 * 1000;

int hesh(const std::vector<int>& vec) {
    int size = 0;
    int number = vec[vec.size() - 1];
    while (number) {
        number = number / 10;
        size++;
    }
    return (size + (vec.size() - 1) * 9);
}

void plus(std::vector<int>& summ, std::vector<int>& bvec) {
    int carry = 0;
    for (size_t i = 0; i < bvec.size() || carry; ++i) {
        if (i == summ.size())
            summ.push_back(0);
        summ[i] += carry + (i < bvec.size() ? bvec[i] : 0);
        carry = summ[i] >= base;
        if (carry) summ[i] -= base;
    }
    while (summ.size() > 1 && summ.back() == 0)
        summ.pop_back();
}

int main() {
    int numb;
    std::cin >> numb;
    std::vector<int> afib = { 1 };
    std::vector<int> bfib = { 1 };
    std::vector<std::vector<std::vector<int>>> allfib(5005);
    allfib[hesh(bfib) - 1].push_back(bfib);
    allfib[hesh(afib) - 1].push_back(afib);
    while (bfib.size() < 557) {
        plus(afib, bfib);
        plus(bfib, afib);
        allfib[hesh(afib) - 1].push_back(afib);
        allfib[hesh(bfib) - 1].push_back(bfib);
    }
    for (int ix = 0; ix < numb; ++ix) {
        std::string strnumb;
        std::cin >> strnumb;
        std::vector<int> cfib;
        for (int ii = static_cast<int>(strnumb.length()); ii > 0; ii -= 9)
            if (ii < 9) {
                cfib.push_back(atoi(strnumb.substr(0, ii).c_str()));
            } else {
                cfib.push_back(atoi(strnumb.substr(ii - 9, 9).c_str()));
            }
            bool fib = false;
            for (auto x : allfib[hesh(cfib) - 1]) {
                if (cfib == x) {
                    fib = true;
                    break;
                }
            }
            if (fib) {
                std::cout << "Yes" << std::endl;
            } else {
                std::cout << "No" << std::endl;
            }
    }
    system("pause");
    return 0;
}
