//
// Created by Jesus Lopez on 9/26/23.
//

#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H
#include "string"
#include <queue>
#pragma once
using namespace std;


struct TreeNode {
    string name;
    int ID; // Gator ID
    int height;
    TreeNode* left;
    TreeNode* right;

    // Constructor - Initialize the name and ID to empty string, and left and right to nullptr
    TreeNode(string name, int ID) : name(name), ID(ID), height(1), left(nullptr), right(nullptr) {}
};
class AVL {
private:

public:

    TreeNode* insert(TreeNode* root, string name, int ID){
        string id = to_string(ID);
        cout << id << endl;
        return nullptr;
        if(to_string(ID).length() != 8){
            //cout << to_string(ID) << endl;

            cout << "unsuccessful" << endl;
            return root;
        }
        if(root == nullptr){
            cout << "successful" << endl;
            return new TreeNode(name, ID);
        }
        if(ID == root->ID){
            cout << "unsuccessful" << endl;
            return root;
        }
        if(ID < root->ID){
            root->left = insert(root->left, name, ID);
        }
        else {
            root->right = insert(root->right, name, ID);
        }
        root->height = 1 + max(root->left ? root->left->height: 0, root->right ? root->right->height: 0);

        // check whether its balance
        int balance = (root->left ? root->left->height : 0) - (root->right ? root->right->height : 0);

        // left heavy
        if(balance > 1){
            if(ID < root->left->ID) {
                return rotateRight(root);
            }
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        // Right heavy
        if(balance < -1){
            if(ID > root->right->ID){
                return rotateLeft(root);
            }
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    // Remove Id
    TreeNode* RemoveId(TreeNode* root, int ID) {

        if(root == nullptr){
            cout << "unsuccessful" << endl; // ID does not exist in the tree
            return nullptr;
        }
        else if(ID < root->ID){
            root->left = RemoveId(root->left, ID);
        }
        else if(ID > root->ID){
            root->right = RemoveId(root->right, ID);
        }
        else {
            cout << "successful" << endl; // IS was found and node will be deleted.
            // Case 1: No child
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
                // Case 2: One Child
            else if (root->left == nullptr) {
                TreeNode *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                TreeNode *temp = root->left;
                delete root;
                return temp;
            }
            // case 3: 2 child
            TreeNode *temp = minValueNode(root->right); // Get in-order successor

            // copy the inorder successor's data to this node
            root->ID = temp->ID;
            root->name = temp->name;

            // Delete the inorder successor
            root->right = RemoveId(root->right, temp->ID);
        }
        // Optional: Balance the tree
        root->height = 1 + max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);

        return root;
    }

    // Search Id
    bool searchID(TreeNode* root, int ID){
        if(root == nullptr){
            return false;  // not found
        }
        else if(root->ID == ID){
            cout << root->name << endl; // print the name
            return true; // found
        }
        else if(ID <= root->ID){
            return searchID(root->left, ID); // search left subtree
        }
        else {
            return searchID(root->right, ID); // search in the right tree
        }
    }
    void searchForID(TreeNode* root, int ID){
        if(!searchID(root, ID)){
            cout << "unsuccessful" << endl;
        }
    }

    /** Search Name  **/
    void searchName(TreeNode* root, string name){
        if(root == nullptr){
           cout << "unsuccessful" << endl; // not found
           return;
        }
        // found
        if(root->name == name){
            cout << root->ID << endl; // print the name
        }
        if(root->left){
            searchName(root->left, name); // search left subtree
        }
        if(root->right){
            searchName(root->right, name); // search in the right tree
        }
    }


    TreeNode* minValueNode(TreeNode* node){
        TreeNode* current = node;

        // loop down to find leftmost leaf
        while(current->left != nullptr){
            current = current->left;
        }
        return current;
    }
    TreeNode* rotateLeft(TreeNode* root){
        TreeNode* grandchild = root->right->left;
        TreeNode* newParent = root->right;
        newParent->left = root;
        root->right = grandchild;

        root->height = 1 + max(root->left ? root->left->height: 0, root->right ? root->right->height: 0);
        newParent->height = 1 + max(newParent->left ? newParent->left->height : 0, newParent->right ? newParent->right->height : 0);

        return newParent;
    }

    TreeNode* rotateRight(TreeNode* root){
        TreeNode* grandchild = root->left->right;
        TreeNode* newParent = root->left;
        newParent->right = root;
        root->left = grandchild;

        root->height = 1 + max(root->left ? root->left->height: 0, root->right ? root->right->height: 0);
        newParent->height = 1 + max(newParent->left ? newParent->left->height : 0, newParent->right ? newParent->right->height : 0);

        return newParent;
    }

    // Pre Order
    void preOrder(TreeNode* root){
        if(root == nullptr){
            return;
        }
        cout << "  ," << root->name << endl;
        preOrder(root->left);
        preOrder(root->right);

    }
    // inOrder
    void inOrder(TreeNode* root){
        if(root == nullptr){
            return;
        }
        inOrder(root->left);
        cout << root->name << endl;
        inOrder(root->right);

    }

    // postOrder
    void postOrder(TreeNode* root){
        if(root == nullptr){
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        cout << root->name << endl;

    }

    void printLevelCount(TreeNode* root){
        if(root == nullptr){
            cout << 0 << endl;
            return;
        }

        queue<TreeNode*> q;
        q.push(root);
        // while there is at least one discovered node
        int levelCount = 0;

        while(!q.empty()) {
            int nodeCount = q.size(); // number of nodes at the current level

            while (nodeCount > 0) {
                TreeNode *curr = q.front();
                if (curr->left != nullptr) {
                    q.push(curr->left);
                }
                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
                q.pop(); // removing the element at front
                nodeCount--; // decrease the num of nodes to be processed at the current level
            }
            levelCount++; // increase level
        }
        cout << levelCount << endl; // num of level
    }

    TreeNode* removeInorderN(TreeNode* root, int N, int count){
        if(root == nullptr){
            return nullptr;
        }
        root->left = removeInorderN(root->left, N, count);
        count++;

        if(count == N+1){
            RemoveId(root, root->ID);
            cout << "successful" << endl;
            return nullptr;
        }

        root->right = removeInorderN(root->right, N, count);
        return root;
    }

    // Deletion
    //AVL() {root = nullptr; }
};


#endif //PROJECT1_AVL_H

