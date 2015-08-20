#pragma once

#include <stdint.h>
#include <vector>

namespace partition_function {

using Part  = int;
using Count = uint64_t;

//----------------------------------------------------------
// PartitionFunction
//----------------------------------------------------------

template <typename Key>
struct PartitionFunction
{
public:
    PartitionFunction(int num_parts, Count total_count);
    void push(const Key& key, Count count);
    Part part(const Key& key);
    bool empty() const;
//public:
//    PartitionFunction(Node *quadtreeNodes);
//    int getThreadIdForAddress(AddressType address, int quadtreeDepth) const;
public:
    std::vector<Key> split_points;
    int              num_parts;
    Count            total_count;

    struct {
        Count count { 0 };
        Key   last_key;
        int   num_keys { 0 }; // in number of
    } group;
};

template <typename Key>
bool PartitionFunction<Key>::empty() const {
    return split_points.size() == 0;
}

template <typename Key>
PartitionFunction<Key>::PartitionFunction(int num_parts, Count total_count):
    num_parts(num_parts),
    total_count(total_count)
{}

#define xDEBUG_PARTITION_FUNCTION

template <typename Key>
void PartitionFunction<Key>::push(const Key& key, Count count) {
    auto threshold = total_count / num_parts;
    if (group.count + count < threshold) {
        group.last_key = key;
        ++group.num_keys;
        group.count += count;
    }
    else {
        if (group.num_keys == 0) {
            split_points.push_back(key);
#ifdef DEBUG_PARTITION_FUNCTION
            std::cerr << "adding split point at " << key << " count: " << count << std::endl;
#endif
        }
        else {
            auto diff_without = threshold - group.count;
            auto diff_with    = group.count + count - threshold;
            if (diff_without < diff_with) {
                split_points.push_back(group.last_key);
#ifdef DEBUG_PARTITION_FUNCTION
                std::cerr << "adding split point at " << group.last_key << " count: " << group.count << std::endl;
#endif
                group.count = count;
                group.last_key = key;
                group.num_keys = 1;
            }
            else {
#ifdef DEBUG_PARTITION_FUNCTION
                std::cerr << "adding split point at " << key << " count: " << group.count + count << std::endl;
#endif
                split_points.push_back(key);
                group.count    = 0;
                group.last_key = key;
                group.num_keys = 0;
            }
        }
    }
}

template <typename Key>
Part PartitionFunction<Key>::part(const Key& key) {
    auto it = std::lower_bound(split_points.begin(),
                               split_points.end(),
                               key);
    return static_cast<Part>(std::distance(split_points.begin(),it));
}

}



