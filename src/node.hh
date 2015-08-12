#pragma once
#include <stdint.h>
#include <vector>

using AddressType = std::vector<int16_t>;

class Node;//forward declaration

class Node
{
    public:

        uint64_t objectCount;

        AddressType address;

        //int level;

        //four childs
        Node *a;
        Node *b;
        Node *c;
        Node *d;

        Node();
        Node(AddressType address);

        Node* createQuadtree(int levels, int currentLevel);

        std::vector<int> calculateSegmentation(Node *rootNode, int baseLine);
};
