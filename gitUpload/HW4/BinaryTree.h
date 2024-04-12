#pragma once
#include <iostream>

struct TreeNode {
    int value;
    TreeNode *left, *right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroyTree(root);
    }

    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    int insert(int value) {
        return insertRecursive(root, value);
    }

    int find(int value) {
        return findRecursive(root, value);
    }

    int remove(int value) {
        bool found = false;
        int count = 0;
        removeRecursive(root, value, found, count);
        return count;
    }

    void print() const {
        printInOrder(root);
        std::cout << std::endl;
    }

private:
    int insertRecursive(TreeNode*& node, int value, int depth = 1) {
        if (!node) {
            node = new TreeNode(value);
            return depth;
        }
        if (value < node->value)
            return insertRecursive(node->left, value, depth + 1);
        else
            return insertRecursive(node->right, value, depth + 1);
    }

    int findRecursive(TreeNode* node, int value, int depth = 1) {
        if (!node) return 0;
        if (node->value == value) return depth;
        if (value < node->value)
            return findRecursive(node->left, value, depth + 1);
        else
            return findRecursive(node->right, value, depth + 1);
    }

    void removeRecursive(TreeNode*& node, int value, bool& found, int& count, int depth = 1) {
        if (!node) return;
        count = depth;
        if (value < node->value) {
            removeRecursive(node->left, value, found, count, depth + 1);
        } else if (value > node->value) {
            removeRecursive(node->right, value, found, count, depth + 1);
        } else {
            found = true;
            if (!node->left || !node->right) {
                TreeNode* temp = node->left ? node->left : node->right;
                delete node;
                node = temp;
            } else {
                TreeNode* temp = minValueNode(node->right);
                node->value = temp->value;
                removeRecursive(node->right, temp->value, found, count, depth + 1);
            }
        }
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void printInOrder(TreeNode* node) const {
        if (!node) return;
        printInOrder(node->left);
        std::cout << node->value << " ";
        printInOrder(node->right);
    }
};
