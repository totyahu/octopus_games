#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include "./TreeNode.h"
#include "./Utils.h"

#define LEFT 1
#define ROOT 0
#define RIGHT -1


using namespace std;

namespace WET1 {

    template<class T>
    class AVLTree {
        TreeNode<T> *root;
        int size;

    public:
        AVLTree();
        explicit AVLTree(const T &data);
        AVLTree(TreeNode<T> *tree, int size);
        ~AVLTree();
        T *find(const T &data) const;
        bool exists(const T &data) const;
        void insert(const T &data);
        void remove(const T &data);
        T* getMax() const;
        int getSize() const;
        void toSortedArray(T dist_arr[]) const;
        static AVLTree<T>* merge(const AVLTree<T> *tree1, const AVLTree<T> *tree2);
        void print2D() const;

        template<typename P>
        bool query(T* dest_arr, P pred, int find_size){
            int found = 0;
            this->root->query(pred, dest_arr, find_size, &found);
            return found == find_size;
        }
    };

//    AVLTree implementation
    template<class T>
    AVLTree<T>::AVLTree() {
        this->root = nullptr;
        this->size = 0;
    }

    template<class T>
    AVLTree<T>::AVLTree(const T &data) {
        this->root = new TreeNode<T>(data);
        this->size = 1;
    }

    template<class T>
    AVLTree<T>::AVLTree(TreeNode<T> *tree, int size): root(tree), size(size) {}

    template<class T>
    AVLTree<T>::~AVLTree(){
        delete this->root;
    }


    template<class T>
    T *AVLTree<T>::find(const T &data) const {
        if(!this->size){
            return nullptr;
        }

        TreeNode<T> *res = this->root->find(data);
        if (res == nullptr) {
            return nullptr;
        }
        return this->root->find(data)->getData();
    }

    template<class T>
    bool AVLTree<T>::exists(const T &data) const {
        if(this->root == nullptr){
            return false;
        }
        return this->root->find(data) != nullptr;
    }

    template<class T>
    void AVLTree<T>::insert(const T &data) {
        this->size += 1;
        if (this->root == nullptr) {
            this->root = new TreeNode<T>(data);
        } else {
            this->root->insert(data);
            TreeNode<T> *parent = this->root->getParent();
            if (parent != nullptr) {
                this->root = parent;
            }
        }
    }

    template<class T>
    void AVLTree<T>::remove(const T &data) {
        this->size -= 1;
        this->root = this->root->remove(data);
    }

    template<class T>
    void AVLTree<T>::toSortedArray(T dist_arr[]) const{
        this->root->toSortedArray(dist_arr);
    }

    template<class T>
    AVLTree<T>* AVLTree<T>::merge(const AVLTree<T> *tree1, const AVLTree<T> *tree2) {
        TreeNode<T> *new_tree = TreeNode<T>::merge(tree1->root, tree2->root, tree1->size, tree2->size);
        return new AVLTree<T>(new_tree, tree1->size + tree2->size);
    }

    template<class T>
    T* AVLTree<T>::getMax() const{
        if(!size){
            return nullptr;
        }
        return this->root->getMax();
    }

    template<class T>
    int AVLTree<T>::getSize() const{
        return this->size;
    }

    template<class T>
    void AVLTree<T>::print2D() const {
        this->root->print2D();
    }

}

#endif