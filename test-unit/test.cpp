#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../src/AVL.h"

using namespace std;


TEST_CASE("AVL Incorrect Commands", "[incorrect_commands]") {
    AVL tree;
    TreeNode* root = nullptr;

    REQUIRE(tree.insert(root, "A11y", "456799999") == root);  // ID length not 8
    REQUIRE(tree.insert(root, "Bob", "1234567") == root);    // ID length not 7
    REQUIRE(tree.insert(root, "Charlie", "123456789") == root); // ID length 9
    REQUIRE(tree.insert(root, "David", "abcdefg8") == root);    // ID with non-numeric chars
    REQUIRE(tree.insert(root, "Eve", "") == root);    // Empty ID
}

TEST_CASE("AVL Edge Cases", "[edge_cases]") {
    AVL tree;
    TreeNode* root = nullptr;

    REQUIRE(tree.RemoveId(root, 12345678) == nullptr);  // Remove from empty tree
    root = tree.insert(root, "Adam", "12345678");
    REQUIRE(tree.searchID(root, 87654321) == false);  // Search non-existent ID
    REQUIRE(tree.searchID(root, 12345678) == true);   // Search existent ID
}

TEST_CASE("AVL Rotation Cases", "[rotations]") {
    AVL avl;
    TreeNode* root = nullptr;
    root = avl.insert(root, "C", "00000003");
    root = avl.insert(root, "B", "00000002");
    root = avl.insert(root, "A", "00000001"); // right rotation

    AVL avl2;
    TreeNode* root2 = nullptr;
    root2 = avl2.insert(root2, "A", "00000001");
    root2 = avl2.insert(root2, "B", "00000002");
    root2 = avl2.insert(root2, "C", "00000003");  // a single left rotation.

    AVL avl3;
    TreeNode* root3 = nullptr;
    root3 = avl3.insert(root3, "C", "00000003");
    root3 = avl3.insert(root3, "A", "00000001");
    root3 = avl3.insert(root3, "B", "00000002"); // This will require a left rotation on A, then a right rotation on C.

    AVL avl4;
    TreeNode* root4 = nullptr;
    root4 = avl4.insert(root4, "A", "00000001");
    root4 = avl4.insert(root4, "C", "00000003");
    root4 = avl4.insert(root4, "B", "00000002"); // This will require a right rotation on C, then a left rotation on A.
}

TEST_CASE("AVL Deletion Cases", "[deletions]") {
    AVL tree;
    TreeNode* root = nullptr;

    // Inserting 3 nodes
    root = tree.insert(root, "A", "12345678");
    root = tree.insert(root, "B", "47991111");
    root = tree.insert(root, "C", "47889999");

    // Deletion: No children
    root = tree.RemoveId(root, 12345678);
    REQUIRE(tree.searchID(root, 12345678) == false);

    // Deletion: One child
    root = tree.RemoveId(root, 47991111);
    REQUIRE(tree.searchID(root, 47991111) == false);

    // Deletion: Two children
    root = tree.insert(root, "B", "87654321");
    root = tree.insert(root, "C", "01234567");
    root = tree.RemoveId(root, 87654321);
    REQUIRE(tree.searchID(root, 01234567) == false);
}

TEST_CASE("AVL 100 Nodes and Removal", "[bulk]") {
    AVL tree;
    TreeNode* root = nullptr;

    // Insert 100 nodes
    for (int i = 1; i <= 100; i++) {
        string id = to_string(i);
        while(id.length() < 8) id = "0" + id;
        root = tree.insert(root, "Name" + id, id);
    }
    // Remove 10 random nodes
    for (int i = 5; i <= 50; i+=5) {
        root = tree.RemoveId(root, i);
    }

    // Check if remaining nodes are in order
    for (int i = 1; i <= 100; i++) {
        if (i % 5 == 0 && i <= 50) {
            REQUIRE(tree.searchID(root, i) == false);
        } else {
            REQUIRE(tree.searchID(root, i) == true);
        }
    }
}