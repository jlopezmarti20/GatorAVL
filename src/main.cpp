#include <iostream>
#include "AVL.h"
#include <sstream>
#include <vector>
using namespace std;

int main() {

    AVL avlTree;
    TreeNode* rootTree = nullptr;


    int numCommands;
    cin >> numCommands;  // Read the number of commands

    cin.ignore();
    vector<string> commands(numCommands);


    for(int i = 0; i < numCommands; i++) {
        getline(cin, commands[i]);  // Read each command line-by-line
    }

    for(const string& command : commands) {
        stringstream ss(command);

        string action;
        string name;
        string idStr;

        ss >> action;  // Extract the action/command

        if (action == "search") {
            string arg;
            ss >> arg;
            if (arg[0] == '"') {  // Check if the first character is a quote, indicating a name
                arg.erase(0, 1);  // Remove the opening quote
                if (arg.back() != '"') {
                    string additional;
                    getline(ss, additional, '"');  // read more of the name until the closing quotation
                    arg += " " + additional;
                } else {
                    arg.pop_back();  // Remove the closing quote
                }
                avlTree.searchName(rootTree, arg);  // the method itself will print the result
            } else {
                int id;
                try {
                    id = stoi(arg);
                    avlTree.searchForID(rootTree, id);
                } catch(invalid_argument&) {
                    // Handle the case if it's not a valid integer, though it shouldn't happen as per the commands given
                    cout << "Invalid ID format: " << arg << endl;
                }
            }
        }
        if (action == "insert") {
            char quote;
            ss >> quote;  // Read the opening quotation
            getline(ss, name, '"');  // read the name until the closing quotation
            ss >> idStr;

            rootTree = avlTree.insert(rootTree, name, idStr);
        }
        else if (action == "remove") {
            int id;
            ss >> id;
            if (avlTree.RemoveId(rootTree, id)) {
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        }
        else if (action == "removeInorder") {
            int n;
            ss >> n;
            int count = 0;
            rootTree = avlTree.removeInorderN(rootTree, n, count);
            if (count < n) {
                cout << "unsuccessful" << endl;
            } else {
                cout << "successful" << endl;
            }
        }
        else if (action == "printInorder") {
            avlTree.printInorder(rootTree);
            cout << endl;
        }
        else if (action == "printPreorder") {
            avlTree.printPreOrder(rootTree);
            cout << endl;
        }
        else if (action == "printPostorder") {
            avlTree.printPostOrder(rootTree);
            cout << endl;
        }
        else if (action == "printLevelCount") {
            avlTree.printLevelCount(rootTree);
        }
    }

    return 0;
}
