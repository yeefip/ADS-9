// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class TreeNode {
 public:
  char value;
  std::vector<std::shared_ptr<TreeNode>> children;

  explicit TreeNode(char val) : value(val) {}
};

class PMTree {
 private:
  std::shared_ptr<TreeNode> root;
  std::vector<char> original;

  void build(std::shared_ptr<TreeNode> node, std::vector<char> remaining);
  void collectPerms(std::shared_ptr<TreeNode> node,
                    std::vector<char>& path,
                    std::vector<std::vector<char>>& result);

 public:
  explicit PMTree(const std::vector<char>& in);

  std::vector<std::vector<char>> getAllPerms();
  std::shared_ptr<TreeNode> getRoot() const;
  const std::vector<char>& getOriginal() const;
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);
int factorial(int n);

#endif  // INCLUDE_TREE_H_
