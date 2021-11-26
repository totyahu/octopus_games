#include <iostream>
#include "AVLTree.h"

using namespace DS;
using namespace std;


// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(AVLTree<int> *root, int space)
{
    // Base case
    if (root == nullptr)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(AVLTree<int> *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    AVLTree<int> t(1);

    t.insert(2);
    t.insert(3);
//    t.insert(4);
//    t.insert(5);
//    t.insert(6);
//    t.insert(7);
//    t.insert(8);
//    t.insert(9);
//    t.insert(10);

    print2D(&t);

    return 0;
}
