// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include "tree.h"

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
  for (int n = 2; n <= 8; ++n) {
    std::vector<char> chars;
    for (int i = 0; i < n; ++i) chars.push_back('a' + i);
    PMTree t(chars);
    int maxPerms = factorial(n);
    unsigned int seed = static_cast<unsigned int>(
    std::chrono::system_clock::now().time_since_epoch().count());
    int randNum = rand_r(&seed) % maxPerms;

    auto start1 = std::chrono::high_resolution_clock::now();
    auto p1 = getPerm1(t, randNum);
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    auto p2 = getPerm2(t, randNum);
    auto end2 = std::chrono::high_resolution_clock::now();

    auto dur1 = std::chrono::duration_cast<std::chrono::microseconds>(
    end1 - start1)
    .count();
    auto dur2 = std::chrono::duration_cast<std::chrono::microseconds>(
    end2 - start2)
    .count();

    std::cout << "n = " << n
          << " | getPerm1 = " << dur1 << " мкс"
          << " | getPerm2 = " << dur2 << " мкс\n";
  }

  return 0;
}
