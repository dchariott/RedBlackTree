//
// Created by Dylan Chariott on 2019-05-14.
//

#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

template <class T>
struct Node{
    T key;
    Node* left;
    Node* right;
    Node* parent;
    string color;

    explicit Node(T key): key(key),
                 left(nullptr),
                 right(nullptr),
                 parent(nullptr),
                 color("red"){}

    Node<T>& operator=(Node<T>& copySource){
        return copySource;
    }

    bool operator>(T key2){
        return this->key > key2;
    }
};

template <class T>
class RedBlackTree{
private:
    Node<T>* root;

    void InOrderTraversal(Node<T>* node){
        if (node != nullptr){
            InOrderTraversal(node->left);
            if (node == root) cout << "Root ";
            cout << "Node: " << node->key << " Color: " << node->color << endl;
            InOrderTraversal(node->right);
        }
    }

    void Insert(Node<T>*& node, Node<T>* parent, T key){
        if (node == nullptr){
            node = new Node<T>(key);
            node->parent = parent;
            if (node->key == 21) cout << GrandParent(node)->key << endl;
            cout << "Node: " << node->key << " inserted" << endl;
            ReColor(node);
        }
        else if (node->key > key){
            Insert(node->left, node, key);
        }
        else{
            Insert(node->right, node, key);
        }
    }

    Node<T>* Find(Node<T>* node, T key){
        if (node == nullptr){
            return nullptr;
        }
        else if (node->key == key){
            return node;
        }
        else if (node->key > key){
            return Find(node->left, key);
        }
        else{
            return Find(node->right, key);
        }
    }

    void ReColor(Node<T>* node){
        if (node == nullptr) return;
        Node<T>* parent = Parent(node);
        Node<T>* grandParent = GrandParent(node);
        Node<T>* uncle = Uncle(node);
        cout << "recolor" << endl;
        if (parent == nullptr){
            node->color = "black";
        }
        else if (parent != nullptr && parent->color != "black"){
            if (uncle != nullptr && uncle->color == "red"){
                parent->color = "black";
                uncle->color = "black";
                grandParent->color = "red";
                ReColor(grandParent);
            }
            else{
                cout << "Node to be restructured: " << node->key << endl;
                Restructure(node);
            }
        }
    }

    void Restructure(Node<T>* node){
        Node<T>* parent = Parent(node);
        Node<T>* grandParent = GrandParent(node);
        cout << "Node Restructured: " << node->key << endl;

        if (node == parent->right && parent == grandParent->left){
            LeftRotate(parent);
            node = node->left;
            RightRotate(grandParent);
            node->color = "black";
            grandParent->color = "red";
        }
        else if (node == parent->left && parent == grandParent->right){
            RightRotate(parent);
            node = node->right;
            LeftRotate(grandParent);
            node->color = "black";
            grandParent->color = "red";
        }
        else if (node == parent->left && parent == grandParent->left){
            RightRotate(grandParent);
            parent->color = "black";
            grandParent->color = "red";
        }
        else if (node == parent->right && parent == grandParent->right){;
            LeftRotate(grandParent);
            parent->color = "black";
            grandParent->color = "red";
        }
    }


    void RightRotate(Node<T>* node){
        cout << "Node: " << node->key << " Right Rotate" << endl;
        Node<T>* node2 = node->left;
        Node<T>* parent = Parent(node);
        node->left = node2->right;
        node2->right = node;
        node->parent = node2;
        if (node->left != nullptr){
            node->left->parent = node;
        }
        if (parent != nullptr){
            if (node == parent->left){
                parent->left = node2;
            }
            else if (node == parent->right){
                parent->right = node2;
            }
        }
        node2->parent = parent;
        if (node2->right == root) root = node2;
    }

    void LeftRotate(Node<T>* node){
        cout << "Node: " << node->key << " Left Rotate" << endl;
        Node<T>* node2 = node->right;
        cout << node2->color << " " << node->right->color << endl;
        Node<T>* parent = Parent(node);
        node->right = node2->left;
        node2->left = node;
        node->parent = node2;
        if (node->right != nullptr){
            node->right->parent = node;
        }
        if (parent != nullptr){
            if (node == parent->left){
                parent->left = node2;
            }
            else if (node == parent->right){
                parent->right = node2;
            }
        }
        node2->parent = parent;
        if (node2->left == root) root = node2;
    }

    Node<T>* Parent(Node<T>* node){
        return node->parent;
    }

    Node<T>* GrandParent(Node<T>* node){
        Node<T>* parent = Parent(node);
        if (parent == nullptr){
            return nullptr;
        }
        else{
            return Parent(parent);
        }
    }

    Node<T>* Uncle(Node<T>* node){
        Node<T>* grandParent = GrandParent(node);
        if (grandParent == nullptr){
            return nullptr;
        }
        else if (grandParent->left == Parent(node)){
            return grandParent->right;
        }
        else{
            return grandParent->left;
        }
    }

    int IsBalanced(Node<T>* node){
        if (node == nullptr) return 0;
        int leftHeight =  IsBalanced(node->left);
        int rightHeight = IsBalanced(node->right);
        int numberToAdd = node->color == "black"? 1 : 0;
        if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight){
            return -1;
        }
        else{
            return leftHeight + numberToAdd;
        }
    }

public:
    RedBlackTree(): root(nullptr) {}

    bool IsBalanced(){
        return IsBalanced(root) != -1;
    }

    void InOrderTraversal(){
        InOrderTraversal(root);
    }

    void Insert(T key){
        Insert(root, nullptr, key);
    }

    void MassInsert(const vector<int>& keys){
        for (auto key : keys){
            Insert(key);
        }
    }

    Node<T>* Find(T key){
        return Find(root, key);
    }

    Node<T>* operator[](T key){
        return Find(key);
    }
};
#endif //REDBLACKTREE_REDBLACKTREE_H
