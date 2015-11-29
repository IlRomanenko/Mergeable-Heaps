#pragma once
#include "Base.h"

template <typename T>
    class IMergeableHeap
{
public:
    virtual void AddElement(const T& object) = 0;
    virtual void MakeHeap(const vector<T> &v) = 0;
    virtual T PeekMin() const = 0;
    
    ///<summary>
    ///Extract minimum element from heap.
    ///</summary>
    virtual T ExtractMin() = 0;

    ///<summary> 
    ///Meld this heap with add_heap, add_heap will be destroyed. Trivial implementation for all kinds of heaps.
    ///</summary>
    virtual void Meld(IMergeableHeap<T> &add_heap)
    {
        while (!add_heap.IsEmpty())
        {
            AddElement(add_heap.ExtractMin());
        }
    }
    virtual bool IsEmpty() = 0;
    virtual ~IMergeableHeap() { }
};