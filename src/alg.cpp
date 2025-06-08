// Copyright 2022 NNTU-CS
#include <algorithm>
#include <iostream>
#include "tree.h"

PMTree::Node::Node(char val) : value(val) {}
PMTree::Node::~Node() {
    for (auto child : children) delete child;
}

PMTree::PMTree(const std::vector<char>& elems) {
    root = new Node(0);
    build(root, elems);
}

PMTree::~PMTree() {
    clear(root);
}

void PMTree::clear(Node* node) {
    if (!node) return;
    for (auto child : node->children)
        clear(child);
    delete node;
}

void PMTree::build(Node* node, const std::vector<char>& remaining) {
    if (remaining.empty()) return;

    std::vector<char> sorted = remaining;
    std::sort(sorted.begin(), sorted.end());

    for (size_t i = 0; i < sorted.size(); ++i) {
        char ch = sorted[i];
        Node* child = new Node(ch);
        node->children.push_back(child);

        std::vector<char> next_remaining = sorted;
        next_remaining.erase(next_remaining.begin() + i);
        build(child, next_remaining);
    }
}

PMTree::Node* PMTree::getRoot() const {
    return root;
}

void collectPerms(PMTree::Node* node, std::vector<char>& path, std::vector<std::vector<char>>& result) {
    if (node->value != 0) path.push_back(node->value);

    if (node->children.empty()) {
        result.push_back(path);
    } else {
        for (auto child : node->children)
            collectPerms(child, path, result);
    }

    if (!path.empty()) path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    collectPerms(tree.getRoot(), path, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<std::vector<char>> all = getAllPerms(tree);
    if (num < 1 || num > (int)all.size()) return {};
    return all[num - 1];
}

int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    PMTree::Node* current = tree.getRoot();
    --num;

    std::vector<char> used;
    std::vector<char> alphabet;

    for (auto child : current->children)
        alphabet.push_back(child->value);

    std::sort(alphabet.begin(), alphabet.end());

    while (!alphabet.empty()) {
        int block_size = factorial(alphabet.size() - 1);
        int index = num / block_size;
        if (index >= (int)alphabet.size()) return {};

        char ch = alphabet[index];
        result.push_back(ch);
        alphabet.erase(alphabet.begin() + index);
        num %= block_size;
    }

    return result;
}
