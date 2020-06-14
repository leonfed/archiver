#ifndef TREE_H
#define TREE_H

#include <memory>

struct Node {
    Node(unsigned long long a, std::shared_ptr<Node> b, std::shared_ptr<Node> c, unsigned char d)
        : count(a)
        , left(b)
        , right(c)
        , byte(d)
    {}

    unsigned long long count;
    std::shared_ptr<Node> left, right;
    unsigned char byte;
};


#endif // TREE_H
