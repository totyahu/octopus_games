#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <iostream>
#include <cstdio>
#include <stdexcept>

#define LEFT 1
#define ROOT 0
#define RIGHT -1


using namespace std;

namespace WET1 {
    template<class T>
    class TreeNode
    {
        T data;
        TreeNode<T> * parent;
        TreeNode<T> * right;
        TreeNode<T> * left;
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
        TreeNode<T>* fix(bool stop_at_root=false);
        void gulag();

        void print2DUtil(int space);

    public:
        TreeNode() = delete;
        TreeNode(const T& data);
//        TreeNode(const TreeNode& tree);
//        TreeNode<T>& operator=(const TreeNode<T>& tree);
        ~TreeNode() = default;

        bool isLeaf();
        TreeNode<T>* getParent();
        TreeNode<T>* find(const T& data);
        void insert(const T& data);
        TreeNode<T>* remove(const T& data);
        TreeNode<T>* removeNode(const T& data);
        T& getData() const;
        void print2D();
    };

    template <class T>
    class AVLTree
    {
        TreeNode<T>* root;

    public:
        AVLTree()=default;
        AVLTree(const T& data);
        ~AVLTree() = default;

        T* find(const T& data);
        void insert(const T& data);
        void remove(const T& data);
        TreeNode<T>* exists(const T& data);
        void print2D();

    };

    template <class T>
    AVLTree<T>::AVLTree(const T& data){
        this->root = new TreeNode<T>(data);
    }

    template <class T>
    T& TreeNode<T>::getData() const{
        return new T(this->data);
    }

    template <class T>
    void AVLTree<T>::insert(const T& data){
        this->root->insert(data);
        TreeNode<T>* parent = this->root->getParent();
        if(parent != nullptr){
            this->root = parent;
        }
    }

    template <class T>
    void AVLTree<T>::remove(const T& data){
        this->root = this->root->remove(data);
    }

    template <class T>
    void AVLTree<T>::print2D(){
        this->root->print2D();
    }



    template <class T>
    TreeNode<T>::TreeNode(const T& data):
        data(data),
        parent(nullptr),
        right(nullptr),
        left(nullptr),
        height(0)
    {}

//    template <class T>
//    TreeNode<T>::~TreeNode(){
//        if(this->left != nullptr){
//            delete this->left;
//        }
//
//        if(this->right != nullptr){
//            delete this->right;
//        }
//
//        delete this;
//    }

    template <class T>
    TreeNode<T>* TreeNode<T>::getParent(){
        return this->parent;
    }


    template <class T>
    bool TreeNode<T>::isLeaf(){
        return this->left == nullptr && this->right == nullptr;
    }

    template <class T>
    int TreeNode<T>::leftHeight(){
        return this->left == nullptr ? -1 : this->left->height;
    }

    template <class T>
    int TreeNode<T>::rightHeight(){
        return this->right == nullptr ? -1 : this->right->height;
    }

    template <class T>
    int TreeNode<T>::BF(){
        return this->leftHeight() - this->rightHeight();
    }

    template <class T>
    void TreeNode<T>::rollLeft() {
        if(this->right == nullptr)
            return;

        TreeNode<T> * right_left = this->right->left;
        TreeNode<T> * old_parent = this->parent;
        TreeNode<T> * old_son = this->right;
        if(old_parent != nullptr)
        {
            int who_am_i = this->whoAmI();
            if(who_am_i == LEFT){
                old_parent->left = old_son;
            }
            else{
                old_parent->right = old_son;
            }
        }

        this->right->left = this;
        this->parent = this->right;
        this->right = right_left;


        this->parent->parent=old_parent;
    }

    template <class T>
    void TreeNode<T>::rollRight()  {
        if(this->left == nullptr)
            return;

        TreeNode<T> * left_right = this->left->right;
        TreeNode<T> * old_parent = this->parent;
        TreeNode<T> * old_son = this->left;

        if(old_parent != nullptr)
        {
            int who_am_i = this->whoAmI();
            if(who_am_i == LEFT){
                old_parent->left = old_son;
            }
            else{
                old_parent->right = old_son;
            }
        }

        this->left->right = this;
        this->parent = this->left;
        this->left = left_right;


        this->parent->parent=old_parent;
    }

    template <class T>
    int  TreeNode<T>::whoAmI()
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
    void TreeNode<T>::rollLL(){
        this->rollRight();
    }

    template <class T>
    void TreeNode<T>::rollRR(){
        this->rollLeft();
    }

    template <class T>
    void TreeNode<T>::rollRL(){
        this->right->rollRight();
        this->rollLeft();
    }

    template <class T>
    void TreeNode<T>::rollLR(){
        this->left->rollLeft();
        this->rollRight();
    }

    template <class T>
    void TreeNode<T>::roll(){
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
    void TreeNode<T>::updateHeight(){
        this->height = 1 + max(this->leftHeight(), this->rightHeight());
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::find(const T& data){
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
    T* AVLTree<T>::find(const T& data){
        TreeNode<T>* res = this->root->find(data);
        if(res == nullptr){
            return nullptr;
        }
        return &(this->root->find(data)->getData());
    }

    template <class T>
    void TreeNode<T>::insert(const T& data){
        if(data <= this->data){
            if(this->left == nullptr){
                TreeNode<T>* new_tree = new TreeNode<T>(data);
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
                TreeNode<T>* new_tree = new TreeNode<T>(data);
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
    void TreeNode<T>::gulag(){
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::removeNode(const T& data)//can return null
    {
        TreeNode<T>* temp = this->find(data);
        if(temp->isLeaf()){
            TreeNode<T>* temp_parent = temp->parent;

            int who_am_i = temp->whoAmI();
            if(who_am_i == LEFT){
                temp_parent->left = nullptr;
            }
            if(who_am_i == RIGHT){
                temp_parent->right = nullptr;
            }

            temp->gulag();
            delete temp;
            return temp_parent;
        }

        if(temp->left != nullptr && temp->right != nullptr){//has two sons
            TreeNode<T>* replace = temp->right;
            TreeNode<T>* to_return = nullptr;
            if(replace->left == nullptr){
                replace->left=temp->left;
                replace->parent=temp->parent;

                int who_am_i = temp->whoAmI();
                if(who_am_i == LEFT){
                    temp->parent->left = replace;
                }
                if(who_am_i == RIGHT){
                    temp->parent->right = replace;
                }
                temp->gulag();
                delete temp;
                return replace;
            }
            else{
                while(replace->left != nullptr){
                    replace = replace->left;
                }
                to_return = replace->parent;

                if(replace->right != nullptr){
                    replace->right->parent = replace->parent;

                }
                replace->parent->left = replace->right;
            }

            replace->right = temp->right;
            replace->left = temp->left;
            temp->right->parent = replace;
            temp->left->parent = replace;
            replace->parent = temp->parent;

            int who_am_i = temp->whoAmI();
            if(who_am_i == LEFT){
                temp->parent->left = replace;
            }
            if(who_am_i == RIGHT){
                temp->parent->right = replace;
            }

            temp->gulag();
            delete temp;
            return to_return;
        }

        TreeNode<T> * temp_parent = temp->parent;
        int who_am_i=temp->whoAmI();
        if(temp->left != nullptr && temp->right == nullptr){
            if(who_am_i == LEFT){
                temp_parent->left = temp->left;
            }
            if(who_am_i == RIGHT){
                temp_parent->right = temp->left;
            }
            temp->left->parent = temp_parent;

            temp->gulag();
            delete temp;
            return temp_parent;
        }

        if(who_am_i == LEFT){
            temp_parent->left = temp->right;
        }
        if(who_am_i==RIGHT){
            temp_parent->right = temp->right;
        }
        temp->right->parent= temp_parent;

        temp->gulag();
        delete temp;
        return temp_parent;
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::remove(const T& data){
        TreeNode<T> * removed = this->removeNode(data);
        return removed->fix(true);
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::fix(bool stop_at_root){
        if(abs(this->BF()) == 2){
            this->roll();
        }

        int oldHeight = this->height;
        this->updateHeight();
        if((!stop_at_root && this->height == oldHeight) || this->parent == nullptr){
            return this;
        }

        return this->parent->fix(stop_at_root);
    }


    // Function to print binary tree in 2D
    // It does reverse inorder traversal
    template <class T>
    void TreeNode<T>::print2DUtil(int space)
    {
        // Base case
        if (this == nullptr)
            return;

        // Increase distance between levels
        space += 10;

        // Process right child first
        if(this->right != nullptr){
            this->right->print2DUtil(space);
        }

        // Print current node after space
        // count
        cout << endl;
        for (int i = 10; i < space; i++)
            cout << " ";
        cout << this->data << "\n";

        // Process left child
        if(this->left != nullptr){
            this->left->print2DUtil(space);
        }
    }

// Wrapper over print2DUtil()
    template <class T>
    void TreeNode<T>::print2D()
    {
        // Pass initial space count as 0
        this->print2DUtil(0);
    }

    int max(int n1, int n2){
        return n1 >= n2 ? n1 : n2;
    }

    template <class T>
    TreeNode<T>* AVLTree<T>::exists(const T& data){
        return this->root->find(data) != nullptr;
    }

}


#endif