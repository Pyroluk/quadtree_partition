#pragma once
#include <stdint.h>

class Node;//forward declaration

class Node
{
    public:

        uint64_t objectCount;

        //int level;

        //four childs
        Node *a;
        Node *b;
        Node *c;
        Node *d;

        Node();

        Node* createQuadtree(int levels, int currentLevel);
};
