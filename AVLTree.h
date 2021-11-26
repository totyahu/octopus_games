#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <iostream>
#include <cstdio>
#include <stdexcept>

#define LEFT 1
#define ROOT 0
#define RIGHT -1


namespace DS {
    template <class T>
    class AVLTree
    {
    public:

        T data;
        AVLTree<T> * parent;
        AVLTree<T> * right;
        AVLTree<T> * left;
        int height;

        int leftHeight();
        int rightHeight();
        int BF();
        void updateHeight();
        void rollLeft();
        void rollRight();
        int whoAmI();
        void rollLL();
        void rollRR();
        void rollRL();
        void rollLR();
        void roll();
        void fix();

//    public:
        AVLTree() = delete;
        AVLTree(const T& data);
//        AVLTree(const AVLTree& tree);
//        AVLTree<T>& operator=(const AVLTree<T>& tree);
        ~AVLTree();

        bool isLeaf();
        AVLTree<T>* find(const T& data);
        void insert(const T& data);
        void remove(const T& data);
    };

    int max(int n1, int n2){
        return n1 >= n2 ? n1 : n2;
    }

    template <class T>
    AVLTree<T>::AVLTree(const T& data):
        data(data),
        parent(nullptr),
        right(nullptr),
        left(nullptr),
        height(0)
    {}

    template <class T>
    AVLTree<T>::~AVLTree(){
        if(this->left != nullptr){
            this->left->~AVLTree();
        }

        if(this->right != nullptr){
            this->right->~AVLTree();
        }

        delete this;
    }

    template <class T>
    bool AVLTree<T>::isLeaf(){
        return this->left == nullptr && this->right == nullptr;
    }

    template <class T>
    int AVLTree<T>::leftHeight(){
        return this->left == nullptr ? -1 : this->left->height;
    }

    template <class T>
    int AVLTree<T>::rightHeight(){
        return this->right == nullptr ? -1 : this->right->height;
    }

    template <class T>
    int AVLTree<T>::BF(){
        return this->leftHeight() - this->rightHeight();
    }

    template <class T>
    void AVLTree<T>::rollLeft() {
        if(this->right == nullptr)
            return;

        AVLTree<T> * right_left = this->right->left;
        AVLTree<T> * old_parent = this->parent;
        AVLTree<T> * parent_son = nullptr;
        if(old_parent != nullptr)
        {
            if(old_parent->right == this)
            {
                parent_son=old_parent->right;
            }
            else
            {
                parent_son=old_parent->left;
            }
        }

        this->right->left=this;
        this->parent= this->right;
        this->right=right_left;

        if(parent_son != nullptr)
        {
            parent_son = this->parent;
            this->parent->parent=old_parent;
        }
    }

    template <class T>
    void AVLTree<T>::rollRight()  {
        if(this->left == nullptr)
            return;

        AVLTree<T> * left_right = this->left->right;
        AVLTree<T> * old_parent = this->parent;
        AVLTree<T> * parent_son = nullptr;
        if(old_parent != nullptr)
        {
            if(old_parent->right == this)
            {
                parent_son=old_parent->right;
            }
            else
            {
                parent_son=old_parent->left;
            }
        }

        this->left->right=this;
        this->parent= this->left;
        this->left=left_right;

        if(parent_son!= nullptr)
        {
            parent_son= this->parent;
            this->parent->parent=old_parent;
        }
    }

    template <class T>
    int  AVLTree<T>::whoAmI()
    {
        if(this->parent != nullptr)
        {
            if(parent->right == this)
            {
                return RIGHT;
            }
            return LEFT;
        }
        return ROOT;
    }

    template <class T>
    void AVLTree<T>::rollLL(){
        this->rollRight();
    }

    template <class T>
    void AVLTree<T>::rollRR(){
        this->rollLeft();
    }

    template <class T>
    void AVLTree<T>::rollRL(){
        this->right->rollRight();
        this->rollLeft();
    }

    template <class T>
    void AVLTree<T>::rollLR(){
        this->left->rollLeft();
        this->rollRight();
    }

    template <class T>
    void AVLTree<T>::roll(){
        if(this->BF()==2){
            if(this->left->BF()==1){
                this->rollLL();
            }
            else{
                this->rollLR();
            }
        } else{
            if(this->right->BF()==1){
                this->rollRL();
            }
            else{
                this->rollRR();
            }
        }
    }

    template <class T>
    void AVLTree<T>::updateHeight(){
        this->height = 1 + max(this->leftHeight(), this->rightHeight());
    }

    template <class T>
    AVLTree<T>* AVLTree<T>::find(const T& data){
        if(data == this->data){
            return this;
        }

        if(this->isLeaf()){
            return nullptr;
        }

        if(data < this->data){
            return this->left->find(data);
        }

        return this->right->find(data);
    }

    template <class T>
    void AVLTree<T>::insert(const T& data){
        if(data <= this->data){
            if(this->left == nullptr){
                AVLTree<T>* new_tree = new AVLTree<T>(data);
                this->left = new_tree;
                new_tree->parent = this;
                this->fix();
            }
            else {
                this->left->insert(data);
            }
        }
        else {
            if(this->right == nullptr){
                AVLTree<T>* new_tree = new AVLTree<T>(data);
                this->right = new_tree;
                new_tree->parent = this;
                this->fix();
            }
            else {
                this->right->insert(data);
            }
        }
    }

    template <class T>
    void AVLTree<T>::fix(){
        if(abs(this->BF()) == 2){
            this->roll();
        }

        int oldHeight = this->height;
        this->updateHeight();
        if(this->height == oldHeight || this->parent == nullptr){
            return;
        }

        this->parent->fix();
    }

//    // Function to print binary tree in 2D
//    // It does reverse inorder traversal
//    template <class T>
//    void print2DUtil(AVLTree<T> *root, int space)
//    {
//        // Base case
//        if (root == nullprt)
//            return;
//
//        // Increase distance between levels
//        space += 10;
//
//        // Process right child first
//        print2DUtil(root->right, space);
//
//        // Print current node after space
//        // count
//        cout << endl;
//        for (int i = 10; i < space; i++)
//            cout << " ";
//        cout << root->data << "\n";
//
//        // Process left child
//        print2DUtil(root->left, space);
//    }
//
//// Wrapper over print2DUtil()
//    template <class T>
//    void print2D(const AVLTree<T> *root)
//    {
//        // Pass initial space count as 0
//        print2DUtil(root, 0);
//    }


}


#endif