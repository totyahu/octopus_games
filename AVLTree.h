#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <iostream>
#include <cstdio>
#include <stdexcept>

namespace DS {
    template <class T>
    class AVLTree
    {
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
        int fix(AVLtree<T> &leaf);

    public:
        AVLTree()=delete;
        AVLTree(const T& data);
//        AVLTree(const AVLTree& tree);
//        AVLTree<T>& operator=(const AVLTree<T>& tree);
        ~AVLTree();

        bool isLeaf();
        AVLTree<T>* find(const T& data);
        void insert(const T& data);
        void delete(const T& data);


    };

    template <class T>
    AVLTree<T>::AVLTree(const T& data):
        data(data),
        parent(nullptr),
        right(nullptr),
        left(nullptr),
        height(0)
    {}

    template <class T>
    bool AVLTree<T>::isLeaf(){
        return this->left == nullptr && this->right == nullptr;
    }

    template <class T>
    int AVLTree<T>::leftHeight(){
        return this->left == nullptr ? 0 : this->left->height;
    }

    template <class T>
    int AVLTree<T>::rightHeight(){
        return this->right == nullptr ? 0 : this->right->height;
    }

    template <class T>
    int AVLTree<T>::BF(){
        return this->leftHeight() - this->rightHeight();
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
        AVLTree<T> new_tree(data);

        if(data <= this->data){
            if(this->left == nullptr){
                this->left = &new_tree;
                new_tree.parent = this;
            }
            else {
                this->left->insert(data);
            }
        }
        else {
            if(this->right == nullptr){
                this->right = &new_tree;
                new_tree.parent = this;
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

}


#endif