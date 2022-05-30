#include <iostream>
#include "linkedlist.hpp"

void LinkedList::insert(ElementType x, Position p) {
    if (l.size() == MaxLength)
        std::cout << "Failed: MaxLength reached\n";
    else if ((p > L.Last + 1) || (p <= 0))
        std::cout << "Failed: Position out of range\n";
    else {
        for (int index = L.Last; index > p - 1; index--) {
            L.Elements[index] = L.Elements[index - 1];
        }
        L.Elements[p - 1] = x;
        L.Last++;
    } 
}

void LinkedList::size()
{
    return size;
}

Position LinkedList::LOCATE(ElementType x, List L) {
    for (int index = 0; index < L.Last; index++) {
        if (L.Elements[index] == x) return index + 1;
    }
    return L.Last;
}

ElementType LinkedList::RETRIEVE(Position p, List L) {
    if ((p > L.Last) || (p <= 0)) {
        std::cout << "Failed: Position out of range\n";
        //return null;
        return 0;
    }
    else return L.Elements[p-1];
}

void LinkedList::DELETE_LIST(Position p, List &L) {
    if ((p > L.Last) || (p <= 0))
        std::cout << "Failed: Position out of range\n";
    else
        for (int index = p - 1; index < L.Last - 1; index++) {
            L.Elements[index] = L.Elements[index + 1];
        }
        L.Last--;
}

Position LinkedList::NEXT(Position p, List L) {
    if ((p > L.Last) || (p <= 0)) {
        std::cout << "Failed: Position out of range\n";
        return 0;
    }
    else return (p + 1);
}

Position LinkedList::PREVIOUS(Position p, List L) {
    if ((p > L.Last) || (p <= 0)) {
        std::cout << "Failed: Position out of range\n";
        return 0;
    }
    else return (p - 1);
}

Position LinkedList::FIRST(List L) {
    return 1;
}

bool LinkedList::EMPTY_LIST(List L) {
    if (L.Last == 0) return true;
    else return false;
}

void LinkedList::MAKENULL_LIST(List &L) {
    L.Last = 0;
}

//Extra abstract function
Position LinkedList::ENDLIST(List L) {
    return L.Last + 1;
}

void LinkedList::READ_LIST(List &L) {
    int amount;
    ElementType x;
    std::cout << "Nhap so phan tu danh sach: ";
    std::cin >> amount;
    for (int index = 0; index < amount; index++) {
        std::cout << "/<" << index + 1 << ">: ";
        std::cin >> x;
        INSERT_LIST(x, FIRST(L), L);
    }
}

void LinkedList::PRINT_LIST(List L) {
    std::cout << "List amount: " << L.Last << std::endl;
    for (int index = 0; index < L.Last; index++) {
        std::cout << "/<" << (index + 1) << ">: "
        << L.Elements[index] << std::endl;
    }
}