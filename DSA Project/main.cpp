#include<iostream>
#include<cstring>
#include "Btree.h"
#include <fstream>
#include <filesystem> // Include filesystem for directory operations
#include <sstream> 
#include<ctime>
#include<cstdlib>
using namespace std;
namespace fs = std::filesystem; // Alias for filesystem namespace


int main() {
    int order;
    cout << "Enter the order of the B-Tree: ";
    cin >> order;

    BTree btree(order);

    srand(time(0));

  /*  btree.insert(10);
    btree.insert(20);
    btree.insert(5);
    btree.insert(6);
    btree.insert(12);
    btree.insert(30);
    btree.insert(7);
    btree.insert(17);*/

    /*for (int i = 0; i < 100; i++)
    {
        btree.insert(i);
    }*/


    btree.insert(74);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(38);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(99);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(27);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(81);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(47);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(3);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    //btree.insert(84);
    btree.insert(25);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(55);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(9);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(35);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(77);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(13);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(44);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(48);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(92);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(80);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(75);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(95);
    cout << "B-Tree Structure:" << endl;
    btree.printTree();
    btree.insert(58);
    btree.insert(11);
    btree.insert(1);
    btree.insert(61);
    btree.insert(26);
    btree.insert(37);
    btree.insert(88);
    btree.insert(72);
    btree.insert(66);
    btree.insert(22);
    btree.insert(55);
    btree.insert(59);
    btree.insert(20);
    btree.insert(71);
    btree.insert(23);
    btree.insert(15);
    btree.insert(67);
    btree.insert(18);
    btree.insert(63);
    btree.insert(85);
    btree.insert(70);
    btree.insert(33);
    btree.insert(39);
    btree.insert(65);
    btree.insert(4);
    btree.insert(32);
    btree.insert(40);
    btree.insert(97);
    btree.insert(43);
    btree.insert(60);
    btree.insert(28);
    btree.insert(17);
    btree.insert(50);
    btree.insert(19);
    btree.insert(21);
    btree.insert(93);
    btree.insert(68);
    btree.insert(30);
    btree.insert(49);
    btree.insert(76);
    btree.insert(41);
    btree.insert(64);
    btree.insert(10);
    btree.insert(25);
    btree.insert(34);
    btree.insert(51);
    btree.insert(53);
    btree.insert(5);
    btree.insert(46);
    btree.insert(52);
    btree.insert(82);
    btree.insert(69);
    btree.insert(6);
    btree.insert(36);
    btree.insert(56);
    btree.insert(14);
    btree.insert(78);
    btree.insert(73);
    btree.insert(90);
    btree.insert(29);
    btree.insert(62);
    btree.insert(12);
    btree.insert(18);
    btree.insert(8);
    btree.insert(42);
    btree.insert(79);
    btree.insert(24);
    btree.insert(94);
    btree.insert(16);
    btree.insert(98);
    btree.insert(86);
    btree.insert(83);
    btree.insert(7);
    btree.insert(31);
    btree.insert(45);
    btree.insert(49);
    btree.insert(65);
    btree.insert(91);
    btree.insert(93);
    btree.insert(60);
    btree.insert(65);
    btree.insert(41);
    btree.insert(83);
    btree.insert(25);
    btree.insert(19);
    btree.insert(99);
    btree.insert(62);
    btree.insert(28);
    btree.insert(63);
    btree.insert(86);
    btree.insert(54);
    btree.insert(87);
    btree.insert(34);

    cout << "B-Tree Structure:" << endl;
    btree.printTree();

    return 0;
}


