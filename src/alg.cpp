// Copyright 2022 NNTU-CS
#include <vector>
#include <memory>
#include <stdexcept>
#include <set>
#include <algorithm>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& in) {
  original = in;
  std::sort(original.begin(), original.end());
  root = std::make_shared<TreeNode>(0);
  build(root, original);
}

std::shared_ptr<TreeNode> PMTree::getRoot() const {
  return root;
}

const std::vector<char>& PMTree::getOriginal() const {
  return original;
}

void PMTree::build(std::shared_ptr<TreeNode> node, std::vector<char> remaining) {
  if (remaining.empty()) return;

  std::set<char> used;
  for (size_t i = 0; i < remaining.size(); ++i) {
    char ch = remaining[i];
    if (used.count(ch)) continue;
    used.insert(ch);

    auto child = std::make_shared<TreeNode>(ch);
    node->children.push_back(child);

    std::vector<char> nextRemaining = remaining;
    nextRemaining.erase(nextRemaining.begin() + static_cast<int>(i));

    build(child, nextRemaining);
  }
}

void PMTree::collectPerms(std::shared_ptr<TreeNode> node,
                          std::vector<char>& path,
                          std::vector<std::vector<char>>& result) {
  if (node->value != 0) path.push_back(node->value);

  if (node->children.empty()) {
    result.push_back(path);
  } else {
    for (auto& child : node->children) {
      collectPerms(child, path, result);
    }
  }

  if (node->value != 0) path.pop_back();
}

std::vector<std::vector<char>> PMTree::getAllPerms() {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  collectPerms(root, path, result);
  return result;
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto perms = tree.getAllPerms();
  if (num < 0 || num >= static_cast<int>(perms.size()))
    throw std::out_of_range("Invalid permutation number");
  return perms[num];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;
  std::vector<char> original = tree.getOriginal();
  int n = static_cast<int>(original.size());

  std::vector<int> fact(n);
  fact[0] = 1;
  for (int i = 1; i < n; ++i) {
    fact[i] = fact[i - 1] * i;
  }

  if (num < 0 || num >= fact[n - 1] * n)
    throw std::out_of_range("Invalid permutation number");

  std::sort(original.begin(), original.end());
  std::vector<bool> used(n, false);

  for (int i = n - 1; i >= 0; --i) {
    int f = fact[i];
    int index = num / f;
    num %= f;

    int count = 0;
    for (int j = 0; j < n; ++j) {
      if (!used[j]) {
        if (count == index) {
          result.push_back(original[j]);
          used[j] = true;
          break;
        }
        ++count;
      }
    }
  }

  return result;
}

int factorial(int n) {
  return (n <= 1) ? 1 : n * factorial(n - 1);
}
