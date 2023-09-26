
#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H
#include "string"
#pragma once
using namespace std;


struct TreeNode {
    string name;
    int ID;
    int height;
    TreeNode* left;
    TreeNode* right;

    // Constructor - Initialize the name and ID to empty string, and left and right to nullptr
    TreeNode(string name, int ID) : name(""), ID(), left(nullptr), right(nullptr) {}
};
class AVL {
private:
    TreeNode* root;

public:
    TreeNode* insert(TreeNode* root, string name, int ID){
        if(root == nullptr){
            return new TreeNode(name, ID);
        }
        if(ID < root->ID){
            root->left = insert(root->left, name, ID);
        }
        else{
            root->right = insert(root->right, name, ID);
        }
        root->height = 1 + max(root->left ? root->height: 0, root->right ? root->right->height: 0);
        return root;
    }
    AVL(): root() {}
};


#endif //PROJECT1_AVL_H
