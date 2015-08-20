#pragma once

#include <stdint.h>
#include <vector>
#include <stack>
#include <iostream>

namespace quadtree {

    using ChildLabel  = uint8_t;

    using Level = uint64_t;

    //----------------------------------------------------------
    // Path
    //----------------------------------------------------------

    struct Path {
    public:
        Path();
        Path(int x, int y, int level);
        int x() const;
        int y() const;
        int level() const;
        void push_back(ChildLabel child);
        void push_front(ChildLabel child);
        ChildLabel child(int index) const;
        ChildLabel operator[](int index) const;
        int size() const;

        bool operator==(const Path& other) const;
        bool operator<(const Path& other) const;

    public:
        struct {
            std::uint64_t _x: 29, _y: 29, _level: 6;
        };
    };

    std::ostream& operator<<(std::ostream& os, const Path& path);

    //----------------------------------------------------------
    // Node
    //----------------------------------------------------------

    class Node {
    public:
        Node() = default;
        Node(Node *parent, ChildLabel label);
        Path path() const;
        void incrementCount();
    public:
        uint64_t    objectCount { 0 };

        //one parent
        Node *parent { nullptr };

        ChildLabel  label { 0 };

        //four childs
        std::unique_ptr<Node> children[4];
    };

    //----------------------------------------------------------------
    // QuadTree
    //----------------------------------------------------------------

    struct QuadTree {
    public:
        QuadTree() = default;
        QuadTree& insert(Path path);
        bool empty() const;
    public:
        std::unique_ptr<Node> _root;
    };

    //----------------------------------------------------------------
    // Iterator
    //----------------------------------------------------------------

    using ConstNodePtr = const Node*;

    struct Iterator {
    public:
        Iterator(const QuadTree &quadtree);
        ConstNodePtr next();
    public:
        std::vector<ConstNodePtr> stack;
    };

}
