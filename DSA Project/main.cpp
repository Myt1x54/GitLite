#include<iostream>
#include<cstring>
#include "Btree.h"
#include <fstream>
#include <filesystem> // Include filesystem for directory operations
using namespace std;
namespace fs = std::filesystem; // Alias for filesystem namespace

int main() {
    // Create the folder named branch1
    const string folderName = "branch1";
    if (!fs::exists(folderName)) {
        fs::create_directory(folderName);
    }

    int order;
    cout << "Enter the order of the B-Tree: ";
    cin >> order;

    if (order < 3) {
        cerr << "Error: B-Tree order must be at least 3." << endl;
        return 1;
    }

    // Create the root node
    BTreeNode root(order);
    const char* folderPath = "branch1";

    // Insert some test values
    root.insert("10", "null", order, folderPath);
    root.insert("20", "null", order, folderPath);
    root.insert("30", "null", order, folderPath); // This will cause a split

    // Write the root node to a file
    const string rootPath = folderName + "/root_node.txt";
    root.writeToFile(rootPath.c_str());

    // Read the root node back from the file
    BTreeNode readNode(order);
    readNode.readFromFile(rootPath.c_str(), order);
    //readNode.printNode();

    return 0;
}