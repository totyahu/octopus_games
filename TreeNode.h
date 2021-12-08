#ifndef OCTOPUS_GAMES_TREENODE_H
#define OCTOPUS_GAMES_TREENODE_H
#include <string>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include "./Utils.h"

#define LEFT 1
#define ROOT 0
#define RIGHT -1
#define NULL_HEIGHT -1


using namespace std;

namespace WET1 {
    template<class T>
    class TreeNode {
        T data;
        TreeNode<T> *parent;
        TreeNode<T> *right;
        TreeNode<T> *left;
        int height;

        int leftHeight() const;
        int rightHeight() const;
        int BF() const;
        void updateHeight();
        void rollLeft();
        void rollRight();
        int whoAmI() const;
        void rollLL();
        void rollRR();
        void rollRL();
        void rollLR();
        void roll();
        TreeNode<T> *fix(bool stop_at_root = false);
        void gulag();
        void toSortedArrayAux(T* dist_arr, int *idx, int size=-1) const;
        static TreeNode<T> *arrayToTreeAux(const T *sortedArr, int startIdx, int size, TreeNode<T> *parent);
        void print2DUtil(int space) const;

    public:
        TreeNode() = delete;
        explicit TreeNode(const T& data);
//        TreeNode(const TreeNode& tree);
//        TreeNode<T>& operator=(const TreeNode<T>& tree);
        ~TreeNode()=default;

        bool isLeaf() const;
        T* getData() ;
        TreeNode<T> *getParent();
        TreeNode<T> *find(const T &data);
        void insert(const T &data);
        TreeNode<T> *remove(const T &data);
        TreeNode<T> *removeNode(const T &data);
        T* getMax();
        void toSortedArray(T* dist_arr, int size=-1) const;
        static TreeNode<T> *arrayToTree(const T *sortedArr, int size);
        static TreeNode<T> *merge(const TreeNode<T> *tree1, const TreeNode<T> *tree2, int size1, int size2);
        void print2D() const;
        void removeAll(TreeNode<T> * node);

        template <typename P>
        void query(P pred, T* dest_arr, int size, int* found){
            if(*found >= size){
                return;
            }

            if(this->left != nullptr){
                return this->left->query(pred, dest_arr, size, found);
            }

            if(pred(this->data)){
                dest_arr[(*found)++] = this->data;
            }

            if(this->right != nullptr){
                return this->right->query(pred, dest_arr, size, found);
            }
        }

        template<typename P>
        void apply(P pred, void* arg){
            pred(&(this->data), arg);

            if(this->left != nullptr){
                this->left->apply(pred, arg);
            }

            if(this->right != nullptr){
                this->right->apply(pred, arg);
            }
        }

    };

    template <class T>
    TreeNode<T>::TreeNode(const T& data):
    data(data),parent(nullptr),left(nullptr),right(nullptr),height(0){
    }

//    template <class T>
//    TreeNode<T>::~TreeNode(){
//        if(this == nullptr){
//            return;
//        }
//
//        delete this->left;
//        delete this->right;
//
////        T* tmp = &(this->data);
// //       this->gulag();
////        delete tmp;
//    }

    template <class T>
    TreeNode<T>* TreeNode<T>::getParent(){
        return this->parent;
    }

    template <class T>
    T* TreeNode<T>::getData() {
        return &(this->data);
    }

    template <class T>
    bool TreeNode<T>::isLeaf() const{
        return this->left == nullptr && this->right == nullptr;
    }

    template <class T>
    int TreeNode<T>::leftHeight() const{
        return this->left == nullptr ? NULL_HEIGHT : this->left->height;
    }

    template <class T>
    int TreeNode<T>::rightHeight() const{
        return this->right == nullptr ? NULL_HEIGHT : this->right->height;
    }

    template <class T>
    int TreeNode<T>::BF() const{
        return this->leftHeight() - this->rightHeight();
    }

    template <class T>
    void TreeNode<T>::rollLeft(){
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
        if(right_left!= nullptr){
            right_left->parent=this;//new
        }
        this->parent->parent=old_parent;

    }

    template <class T>
    void TreeNode<T>::rollRight(){
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
        if(left_right!= nullptr){
            left_right->parent= this;//new
        }
        this->parent->parent=old_parent;
    }

    template <class T>
    int  TreeNode<T>::whoAmI() const{
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
        this->height = 1 + MAX(this->leftHeight(), this->rightHeight());
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::find(const T& data){
        if(this->data == data){
            return this;
        }

        if(this->isLeaf()){
            return nullptr;
        }

        if(!(this->data < data)){
            if(this->left == nullptr){
                return nullptr;
            }
            else{
                return this->left->find(data);
            }
        }

        if(this->right == nullptr){
            return nullptr;
        }
        else{
            return this->right->find(data);
        }
    }

    template <class T>
    void TreeNode<T>::insert(const T& data){
        if(!(this->data < data)){
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
    TreeNode<T>* TreeNode<T>::removeNode(const T& data){ //can return null
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
            return temp_parent;
        }

        if(temp->left != nullptr && temp->right != nullptr){//has two sons
            TreeNode<T>* replace = temp->right;
            TreeNode<T>* to_return = nullptr;
            if(replace->left == nullptr){
                replace->left=temp->left;
                replace->parent=temp->parent;
                temp->left->parent=replace;

                int who_am_i = temp->whoAmI();
                if(who_am_i == LEFT){
                    temp->parent->left = replace;
                }
                if(who_am_i == RIGHT){
                    temp->parent->right = replace;
                }
                temp->gulag();
//                delete temp;
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
          //delete temp;
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
            TreeNode<T> * temp_left = temp->left;
            temp->gulag();
            return temp_left;
        }

        if(who_am_i == LEFT){
            temp_parent->left = temp->right;
        }
        if(who_am_i==RIGHT){
            temp_parent->right = temp->right;
        }
        temp->right->parent = temp_parent;
        TreeNode<T> * temp_right=temp->right;

        temp->gulag();
        return temp_right;
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::remove(const T& data){
        TreeNode<T> * removed = this->removeNode(data);
        return removed->fix(true);
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::fix(bool stop_at_root){
        if(this== nullptr){
            return nullptr;
        }
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


    template <class T>
    T* TreeNode<T>::getMax(){
        if(this == nullptr){
            return nullptr;
        }
        if(this->right == nullptr){
//            return &(this->data);
            return new T(this->data);
        }
        return this->right->getMax();
    }

    template <class T>
    void TreeNode<T>::toSortedArray(T* dist_arr, int size) const{
        int idx = 0;
        return this->toSortedArrayAux(dist_arr, &idx, size);
    }

    template <class T>
    void TreeNode<T>::toSortedArrayAux(T* dist_arr, int* idx, int size) const{
        if(size != -1 && (*idx) >= size){
            return;
        }

        if(this->left != nullptr){
            this->left->toSortedArrayAux(dist_arr, idx, size);
        }

        dist_arr[(*idx)++] = this->data;

        if(this->right != nullptr){
            this->right->toSortedArrayAux(dist_arr, idx, size);
        }
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::merge(const TreeNode<T> *tree1, const TreeNode<T> *tree2, int size1, int size2){
        if(!size1 && !size2){
            return nullptr;
        }
        if(!size1 && size2){
            T* arr2 = new T[size2];
            tree2->toSortedArray(arr2);
            return TreeNode<T>::arrayToTree(arr2,  size2);
        }
        if(size1 && !size2){
            T* arr1 = new T[size1];
            tree1->toSortedArray(arr1);
            return TreeNode<T>::arrayToTree(arr1,  size1);
        }

        T* arr1 = new T[size1];
        T* arr2 = new T[size2];

        tree1->toSortedArray(arr1);
        tree2->toSortedArray(arr2);


        T* arr_merge = new T[size1 + size2];
        Utils::mergeArrays(arr_merge, arr1, arr2, size1, size2);
        delete[] arr1;
        delete[] arr2;
        TreeNode<T>* t = TreeNode<T>::arrayToTree(arr_merge, size1 + size2);
        delete [] arr_merge;
        return t;
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::arrayToTree(const T* sortedArr, int size){
        return arrayToTreeAux(sortedArr, 0, size, nullptr);
    }

    template <class T>
    TreeNode<T>* TreeNode<T>::arrayToTreeAux(const T* sortedArr, int startIdx, int size, TreeNode<T>* parent){
        if(size == 0){
            return nullptr;
        }

        int mid = (size - 1) / 2 + startIdx;
        TreeNode<T>* sub_root = new TreeNode<T>(sortedArr[mid]);
        sub_root->parent = parent;

        int half_size = size / 2;
        int left_size = size % 2 == 0 ? half_size - 1 : half_size;
        sub_root->left = TreeNode<T>::arrayToTreeAux(sortedArr, startIdx, left_size, sub_root);
        sub_root->right = TreeNode<T>::arrayToTreeAux(sortedArr, mid + 1, half_size, sub_root);
        sub_root->updateHeight();

        return sub_root;
    }


    // Function to print binary tree in 2D
    // It does reverse inorder traversal
    template <class T>
    void TreeNode<T>::print2DUtil(int space) const
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
    void TreeNode<T>::print2D() const{
        // Pass initial space count as 0
        this->print2DUtil(0);
    }

    template <class T>
    void TreeNode<T>::removeAll(TreeNode<T> * node){
        if(node!= nullptr)
        {
            removeAll(node->left) ;
            removeAll(node->right) ;
            delete node;
        }
    }

//    template<class T>
//    TreeNode<T>::~TreeNode() {
//        T * tmp= &data;
//        this->gulag();
//        if(tmp!= nullptr){
//            delete tmp;
//        }
//    }

}


#endif //OCTOPUS_GAMES_TREENODE_H
