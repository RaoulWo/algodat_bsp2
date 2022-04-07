#include <iostream>
#include "BinarySearchTree.h"

// * argc tracks the number of parameters given to the main function,
// * argv stores the parameters as strings in an array
int main(int argc, char* argv[]) {
    if (argc == 1) { // throw error message if no parameters given to the main function
        std::cout << "Error, expected parameters are missing:" << '\n';
        std::cout << "\'treecheck <filename>\' or \'treecheck <filename> <filename>\'" << '\n';
    }
    else if (argc == 2) { // create the BinarySearchTree using the filename given as parameter
        BinarySearchTree bst;
        // Create bst from filename
        bst.Create(argv[1]);
        // Log the tree-nodes
        std::cout << "***** TRAVERSING THE TREE *****" << '\n' << '\n';
        bst.Log(bst.root);
        // Log Balance
        std::cout << "***** AVL AND BALANCE *****" << '\n' << '\n';
        bst.LogBalance(bst.root);
        std::cout << "AVL: " << (bst.avl ? "yes" : "no") << '\n';
        // Print statistics
        bst.Stats(bst.root);
    }
}
