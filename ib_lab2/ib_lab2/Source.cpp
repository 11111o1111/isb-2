#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdint.h>


std::vector<int> PRNG() {
    std::vector<int> result;
    std::srand(5334);

    for (int i = 0; i < 128; ++i) {
        result.push_back((std::rand() % 5235) % 2);
    }

    return result;
}


double test_1(std::vector<int> obj) {
    double Sn;
    double sum = 0;
    for (int i = 0; i < obj.size(); ++i) {
        if (obj[i]) {
            ++sum;
        }
        else {
            --sum;
        }
    }
    Sn = 1 / (sqrt(obj.size())) * sum;
    return std::erfc(Sn / sqrt(2));

}


double test_2(std::vector<int> obj) {
    double e = 0;
    double sum = 0;
    for (int i = 0; i < obj.size(); ++i) {
        sum += obj[i];
    }
    e = (1.0 / obj.size()) * sum;

    if ((e - 0.5) >= (2 / sqrt(obj.size()))) {
        return 0;
    }
    int Vn = 0;
    for (int i = 0; i < obj.size() - 1; ++i) {
        if (obj[i] != obj[i + 1]) {
            ++Vn;
        }
    }
    return std::erfc((abs(Vn - 2.0 * obj.size() * e * (1 - e))) / (2 * sqrt(2 * obj.size()) * e * (1 - e)));
}


template<typename Iterator>
int stats(Iterator begin, Iterator end) {
    int max_lenght = 0, lenght;
    auto i = begin;
    while (i < end) {
        int count = 0;
        lenght = 0;
        while (*i && i != end) {
            ++lenght;
            ++count;
            ++i;
        }
        if (lenght > max_lenght) {
            max_lenght = lenght;
        }
        if (count == 0) ++i;
    }

    return max_lenght;
}


double test_3(std::vector<int> obj) {
    std::vector<int> v = { 0, 0, 0, 0 };
    std::vector<double> p = { 0.2148, 0.3762, 0.2305, 0.1875 };
    for (auto i = obj.begin(); i != obj.end(); i += 8) {
        int vi = stats(i, i + 7);
        if (vi <= 1) ++v[0];
        if (vi == 2) ++v[1];
        if (vi == 3) ++v[2];
        if (vi >= 4) ++v[3];
    }

    double x = 0;
    for (int i = 0; i < 4; ++i) {
        x += pow(v[i] - 16 * p[i], 2) / (16 * p[i]);
    }

    return x / 2;
}


int main() {
    std::vector<int> n;
    n = PRNG();
    for (auto& i : n) {
        std::cout << i;
    }
    std::cout << "\n\n" << test_1(n) << "\n" << test_2(n) << "\n" << test_3(n);
    return 0;
}

