#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#define MaxLength 128
// typedef int ElementType;
typedef int Position;

template <class ElementType>
class LinkedList {
public:
    LinkedList();
    void insert(ElementType x, Position p);
    int size();
    int count();

    ElementType RETRIEVE(Position p, List L);
    Position LOCATE(ElementType x, List L);
    void DELETE_LIST(Position p, List &L);
    Position NEXT(Position p, List L);
    Position PREVIOUS(Position p, List L);
    Position FIRST(List L);
    bool EMPTY_LIST(List L);
    void MAKENULL_LIST(List &L);
    Position ENDLIST(List L);
    void READ_LIST(List &L);
    void PRINT_LIST(List L);

private:
    ElementType data;

    LinkedList *prev;
    LinkedList *next;
};
#endif