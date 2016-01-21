#include "node.hh"

#include <algorithm>

namespace quadtree {

    //-------------------------------------------------------
    // Path
    //-------------------------------------------------------

    Path::Path():
        _x(0), _y(0), _level(0)
    {}

	Path::Path(std::vector<int16_t> address)
	{
		int _x = _y = _level = 0;
		for (auto& label : address)
		{	
			if (label < 0 || label > 3)
				throw std::runtime_error("ooooops!!");

			_x *= 2;
			_y *= 2;
			_level += 1;
			if (label & 0x1)
				_x += 1;
			if (label & 0x2)
				_y += 1;
		}
	}

    Path::Path(int x, int y, int level):
        _x(x), _y(y), _level(level)
    {}

    int Path::level() const {
        return static_cast<int>(_level);
    }

    int Path::x() const {
        return static_cast<int>(_x);
    }

    int Path::y() const {
        return static_cast<int>(_y);
    }

    int Path::size() const {
        return static_cast<int>(_level);
    }

    bool Path::operator==(const Path& other) const {
        return _x == other._x && _y == other._y && _level == other._level;
    }

    bool Path::operator<(const Path& other) const {
        auto n = static_cast<int>(std::min(_level,other._level));
        for (auto i=0;i<n;++i) {
            auto a = child(i);
            auto b = other.child(i);
            if (a < b)
                return true;
            else if (a > b)
                return false;
        }
        return _level < other.level();
    }

    ChildLabel Path::child(int index) const {
        return (*this)[index];
    }

    ChildLabel Path::operator[](int index) const {
        auto xbit = (_x & (1 << (_level - 1 - index))) ? 1 : 0;
        auto ybit = (_y & (1 << (_level - 1 - index))) ? 1 : 0;
        return (xbit + 2 * ybit);
    }

    void Path::push_back(ChildLabel child) {
        _x = 2 * _x + ((child & 0x1) ? 1ULL : 0ULL);
        _y = 2 * _y + ((child & 0x2) ? 1ULL : 0ULL);
        _level = _level + 1;
    }

    void Path::push_front(ChildLabel child) {
        _x = _x + (((child & 0x1) ? 1ULL : 0ULL) << _level);
        _y = _y + (((child & 0x2) ? 1ULL : 0ULL) << _level);
        _level = _level + 1;
    }

    std::ostream& operator<<(std::ostream& os, const Path& path) {
        for (auto i=0;i<path.size();++i) {
            os << (int) path[i];
        }
        return os;
    }

    //-------------------------------------------------------
    // Node Impl.
    //-------------------------------------------------------

    Node::Node(Node* parent, ChildLabel label):
        parent(parent),
        label(label)
    {}

    void Node::incrementCount() {
        ++this->objectCount;
    }

    Path Node::path() const
    {
        Path result;
        auto currentNode = this;
        while(currentNode->parent) {
            result.push_front(currentNode->label);
            currentNode = currentNode->parent;
        }
        return result;
    }

    //-------------------------------------------------------
    // Quadtree Impl.
    //-------------------------------------------------------

    bool QuadTree::empty() const {
        return _root.get() == nullptr;
    }

    QuadTree& QuadTree::insert(Path path) {
        if (empty()) {
            _root.reset(new Node());
        }
        auto u = _root.get();
        u->incrementCount();
        for (int i=0;i<path.size();++i) {
            auto child = path[i];
            // std::cout << (int) child << std::endl;
            if (!u->children[child]) {
                u->children[child].reset(new Node(u,child));
            }
            u = u->children[child].get();
            u->incrementCount();
        }
        return *this;
    }

    //-------------------------------------------------------
    // Iterator
    //-------------------------------------------------------

    Iterator::Iterator(const QuadTree &quadtree) {
        if (!quadtree.empty()) {
            stack.push_back(quadtree._root.get());
        }
    }

    ConstNodePtr Iterator::next() {
        while (!stack.empty()) {

            auto result = stack.back();
            stack.pop_back();

            auto children = 0;
            for (auto i=3;i>=0;--i) {
                if (result->children[i]) {
                    ++children;
                    stack.push_back(result->children[i].get());
                }
            }

            if (children == 0)
                return result;
        }
        return nullptr;
    }
}
