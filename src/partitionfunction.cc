#include "partitionfunction.hh"

PartitionFunction::PartitionFunction(Node* quadtreeRoot)
{
    int numThreads = 4;
    int64_t numObjects = quadtreeRoot->objectCount;
    int64_t baseLine = numObjects / numThreads; //maybe round up
    int64_t currentSum = 0;

    std::vector<AddressType> splitNodeAddresses;

    std::stack<Node*> nodeStack;

    nodeStack.push(quadtreeRoot);

    while (!nodeStack.empty())
    {
        Node* currentNode = nodeStack.top();
        nodeStack.pop();

        //if its a leaf, increment counter
        if(currentNode->a == nullptr && currentNode->b == nullptr && currentNode->c == nullptr && currentNode->d == nullptr)
        {
            currentSum += currentNode->objectCount;

            //split, store Address of Node
            if(currentSum > baseLine)
            {
                splitNodeAddresses.push_back(currentNode->getAddress());
                currentSum = 0;
            }
        }

        //push childes on stack
        if (currentNode->d != nullptr)
            nodeStack.push(currentNode->d);
        if (currentNode->c != nullptr)
            nodeStack.push(currentNode->c);
        if (currentNode->b != nullptr)
            nodeStack.push(currentNode->b);
        if (currentNode->a != nullptr)
            nodeStack.push(currentNode->a);
    }

    this->numThreads = splitNodeAddresses.size() + 1;
    this->split_points = splitNodeAddresses;
}

int PartitionFunction::getThreadIdForAddress(AddressType address, int quadtreeDepth) const
{
    int ThreadId = 0;
    AddressType currentAddressBorder = split_points[ThreadId];

    //check if address is bigger than currentAddressBorder

    for(int k = 0; k < split_points.size(); k++)
    {
        for(int i = 0; i < quadtreeDepth; i++)
        {
            //if the addressborder is smaller than the address, next addressborder
            if((currentAddressBorder & (0x3 << i*2)) < (address & (0x3 << i*2)))
            {
                currentAddressBorder = split_points[++ThreadId];
                break;
            }
        }
    }

    return ThreadId;
}
