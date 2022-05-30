#ifndef NODE_HPP
#define NODE_HPP
#define MaxLength 128
// typedef int ElementType;
typedef int Position;

template <class ElementType>
class Node
{
public:
    Node();

private:
    ElementType data;

    LinkedList *prev;
    LinkedList *next;
};
#endif