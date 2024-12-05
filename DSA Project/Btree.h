#pragma once
#pragma warning(disable : 4996)
#include<iostream>
#include <fstream>
#include <sstream>
#include <filesystem> // Include filesystem for directory operations
#include <cstring>
using namespace std;
namespace fs = std::filesystem;

int nodeCounter = 0;

struct bnode {
    int* data;
    bnode** child;
    int order;
    int numkey;
    char filePath[100];    // File path to store the node data
    char parentPath[100];  // Path to the parent node file

    bnode(int neworder, int nodeCounter = 0) {
        order = neworder;
        numkey = 0;
        data = new int[order];
        child = new bnode * [order + 1];

        // Initialize children pointers and data
        for (int i = 0; i < order + 1; i++) {
            child[i] = nullptr;
        }
        for (int i = 0; i < order; i++) {
            data[i] = 0;
        }

        // Initialize parent path and file path
        strcpy(parentPath, "null");
        std::ostringstream oss;
        oss << "branch1/node_" << nodeCounter << ".txt";
        strcpy(filePath, oss.str().c_str());
    }

    void writeToFile() {
        std::ofstream file(filePath, std::ios::out | std::ios::trunc);
        if (!file) {
            std::cerr << "Error: Unable to open file " << filePath << std::endl;
            return;
        }

        file << parentPath << endl;
        file << numkey << endl;

        // Write keys
        for (int i = 0; i < numkey; ++i) {
            file << data[i] << endl;
        }

        // Write child paths
        for (int i = 0; i < order + 1; ++i) {
            if (child[i] != nullptr)
                file << child[i]->filePath << endl; // Save child path
            else
                file << "null" << endl;
        }

        file.close();
    }

    void readFromFile(const char* path) {
        std::ifstream file(path);
        if (!file) {
            std::cerr << "Error: Unable to read file " << path << std::endl;
            return;
        }

        strcpy(filePath, path);
        file.getline(parentPath, 100);
        file >> numkey;
        file.ignore();

        for (int i = 0; i < numkey; ++i) {
            file >> data[i];
        }

        for (int i = 0; i < order + 1; ++i) {
            char childPath[100];
            file.getline(childPath, 100);
            if (strcmp(childPath, "null") != 0) {
                child[i] = new bnode(order, i); // Temporary initialization
                strcpy(child[i]->filePath, childPath);
            }
            else {
                child[i] = nullptr;
            }
        }

        file.close();
    }

    void insertkey(int newdata, bnode* parent, int kahakrna, bnode*& root) {
        data[numkey] = newdata;
        numkey++;

        // Sort the keys in ascending order
        for (int i = 0; i < numkey; i++) {
            for (int j = 0; j < numkey - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    int tempdata = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = tempdata;
                }
            }
        }

        // Save the current node to file
        writeToFile();

        if (numkey == order) {
            splitnode(parent, kahakrna, root);
        }
    }

    void splitnode(bnode* parent, int kahakrna, bnode*& root)
    {
        bnode* newnode = new bnode(order, ++nodeCounter);
        int midindex = numkey / 2;

        for (int i = midindex + 1; i < numkey; i++)
        {
            newnode->data[i - midindex - 1] = data[i];
            newnode->numkey++;
        }

        for (int i = midindex; i <= order; i++)
        {
            if (child[i] != nullptr) {
                newnode->child[i - midindex] = child[i];
                strcpy(newnode->child[i - midindex]->parentPath, newnode->filePath);
                child[i] = nullptr; // Clear the reference in the current node

            }
        }

        numkey = midindex;

        int midvalue = data[midindex];
        data[midindex] = 0;

        if (parent == nullptr)
        {
            parent = new bnode(order, ++nodeCounter);
            parent->data[0] = midvalue;
            parent->child[0] = this;
            parent->child[1] = newnode;
            parent->numkey = 1;
            root = parent;
            // Update parent and save the nodes
            strcpy(this->parentPath, parent->filePath);
            strcpy(newnode->parentPath, parent->filePath);

            parent->writeToFile();
            newnode->writeToFile();
            writeToFile();

            return;
        }

        parent->insertkey(midvalue, nullptr, kahakrna, root);

        for (int i = parent->numkey; i > kahakrna + 1; i--)
        {
            parent->child[i] = parent->child[i - 1];
        }
        parent->child[kahakrna + 1] = newnode;

        // Update parent and child relationships
        strcpy(newnode->parentPath, parent->filePath);

        // Save the parent, current, and new nodes to their respective files
        parent->writeToFile();
        newnode->writeToFile();
        writeToFile();
    }


    void printnodedata() {
        for (int i = 0; i < numkey; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void printTree(bnode* node, int depth = 0) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < depth; i++) {
            cout << "|-";
        }
        node->printnodedata();

        for (int i = 0; i <= node->numkey; i++) {
            printTree(node->child[i], depth + 1);
        }
    }
};



class BTree {
private:
    bnode* root;
    int order;
    int nodeCounter;

public:
    BTree(int neworder) {
        order = neworder;
        root = nullptr;
        nodeCounter = 1;

        // Ensure the folder `branch1` exists
        if (!fs::exists("branch1")) {
            fs::create_directory("branch1");
        }
    }

    void insert(int newdata) {
        if (root == nullptr) {
            root = new bnode(order, nodeCounter++);
            root->insertkey(newdata, nullptr, 0, root);
        }
        else {
            bnode* temp = root;
            bnode* parent = nullptr;
            int kahakrna = 0;

            while (true) {
                if (temp->child[0] == nullptr) { // If it's a leaf node
                    temp->insertkey(newdata, parent, kahakrna, root);
                    return;
                }

                parent = temp;
                kahakrna = insertkahakrna(temp, newdata);
                if (kahakrna == -2) {
                    kahakrna = 0;
                }
                else if (kahakrna == -1) {
                    kahakrna = temp->numkey;
                }

                temp = temp->child[kahakrna];
            }
        }
    }

    void printTree() {
        if (root != nullptr) {
            root->printTree(root);
        }
    }

    int insertkahakrna(bnode* newnode, int newdata) {
        if (newdata < newnode->data[0]) {
            return -2; // Leftmost child
        }
        if (newdata > newnode->data[newnode->numkey - 1]) {
            return -1; // Rightmost child
        }

        for (int i = 0; i < newnode->numkey - 1; i++) {
            if (newdata > newnode->data[i] && newdata < newnode->data[i + 1]) {
                return i + 1; // Middle child
            }
        }
        return -1; // Default to rightmost
    }
};



