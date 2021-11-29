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
        int whoAmI();
        void rollLL();
        void rollRR();
        void rollRL();
        void rollLR();
        void roll();
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
        void remove(const T& data);


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

        if(parent_son!= nullptr)
        {
            parent_son= this->parent;
            this->parent->parent=old_parent;
        }
        return;
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
        return;
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


    template <class T>
    node<T> *  AVLTree<T>::removeNode(const T& data)//can return null
    {
        node<T> * temp= this->find(data);
        if(temp->isLeaf()){
            node<T> * to_return=temp->parent;
            delete(temp);
            return to_return;
        }

        if(temp->left!= nullptr && temp->right!= nullptr){//has two sons
                node<T> * replace=temp->right;
                if(replace->left== nullptr && replace->right!= nullptr ){
                    replace->right->parent=replace->parent;
                    replace->parent->right=replace->right;
                }
                else{
                    while( replace->left!= nullptr){
                        replace=replace->left;
                    }

                    if(replace->right!= nullptr){
                        replace->right->parent=replace->parent;

                    }
                    replace->parent->left=replace->right;
                }

                replace->right=temp->right;
                replace->left=temp->left;
                temp->right->parent=replace;
                temp->left->parent=replace;
                replace->parent=temp->parent;
                delete(temp);
                return replace;
            }
        node<T> * temp_parent=temp->parent;
        int who_am_i=temp->whoAmI();
        if(temp->left!= nullptr && temp->right== nullptr){
            if(who_am_i==LEFT){
                temp_parent->left=temp->left;
            }
            if(who_am_i==RIGHT){
                temp_parent->right=temp->left;
            }
            temp->left->parent= temp_parent;
            delete(temp)
            return temp_parent;
        }

        if(who_am_i==LEFT){
            temp_parent->left=temp->right;
        }
        if(who_am_i==RIGHT){
            temp_parent->right=temp->right;
        }
        temp->right->parent= temp_parent;
        delete(temp)
        return temp_parent;
    }

    template <class T>
    void AVLTree<T>::remove(const T& data)
    {


    }



}


#endif