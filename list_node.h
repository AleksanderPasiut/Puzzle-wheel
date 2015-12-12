#ifndef LIST_NODE_H
#define LIST_NODE_H

template<class DT> class CycleList;

template<class DT> class ListNode
{
private:
    DT data;
    
    ListNode* prior;
    ListNode* next;
    
private:
    ListNode() {}
    ListNode(const DT& in_data, ListNode* in_prior, ListNode* in_next);
    
    friend class CycleList<DT>;
};

template<class DT> ListNode<DT>::ListNode(const DT& in_data, ListNode* in_prior, ListNode* in_next)
    : data(in_data),
      prior(in_prior),
      next(in_next) {}

#endif
