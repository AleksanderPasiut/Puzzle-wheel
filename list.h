#ifndef LIST_H
#define LIST_H

#include <stdexcept>
using namespace std;

#include "list_node.h"

template <class DT> class CycleList
{
private:
    CycleList(CycleList&) {}
    CycleList& operator= (CycleList&) {}

private:
    ListNode<DT>* cursor;
    
public:
    CycleList();
    ~CycleList();
    void insert(const DT& new_data);
    void remove();
    void replace(const DT& new_data);
    void clear();
    bool isEmpty() const;
    bool isFull() const;
    void gotoNext();
    void gotoPrior();
    DT* getCursor() const;
};

template<class DT> CycleList<DT>::CycleList()
{
    cursor = 0;
}

template<class DT> CycleList<DT>::~CycleList()
{
    clear();
}

template<class DT> void CycleList<DT>::insert(const DT& new_data)
{
    ListNode<DT>* new_list_node_ptr;
    
    if (cursor)
    {
        new_list_node_ptr = new ListNode<DT>(new_data, cursor, cursor->next);

        cursor->next->prior = new_list_node_ptr;
        cursor->next = new_list_node_ptr;        
    }
    else
    {
        new_list_node_ptr = new ListNode<DT>(new_data, 0, 0);
        new_list_node_ptr->next = new_list_node_ptr;
        new_list_node_ptr->prior = new_list_node_ptr;
    }
    
    cursor = new_list_node_ptr;
    return;
}

template<class DT> void CycleList<DT>::remove()
{
    if (!cursor)
        throw logic_error("list is empty");
    
    cursor->prior->next = cursor->next;
    cursor->next->prior = cursor->prior;
    
    delete cursor;
    return;
}

template<class DT> void CycleList<DT>::replace(const DT& new_data)
{
    if (!cursor)
        throw logic_error("list is empty");
    
    cursor->data = new_data;
    return;
}

template<class DT> void CycleList<DT>::clear()
{
    for (;;)
    {
        if (!cursor)
            break;
            
        cursor->prior->next = 0;
        ListNode<DT>* deleted_element_ptr = cursor;
        cursor = cursor->next;
        delete deleted_element_ptr;
    }
    
    cursor = 0;
    return;
}

template<class DT> bool CycleList<DT>::isEmpty() const
{
    return cursor;
}

template<class DT> bool CycleList<DT>::isFull() const
{
    ListNode<DT>* try_element = new ListNode<DT>;
    
    if (try_element)
    {
        delete try_element;
        return false;
    }
    else return true;
}

template<class DT> void CycleList<DT>::gotoNext()
{
    if (!cursor)
        throw logic_error("list is empty");
    
    cursor = cursor->next;
    return;
}

template<class DT> void CycleList<DT>::gotoPrior()
{
    if (!cursor)
        throw logic_error("list is empty");
    
    cursor = cursor->prior;
    return;
}

template<class DT> DT* CycleList<DT>::getCursor() const
{
    if (!cursor)
        throw logic_error("list is empty");
    
    return &(cursor->data);
}

#endif
