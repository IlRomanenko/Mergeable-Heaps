#pragma once
#include "Base.h"
#include "IMergeableHeap.h"

class BinominalHeap : public IMergeableHeap<int>
{
    enum {
        InitialSize = 1
    };

    struct BinominalTree
    {
        vector<BinominalTree*> children;
        int data, size;
    
        BinominalTree(const int& key)
        {
            data = key;
            size = 1;
        }

        ~BinominalTree()
        {
            for (int i = 0; i < children.size(); i++)
            {
                delete children[i];
                children[i] = nullptr;
            }
            /*
            for_each(children.begin(), children.end(), [](auto* tree) mutable
            {
                delete tree;
                tree = nullptr;
            });*/

            children.clear();
        }
    };

    typedef BinominalTree* Node;

    BinominalHeap(Node && tree)
    {
        heap.resize(InitialSize);
        heap[0] = tree;
        curSize = 1;
    }
    
    BinominalHeap(vector<Node> &nodes)
    {
        heap.swap(nodes);
        RecalcSize();
    }

    Node MergeTrees(Node first, Node second)
    {
        if (first->data < second->data)
        {
            first->children.push_back(second);
            first->size += second->size;
            return first;
        }
        else
        {
            second->children.push_back(first);
            second->size += first->size;
            return second;
        }
    }

    void MergeNodes(Node first, Node second, Node additional, Node &result, Node &new_additional)
    {
        if (first == nullptr)
        {
            if (second != nullptr)
                swap(first, second);
            else if (additional != nullptr)
                swap(first, additional);
        }
        if (second == nullptr)
        {
            if (additional != nullptr)
                swap(second, additional);
        }
        if (first != nullptr && second != nullptr)
        {
            result = additional;
            new_additional = MergeTrees(first, second);
        }
        else
        {
            result = first;
            new_additional = nullptr;
        }
    }

    void CompressSize()
    {
        if (heap.back() == nullptr && heap.size() > InitialSize)
            heap.pop_back();
    }

    void RecalcSize()
    {
        curSize = accumulate(heap.begin(), heap.end(), 0, [](int sum, Node ptr)
        {
            return sum + (ptr == nullptr ? 0 : ptr->size);
        });
    }

private:

    vector<Node> heap;

    int curSize;

public:

    BinominalHeap()
    {
        heap.resize(InitialSize);
        for_each(heap.begin(), heap.end(), [](BinominalTree *ptr) mutable
        {
            ptr = nullptr;
        });
        curSize = 0;
    }

    void AddElement(const int& object)
    {
        Meld(BinominalHeap(new BinominalTree(object)));
    }

    void MakeHeap(const vector<int> &v) override
    {
        for_each(v.begin(), v.end(), [this](int x) { AddElement(x); });
    }

    int PeekMin() const override
    {
        int min = INT_MAX, size = heap.size();
        for (uint i = 0; i < size; i++)
        {
            if (heap[i] != nullptr && heap[i]->data < min)
            {
                min = heap[i]->data;
            }
        }
        return min;
    }

    ///<summary>
    ///Extract minimum element from heap.
    ///</summary>
    int ExtractMin() override
    {
        uint size = heap.size();
        int min = INT_MAX, index = -1;
        for (uint i = 0; i < size; i++)
        {
            if (heap[i] != nullptr && heap[i]->data < min)
            {
                min = heap[i]->data;
                index = i;
            }
        }

        BinominalTree* tree = heap[index];
        heap[index] = nullptr;
        Meld(BinominalHeap(tree->children));
        tree->children.clear();
        delete tree;
        tree = nullptr;
        CompressSize();
        return min;
    }

    ///<summary> 
    ///Meld this heap with add_heap, add_heap will be destroyed. Trivial implementation for all kinds of heaps.
    ///</summary>
    void Meld(BinominalHeap &add_heap)
    {
        uint max_size = max(add_heap.heap.size(), heap.size());
        add_heap.heap.resize(max_size);
        heap.resize(max_size);
        
        BinominalTree *additional = nullptr, *result = nullptr, *new_additional = nullptr;

        for (uint i = 0; i < max_size; i++)
        {
            MergeNodes(heap[i], add_heap.heap[i], additional, result, new_additional);
            heap[i] = result;
            additional = new_additional;
            result = nullptr;
        }
        if (additional != nullptr)
            heap.push_back(additional);
        RecalcSize();
        add_heap.heap.clear();
    }

    bool IsEmpty() override
    {
        return (curSize == 0);
    }

    void Clear()
    {
        for (int i = 0; i < heap.size(); i++)
        {
            delete heap[i];
            heap[i] = nullptr;
        }
        curSize = 0;
    }

    ~BinominalHeap()
    {
        Clear();
    }
};
