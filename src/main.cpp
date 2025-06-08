// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

static int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

void printVector(const std::vector<char>& v) {
    for (char c : v) std::cout << c;
    std::cout << '\n';
}

int main() {
    std::vector<char> input = {'1', '2', '3'};
    PMTree tree(input);

    std::cout << "Все перестановки:\n";
    auto perms = getAllPerms(tree);
    for (const auto& p : perms) printVector(p);

    std::cout << "\nПерестановка №1 (getPerm1): ";
    printVector(getPerm1(tree, 1));

    std::cout << "Перестановка №2 (getPerm2): ";
    printVector(getPerm2(tree, 2));

    std::cout << "\n=== Эксперимент ===\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int n = 2; n <= 8; ++n) {
        std::vector<char> chars;
        for (int i = 0; i < n; ++i) {
            chars.push_back('a' + i);
        }
        PMTree t(chars);

        int maxPerms = factorial(n);
        std::uniform_int_distribution<> dist(1, maxPerms);
        int randNum = dist(gen);

        auto start1 = std::chrono::high_resolution_clock::now();
        getPerm1(t, randNum);
        auto end1 = std::chrono::high_resolution_clock::now();

        auto start2 = std::chrono::high_resolution_clock::now();
        getPerm2(t, randNum);
        auto end2 = std::chrono::high_resolution_clock::now();

        auto dur1 = std::chrono::duration_cast<
                        std::chrono::microseconds>(end1 - start1)
                        .count();
        auto dur2 = std::chrono::duration_cast<
                        std::chrono::microseconds>(end2 - start2)
                        .count();

        std::cout
            << "n = " << n
            << " | getPerm1 = " << dur1 << " мкс"
            << " | getPerm2 = " << dur2 << " мкс\n";
    }
    return 0;
}
