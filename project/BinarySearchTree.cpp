//
// Created by Christian on 07.04.2022.
//

#include <cassert>
#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"

// Constructor initializes Node with key = k, pointers left,right = nullptr
Node::Node(int k)
    : key(k), left(nullptr), right(nullptr)
{
}

// Constructor initializes BST with root = nullptr and avl = true
BinarySearchTree::BinarySearchTree()
    : root(nullptr), avl(true)
{
}

int BinarySearchTree::Size(Node *tree) const {
    if (tree == nullptr) // if node is nullptr return 0
        return 0;
    // recursively add 1 + the sizes of the left and right subtrees
    return 1 + Size(tree->left) + Size(tree->right);
}

// searches tree for the key, returns true if found, false if not found
bool BinarySearchTree::Search(Node *tree, int key) const {
    if (tree == nullptr) // if root is null, key is not in tree
        return false;
    if (key == tree->key) // key is found
        return true;
    else if (key < tree->key) // recursively look at left subtree if key < tree->key
        return Search(tree->left, key);
    else // recursively look at right subtree if key > tree->key
        return Search(tree->right, key);
}

void BinarySearchTree::Add(Node* tree, int key) {
    if (Size(root) == 0) { // if tree is empty, add node as root node
        Node* newNode = new Node(key);
        root = newNode;
        return;
    }
    if (Search(tree, key)) // search the tree for the key, if it exists exit the function
        return;
    if (key < tree->key) { // new entry smaller than key
        if (tree->left == nullptr) { // enter node if left child is nullptr
            Node* newNode = new Node(key);
            tree->left = newNode;
            return;
        }
        else { // else recursively call Add for the left subtree
            Add(tree->left, key);
        }
    }
    if (key > tree->key) { // new entry greater than key
        if (tree->right == nullptr) { // enter node if right child is nullptr
            Node* newNode = new Node(key);
            tree->right = newNode;
            return;
        }
        else { // else recursively call Add for the right subtree
            Add(tree->right, key);
        }
    }
}

// **** Iterative FindMin / FindMax ****
int BinarySearchTree::FindMin() const {
    assert(root != nullptr); // assert that tree is not empty
    Node* tmp = root;
    while (tmp->left != nullptr) {
        tmp = tmp->left;
    }
    return tmp->key;
}

int BinarySearchTree::FindMax() const {
    assert(root != nullptr); // assert that tree is not empty
    Node* tmp = root;
    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    return tmp->key;
}

// **** Recursive FindMin / FindMax ****
int BinarySearchTree::FindMinRec(Node* tree) const {
    if (tree == nullptr)
        return INT_MAX;
    int tmp = tree->key;
    return tmp < FindMinRec(tree->left) ? tmp : FindMinRec(tree->left);
}

int BinarySearchTree::FindMaxRec(Node* tree) const {
    if (tree == nullptr)
        return INT_MIN;
    int tmp = tree->key;
    return tmp > FindMaxRec(tree->right) ? tmp : FindMaxRec(tree->right);
}

int BinarySearchTree::Sum(Node *tree) const {
    if (tree == nullptr) // if node is nullptr return 0 to the sum
        return 0;
    // recursively add key of current node to the sum of left and right subtrees
    return tree->key + Sum(tree->left) + Sum(tree->right);
}

// takes a filepath as parameter, opens ifstream and adds a new node to the bst for every line in the file
void BinarySearchTree::Create(const std::string& filepath) {
    std::ifstream file;
    file.open(filepath);
    if (!file.is_open()) { // throw an exception if file cannot be opened
        std::cout << "**** ERROR, the file could not be read! ****" << '\n';
        exit(-1);
    }
    std::string num;
    while(std::getline(file,num)) {
        Add(root, stoi(num)); // call Add function for every line
        num.clear(); // clear the string after every iteration
    }
}

void BinarySearchTree::LogPreorder(Node *tree) const { // prints keys in preorder
    if (tree == nullptr)
        return;
    std::cout << tree->key << ' ';
    LogPreorder(tree->left);
    LogPreorder(tree->right);
    return;
}

void BinarySearchTree::LogInorder(Node *tree) const { // prints keys in inorder
    if (tree == nullptr)
        return;
    LogInorder(tree->left);
    std::cout << tree->key << ' ';
    LogInorder(tree->right);
    return;
}

void BinarySearchTree::LogPostorder(Node *tree) const { // prints keys in postorder
    if (tree == nullptr)
        return;
    LogPostorder(tree->left);
    LogPostorder(tree->right);
    std::cout << tree->key << ' ';
    return;
}

double BinarySearchTree::Avg(Node* tree) const {
    // typecast int into double in order to avoid precision loss
    return static_cast<double>(Sum(tree)) / static_cast<double>(Size(tree));
}

void BinarySearchTree::Log(Node *tree) const { // calls pre-, in- and postorder
    std::cout << "Preorder  : ";
    LogPreorder(tree);
    std::cout << '\n';
    std::cout << "Inorder   : ";
    LogInorder(tree);
    std::cout << '\n';
    std::cout << "Postorder : ";
    LogPostorder(tree);
    std::cout << '\n' << '\n';
}

void BinarySearchTree::Stats(Node *tree) const {
    std::cout << '\n' << "***** STATISTICS *****" << '\n' << '\n';
    std::cout << "Nodes n = " << Size(tree) << '\n';
    std::cout << "Sum     = " << Sum(tree) << '\n';
    std::cout << "Average = " << Avg(tree) << '\n';
    std::cout << "Minimum = " << FindMin() << '\n';
    std::cout << "Minimum = " << FindMinRec(tree) << '\n';
    std::cout << "Maximum = " << FindMax() << '\n';
    std::cout << "Maximum = " << FindMaxRec(tree) << '\n';
    std::cout << "Height  = " << Height(tree) << '\n';
}

int BinarySearchTree::Height(Node *tree) const {
    if (tree == nullptr)
        return 0;
    // recursively calculates the height of a tree by adding 1 to the maximum of the subtree left or right
    return 1 + (Height(tree->left) > Height(tree->right) ? Height(tree->left) : Height(tree->right));
}

int BinarySearchTree::Balance(Node *tree) const { // calculates Balance of a Node
    if (tree == nullptr)
        return 0;
    // balance of node is height of right subtree hr - height of left subtree hl (diff = hr - hl)
    return (Height(tree->right) - Height(tree->left));
}

void BinarySearchTree::LogBalance(Node *tree)  { // logs the balance of each node inorder
    if (avl && (Balance(tree) < -1 || Balance(tree) > 1)) // sets avl to false if one node has balance < -1 or > 1
        avl = false;
    if (tree == nullptr)
        return;
    LogBalance(tree->left);
    if (Balance(tree) >= -1 && Balance(tree) <= 1)
        std::cout << "bal(" << tree->key << ") = " << Balance(tree) << '\n';
    else
        std::cout << "bal(" << tree->key << ") = " << Balance(tree) << "    (AVL violation!)" << '\n';
    LogBalance(tree->right);
}




