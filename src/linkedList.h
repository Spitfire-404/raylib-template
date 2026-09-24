#pragma once
#include <iterator>

template <typename T>
struct linkedList
{
public:

    T value;
    //null terminated
    linkedList *next = nullptr;
    linkedList(){};
    linkedList(T in): value(in){};
    linkedList(T in, linkedList *n): value(in), next(n){};

    void append(T data){
        linkedList<T> *current = this;
        while (current->next != nullptr)
        {
            current = current->next;
        }


        current->next = new linkedList<T>(data);
    };
     
    
};


