#include "node.hh"

//used for root
Node::Node()
{
    objectCount = 0;
    a = b = c = d = 0;

    AddressType address;
    address.push_back(-1);
    this->address = address;
}

Node::Node(AddressType address)
{
    objectCount = 0;
    a = b = c = d = 0;
    this->address = address;
}

std::vector<int> Node::calculateSegmentation(Node* rootNode, int baseLine)
{
    /*numbers from 0-4^quadtreelevels
    vector<AddressType> segmentation;


    //Baum durchlaufen, von oben nach unten

    //Wenn KnotenCount < Baseline ist, dann Adresse des Knoten speichern, wenn alle Geschwisterknoten auch kleiner sind als baseline, dann speicher die Adresse des Elternknotens










    int currentSum = 0;

    //traverse tree
    //childs first
    //if leafnode increment Count

    Node* currentNode = rootNode;

    if(currentNode->objectCount > baseLine)//check Childs
    {
        if(currentNode->a->objectCount > baseLine)
            ca
    }

    //it is a leafe node
    if(currentNode->a == NULL && currentNode->b == NULL && currentNode->c == NULL && currentNode->d == NULL)
    {
        currentSum += rootNode->objectCount;
    }
    else
    {
        currentNode = currentNode->a;
    }*/
}
