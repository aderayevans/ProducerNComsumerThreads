#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>



template<typename T>
class LinkedList
{
public:
    LinkedList ()
        : head(nullptr)
    {
    }

    void push_back(T data);
    int size();

    // void operator = (const Node& A)
    // {
    //     data = A.data;
    //     next = A.next;
    //     prev = A.prev;
    // }

    class Node;

    class Iterator;

    Iterator begin()
    {
        return Iterator(head);
    }
 
    // End of LInkedList wrapped in Iterator type
    Iterator end()
    {
        return Iterator(nullptr);
    }

    Iterator find(Iterator begin, Iterator end, T data)
    {
        while (begin != end)
        {
            if (*begin == data)
                return begin;
            ++begin;
        }
        return end;
    }

    class Iterator
    {
    public:
        Iterator()
            : current_Node (head) 
        {
        }
        Iterator(const Node* node)
            : current_Node (node)
        {
        }

        Iterator& operator=(Node* node)
        {
            this->current_Node = node;
            return *this;
        }
 
        // Prefix ++ overload
        Iterator& operator++()
        {
            if (current_Node)
                current_Node = current_Node->next;
            return *this;
        }
 
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
 
        bool operator!=(const Iterator& iterator)
        {
            return current_Node != iterator.current_Node;
        }
 
        T operator*()
        {
            return current_Node->data;
        }

    private:
        const Node* current_Node;
    };

    class Node
    {
    public:
        Node()
            : next(nullptr), prev(nullptr)
        {
        }

        Node(T data)
            : data(data), next(nullptr), prev(nullptr)
        {
        }

        T data;
        Node *next, *prev;
    };

    void erase(Iterator);

private:
    Node* head;
};

template <typename T>
void LinkedList<T>::push_back(T data)
{
    std::cout << "push_back " << data << std::endl;
    Node* new_node = new Node(data);
    // List is empty
    if (head == nullptr)
    {
        new_node->prev = nullptr;
        head = new_node;
        return;
    }
        Node* last = head;
    while (last->next != nullptr)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;
}


template <typename T>
int LinkedList<T>::size()
{
    int size = 0;
    if (head == nullptr) return 0;
    Node* last = head;
    while (last->next != nullptr)
    {
        last = last->next;
        size++;
    }
    size++;
    return size;
}


template <typename T>
void LinkedList<T>::erase(LinkedList<T>::Iterator it)
{
    std::cout << "erasing " << *it << std::endl;
    if (head == nullptr) return;

    if (head->data == *it) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* prev = head;
    Node* cur = head->next;
    while (cur != nullptr)
    {
        if (cur->data == *it)
            break;
        prev = cur;
        cur = cur->next;
    }
    if (cur == nullptr)
        std::cout << "Failed: No matching value" << std::endl;
    else
    {
        prev->next = cur->next;
        delete cur;
    }
}
// template<class T>
// class Iterator 
// {
// public:
//     Iterator(T* t_)
//         : t_(t_)
//     {
//     }

//     Iterator& operator++() {
//         t_ = t_->next;
//         return *this;
//     }

//     T const& operator*() const  {return *t_;}
//     T&       operator*()        {return *t_;}
//     T const* operator->() const {return t_;}
//     T*       operator->()       {return t_;}

//     bool operator==(Iterator b) const { return t_ == b.t_; }
//     bool operator!=(Iterator b) const { return t_ != b.t_; }

//     // Implement the rest of iterator interface.

// private:
//     T* t_;

// };
// template<typename T>
// Iterator<T> make_Iterator(T* val)   {return Iterator<T>(val);}
// template<typename T>
// Iterator<T> make_Iterator()         {return Iterator<T>{};}


// Iterator<Node> begin(Node* ptr)  {return make_Iterator(ptr);}
// Iterator<Node> end(Node*)        {return make_Iterator<Node>();}
#endif