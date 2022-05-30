#include <iostream>
#include "node.hpp"

void Node::insert(ElementType x, Position p) {
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

Position Node::LOCATE(ElementType x, List L) {
    for (int index = 0; index < L.Last; index++) {
        if (L.Elements[index] == x) return index + 1;
    }
    return L.Last;
}

ElementType Node::RETRIEVE(Position p, List L) {
    if ((p > L.Last) || (p <= 0)) {
        std::cout << "Failed: Position out of range\n";
        //return null;
        return 0;
    }
    else return L.Elements[p-1];
}

void Node::DELETE_LIST(Position p, List &L) {
    if ((p > L.Last) || (p <= 0))
        std::cout << "Failed: Position out of range\n";
    else
        for (int index = p - 1; index < L.Last - 1; index++) {
            L.Elements[index] = L.Elements[index + 1];
        }
        L.Last--;
}

Position Node::NEXT(Position p, List L) {
    if ((p > L.Last) || (p <= 0)) {
        std::cout << "Failed: Position out of range\n";
        return 0;
    }
    else return (p + 1);
}

Position Node::PREVIOUS(Position p, List L) {
    if ((p > L.Last) || (p <= 0)) {
        std::cout << "Failed: Position out of range\n";
        return 0;
    }
    else return (p - 1);
}

Position Node::FIRST(List L) {
    return 1;
}

bool Node::EMPTY_LIST(List L) {
    if (L.Last == 0) return true;
    else return false;
}

void Node::MAKENULL_LIST(List &L) {
    L.Last = 0;
}

//Extra abstract function
Position Node::ENDLIST(List L) {
    return L.Last + 1;
}

void Node::READ_LIST(List &L) {
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

void Node::PRINT_LIST(List L) {
    std::cout << "List amount: " << L.Last << std::endl;
    for (int index = 0; index < L.Last; index++) {
        std::cout << "/<" << (index + 1) << ">: "
        << L.Elements[index] << std::endl;
    }
}