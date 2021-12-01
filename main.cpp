#include <iostream>
#include "AVLTree.h"

using namespace WET1;
using namespace std;


int main() {
    std::cout << "Hello, World!" << std::endl;
    AVLTree<int> t1(1);
    t1.insert(2);
    t1.insert(3);
    t1.insert(4);
    t1.insert(13);
    t1.insert(5);
    t1.insert(10);
    t1.insert(6);
    t1.insert(11);
    t1.insert(9);
    t1.insert(16);

//    AVLTree<int> t2(8);
    AVLTree<int>* t2 = new AVLTree<int>(8);
    t2->insert(7);
    t2->insert(12);
    t2->insert(14);
    t2->insert(15);


    t1.print2D();

    cout << "------------------------------------------" << endl;

    t2->print2D();

    AVLTree<int> *t3 = AVLTree<int>::merge(&t1, t2);

    cout << "------------------------------------------" << endl;

    t3->print2D();

//    delete t2;
//    delete t3;

    return 0;
}