#include <iostream>
#include "AVLTree.h"

using namespace WET1;
using namespace std;


int main() {
    std::cout << "Hello, World!" << std::endl;
    AVLTree<int> t(5);

    t.insert(4);
    t.insert(7);
    t.insert(3);
    t.insert(6);
    t.insert(8);
    t.insert(9);


    t.remove(5);

    t.print2D();

    return 0;
}
