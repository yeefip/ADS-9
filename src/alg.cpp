// Copyright 2022 NNTU-CS
#include <vector>
#include <memory>
#include <stdexcept>
#include <set>
#include <algorithm>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& in) : original(in) {
  std::sort(original.begin(), original.end());
  root = std::make_shared<TreeNode>('\0');
  build(root, original);
}

std::shared_ptr<TreeNode> PMTree::getRoot() const {
  return root;
}

const std::vector<char>& PMTree::getOriginal() const {
  return original;
}

void PMTree::build(std::shared_ptr<TreeNode> node,
                  std::vector<char> remaining) {
  if (remaining.empty()) return;

  std::set<char> used;
  for (size_t i = 0; i < remaining.size(); ++i) {
    char ch = remaining[i];
    if (used.count(ch)) continue;
    used.insert(ch);

    auto child = std::make_shared<TreeNode>(ch);
    node->children.push_back(child);

    std::vector<char> nextRemaining(remaining);
    nextRemaining.erase(nextRemaining.begin() + i);
    build(child, nextRemaining);
  }
}

void PMTree::collectPerms(std::shared_ptr<TreeNode> node,
                         std::vector<char>& path,
                         std::vector<std::vector<char>>& result) {
  if (node->value != '\0') {
    path.push_back(node->value);
  }

  if (node->children.empty()) {
    result.push_back(path);
  } else {
    for (auto& child : node->children) {
      collectPerms(child, path, result);
    }
  }

  if (node->value != '\0') {
    path.pop_back();
  }
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
  int total = perms.size();
  if (num < 1 || num > total) {
    return{};
  }
  return perms[num-1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> original = tree.getOriginal();
  int n = original.size();
  if (n == 0) return {};

  int total_perms = 1;
  for (int i = 2; i <= n; ++i) {
    total_perms *= i;
  }

  if (num < 1 || num > total_perms) {
    return{};
  }
  num--;

  std::vector<char> result;
  std::vector<char> elements = original;

  for (int i = n; i > 0; --i) {
    total_perms /= i;
    int index = num / total_perms;
    num %= total_perms;

    result.push_back(elements[index]);
    elements.erase(elements.begin() + index);
  }

  return result;
}

int factorial(int n) {
  if (n <= 1) return 1;
  return n * factorial(n-1);
}
