#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class BTreeNode {
public:
    char parentPath[100];       // Path to the parent node file
    char** keys;                // Dynamic array for keys
    char** childPaths;          // Dynamic array for child node file paths
    int numKeys;                // Current number of keys in the node
    int maxKeys;                // Maximum keys in the node (order - 1)

    BTreeNode(int order) {
        maxKeys = order - 1;    // Max keys = order - 1
        numKeys = 0;
        strcpy_s(parentPath, "null");

        // Allocate memory for keys
        keys = new char* [maxKeys + 1]; // Allocate an extra slot for temporary overflow during split
        for (int i = 0; i <= maxKeys; ++i) {
            keys[i] = new char[50];
            memset(keys[i], '\0', 50); // Initialize with zeros
        }

        // Allocate memory for child paths
        childPaths = new char* [order + 1];
        for (int i = 0; i < order + 1; ++i) {
            childPaths[i] = new char[100];
            strcpy(childPaths[i], "null"); // Initialize as "null"
        }
    }

    ~BTreeNode() {
        for (int i = 0; i <= maxKeys; ++i) {
            delete[] keys[i];
        }
        delete[] keys;

        for (int i = 0; i < maxKeys + 2; ++i) {
            delete[] childPaths[i];
        }
        delete[] childPaths;
    }

    // Function to insert a new key and handle split if needed
    void insert(const char* newKey, const char* newChildPath, int order, const string& folderPath) {
        // Insert the new key in sorted order
        int i = numKeys - 1;
        while (i >= 0 && strcmp(newKey, keys[i]) < 0) {
            strcpy(keys[i + 1], keys[i]);            // Shift keys
            strcpy(childPaths[i + 2], childPaths[i + 1]); // Shift child paths
            i--;
        }
        strcpy(keys[i + 1], newKey);                // Place the new key
        strcpy(childPaths[i + 2], newChildPath);    // Place the new child path
        numKeys++;

        // Check if the node exceeds maxKeys
        if (numKeys > maxKeys) {
            splitNode(order, folderPath);
        }
    }

    void splitNode(int order, const string& folderPath) {
        // Middle index for splitting
        int midIndex = numKeys / 2;

        // Create the right half node
        BTreeNode newRightNode(order);
        for (int i = midIndex + 1; i < numKeys; ++i) {
            // Copy keys and child paths to the right node
            strcpy(newRightNode.keys[i - midIndex - 1], keys[i]);
            strcpy(newRightNode.childPaths[i - midIndex - 1], childPaths[i]);
        }
        strcpy(newRightNode.childPaths[numKeys - midIndex - 1], childPaths[numKeys]);
        newRightNode.numKeys = numKeys - midIndex - 1;

        // Update the current (left) node
        numKeys = midIndex;

        // Promote the middle key
        const char* midKey = keys[midIndex];

        // Generate file paths for the left and right nodes
        string leftNodePath = folderPath + "/leftnode.txt";
        string rightNodePath = folderPath + "/rightnode.txt";

        // Write the updated left and right nodes to files
        this->writeToFile(leftNodePath.c_str());
        newRightNode.writeToFile(rightNodePath.c_str());

        // Handle the parent node
        if (strcmp(parentPath, "null") != 0) {
            // Update the existing parent
            BTreeNode parent(order);
            parent.readFromFile(parentPath, order);
            parent.insert(midKey, rightNodePath.c_str(), order, folderPath);
            parent.writeToFile(parentPath);
        }
        else {
            // No parent exists: create a new root
            BTreeNode newRoot(order);
            strcpy(newRoot.keys[0], midKey);                  // Promote the middle key to the root
            strcpy(newRoot.childPaths[0], leftNodePath.c_str());
            strcpy(newRoot.childPaths[1], rightNodePath.c_str());
            newRoot.numKeys = 1;

            // Write the new root to file
            string rootPath = folderPath + "/root_node.txt";
            newRoot.writeToFile(rootPath.c_str());

            // Update parent paths for the left and right nodes
            strcpy(this->parentPath, rootPath.c_str());
            strcpy(newRightNode.parentPath, rootPath.c_str());
            this->writeToFile(leftNodePath.c_str());
            newRightNode.writeToFile(rightNodePath.c_str());
        }
    }

    void writeToFile(const char* filePath) {
        ofstream file(filePath, ios::out | ios::trunc);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filePath << endl;
            return;
        }

        // Write parent path
        file << parentPath << endl;

        // Write keys
        for (int i = 0; i < numKeys; ++i) {
            file << keys[i] << endl;
        }

        // Write child paths
        for (int i = 0; i <= numKeys; ++i) {
            file << childPaths[i] << endl;
        }

        // Fill remaining keys and child paths with "null"
        for (int i = numKeys; i < maxKeys + 1 - 1; ++i) {
            file << "null" << endl;
        }
        /*for (int i = numKeys + 1; i < maxKeys + 1; ++i) {
            file << "null" << endl;
        }*/

        file.close();
    }

    void readFromFile(const char* filePath, int order) {
        ifstream inFile(filePath);
        if (!inFile) {
            cerr << "Error: Unable to read from file " << filePath << endl;
            return;
        }

        inFile >> numKeys;
        inFile.ignore(); // Skip newline
        inFile.getline(parentPath, 100);

        for (int i = 0; i < numKeys; ++i) {
            inFile.getline(keys[i], 50);
        }
        for (int i = 0; i <= numKeys; ++i) {
            inFile.getline(childPaths[i], 100);
        }

        inFile.close();
    }
};
