#ifndef TREE_H_
#define TREE_H_

//#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

class Tree {
  public:
    Node* root;
    Node* currNode;
    int expanded = 0;

    //initialize the tree
    Tree(Node* input_root) {
        this->root = input_root;
        this->currNode = input_root;
    }

};

#endif