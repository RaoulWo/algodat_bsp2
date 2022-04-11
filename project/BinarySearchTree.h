//
// Created by Raoul on 07.04.2022.
//

#ifndef PROJECT_BINARYSEARCHTREE_H
#define PROJECT_BINARYSEARCHTREE_H
#include <string>

class Node {
public:
// #### Constructor ####
    Node(int k);
// #### Public Attributes ####
    int key;
    Node* left;
    Node* right;
};

class BinarySearchTree {
public:
// #### Constructor ####
    BinarySearchTree();
// #### Public Attributes ####
    Node* root; // points to the root of the binary search-tree
    bool avl; // dictates whether the tree is an avl-tree or not
// #### Public Methods ####
    int Size(Node* tree) const;
    int Height(Node* tree) const;
    int Balance(Node* tree) const;
    void LogBalance(Node* tree);
    void Add(Node* tree, int key);
    bool Search(Node* tree, int key) const;
    int FindMin() const;
    int FindMax() const;
    int FindMinRec(Node* tree) const;
    int FindMaxRec(Node* tree) const;
    int Sum(Node* tree) const;
    double Avg(Node* tree) const;
    void Create(const std::string& file);
    void Log(Node* tree) const;
    void LogPreorder(Node* tree) const;
    void LogInorder(Node* tree) const;
    void LogPostorder(Node* tree) const;
    void Stats(Node* tree) const;
};


#endif //PROJECT_BINARYSEARCHTREE_H
