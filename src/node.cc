#include "node.hh"

//used for root
Node::Node()
{
    objectCount = 0;
    a = b = c = d = parent = 0;
    lable = 0;
}

Node::Node(Node* parent, uint8_t lable)
{
    objectCount = 0;
    a = b = c = d = 0;
    this->parent = parent;
    this->lable = lable;
}

AddressType Node::getAddress()
{
    AddressType result = 0;

    Node* currentNode = this;
    while(currentNode->parent != 0)
    {
        //addresses are stored from left to right, fine to coarse
        result = (result << 2) + (currentNode->lable & 0x3);
        currentNode = currentNode->parent;
    }
    return result;
}
