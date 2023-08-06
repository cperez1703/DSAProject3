#include<string>
#include<vector>
#include "Artist.h"
#pragma once
using namespace std;

class RedBlackTree{
private:
    struct Node{
        std::string genre;
        std::vector<Artist> artists;
        Node *left = nullptr;
        Node *right = nullptr;
        bool isRed = true;
        Node *parent = nullptr;
        Node *grandParent = nullptr;
        Node(string genre_, Artist object_);
    };
    Node* deepest = nullptr;
    Node* root = nullptr;
    bool newNode = true;
    Node* insertHelper(Node *node, Artist object, string& genre, Node* parent, Node* grandparent);

    // rotations
    Node* rotateRight(Node *node);
    Node* rotateLeft(Node *node);

public:
    RedBlackTree(vector<Artist> artists);
    void insertGenreNode(string genre, Artist object);
    void fixRedBlackValidity(Node* node, Node* temp);
    vector<Artist> searchGenre(string genre);

};


// constructs red-black tree from the data file
RedBlackTree::RedBlackTree(vector<Artist> objects) {
    root = nullptr;
    for (int i = 0; i < objects.size(); i++) {
        insertGenreNode(objects[i].genre, objects[i]);
    }
}

// constructs a node
RedBlackTree::Node::Node(string genre_, Artist object_) {
    genre = genre_;
    artists.push_back(object_);
    isRed = true;
}


RedBlackTree::Node *RedBlackTree::insertHelper(Node *node, Artist object, string& genre, Node* parent, Node* grandparent) {
    if (node == nullptr) {
        node = new Node(genre, object);
        node->parent = parent;
        node->grandParent = grandparent;
        deepest = node;
        return node;
    }
    // if genre node exists
    else if (genre == node->genre) {
        node->artists.push_back(object);
        newNode = false;
    }
    // to the left in bst
    else if (genre < node->genre) {;
        node->left = insertHelper(node->left, object, genre, node, parent);
    }
    //right in bst
    else if (genre > node->genre) {
        node->right = insertHelper(node->right, object, genre, node, parent);
    }
    return node;
}

void RedBlackTree::RedBlackTree::insertGenreNode(string genre, Artist object) {
    if (root == nullptr) {
        root = new Node(genre, object);
        root->isRed = false;
        root->parent = nullptr;
        root->grandParent = nullptr;
    }
    else {
        newNode = true;
        insertHelper(root, object, genre, nullptr, nullptr);
        if(newNode){
            // starts at deepest node and checks to make sure nothing is violated
            fixRedBlackValidity(root, deepest);
        }
        if (root->isRed) {
            root->isRed = false;
        }
    }
}


RedBlackTree::Node *RedBlackTree::rotateRight(RedBlackTree::Node *node) {
    Node* leftChild = node->left;
    leftChild->parent = leftChild->grandParent;
    node->left = leftChild->right;
    leftChild->right = node;
    node->parent = leftChild;
    if (node == root) {
        leftChild->grandParent = nullptr;
        root = leftChild;
    }
    return leftChild;
}


RedBlackTree::Node *RedBlackTree::rotateLeft(RedBlackTree::Node *node) {
    Node* rightChild = node->right;
    rightChild->parent = rightChild->grandParent;
    node->right = rightChild->left;
    rightChild->left = node;
    node->parent = rightChild;
    if (node == root) {
        rightChild->grandParent = nullptr;
        root = rightChild;
    }
    return rightChild;
}

void RedBlackTree::fixRedBlackValidity(RedBlackTree::Node *node, Node *temp) {
    if (temp->parent == nullptr) {
        temp->isRed = false;
        return;
    }
    if (!temp->parent->isRed) {
        return;
    }

    Node* parent = temp->parent;
    Node* grandParent = temp->grandParent;
    Node* uncle = nullptr;
    if (grandParent != nullptr && grandParent->right == parent) {
        uncle = grandParent->left;
    }
    else if (grandParent != nullptr && grandParent->left == parent) {
        uncle = grandParent->right;
    }
    if (uncle != nullptr && uncle->isRed) {
        parent->isRed = false;
        uncle->isRed = false;
        grandParent->isRed = true;
        fixRedBlackValidity(root, grandParent);
        return;
    }

    if (temp == parent->right && parent == grandParent->left) {
        rotateLeft(parent);
        temp = parent;
        parent = temp->parent;
    }
    else if (temp == parent->left && parent == grandParent->right) {
        rotateRight(parent);
        temp = parent;
        parent = temp->parent;
    }
    parent->isRed = false;
    grandParent->isRed = true;

    if (temp == parent->left) {
        rotateRight(grandParent);
    }
    else {
        rotateLeft(grandParent);
    }
}

vector<Artist> RedBlackTree::searchGenre(string genre) {
    Node* temp = root;
    while(temp!=nullptr){
        if(temp->genre == genre){
            return temp->artists;
        }
        if(genre < temp->genre){
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    return {};
};
