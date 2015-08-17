#pragma once

#include "node.hh"

#include <stdint.h>
#include <vector>

class PartitionFunction
{
    public:

        PartitionFunction(Node *quadtreeNodes);

        int getThreadIdForAddress(AddressType address, int quadtreeDepth) const;

        public:
            std::vector<AddressType> split_points;
            int numThreads = 0;
};
