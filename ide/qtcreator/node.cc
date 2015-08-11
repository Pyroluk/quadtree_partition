#include "node.hh"

Node::Node()
{
    objectCount = 0;
    a = b = c = d = 0;

    //this->level = level;
}

/*Node* Node::createQuadtree(int levels, int currentLevel)
{
    if(currentLevel <= levels)
    {
        a = new Node(currentLevel);
        b = new Node(currentLevel);
        c = new Node(currentLevel);
        d = new Node(currentLevel);

        a->createQuadtree(levels, currentLevel--);
        b->createQuadtree(levels, currentLevel--);
        c->createQuadtree(levels, currentLevel--);
        d->createQuadtree(levels, currentLevel--);
    }

    return this;
}*/
