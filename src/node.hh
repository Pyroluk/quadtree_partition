#pragma once
#include <stdint.h>
#include <vector>
#include <stack>

using AddressType = uint64_t;

class Node;//forward declaration

class Node
{
    public:

        uint64_t objectCount;
        uint8_t lable;

        //one parent
        Node *parent;

        //four childs
        Node *a;
        Node *b;
        Node *c;
        Node *d;

        Node();
        Node(Node *parent, uint8_t lable);

        AddressType getAddress();
};
