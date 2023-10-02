#include <iostream>
#include "AVL.h"
using namespace std;

int main() {
    AVL t;
    TreeNode* root = nullptr;

    root = t.insert(root, "Brandon", 00000001);
//    root = t.insert(root, "Brian", 35459999);
//    root = t.insert(root, "Briana", 87879999);
//    root = t.insert(root, "Bella", 95469999);
    //root = t.RemoveId(root, 45679999);

    //root = t.insert(root, "Anderson", 7);

    // In-order traversal
    cout << "In-order traversal:\n";
    t.inOrder(root);
    //t.
    cout << "\n";

    return 0;
}
