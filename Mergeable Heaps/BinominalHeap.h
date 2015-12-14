#pragma once
#include "Base.h"
#include "IMergeableHeap.h"
#include <list>

class BinominalHeap : public IMergeableHeap<int>
{
    enum {
        InitialSize = 1
    };

    struct BinominalTree
    {
        int data, size;
        BinominalTree *subTree, *prevTree;

        BinominalTree(const int &key)
        {
            data = key;
            size = 1;
            subTree = prevTree = nullptr;
        }
        ~BinominalTree()
        {
            delete subTree;
            delete prevTree;
            subTree = prevTree = nullptr;
        }
    };

    typedef BinominalTree* Node;

    vector<Node> getChildren(Node root)
    {
        root = root->subTree;
        vector<Node> v;
        while (root != nullptr)
        {
            v.push_back(root);
            root = root->prevTree;
        }
        for_each(v.begin(), v.end(), [](Node &ptr) mutable
        {
            ptr->prevTree = nullptr;
        });
        reverse(v.begin(), v.end());
        return v;
    }

    void AddSubTree(Node &root, Node &additional)
    {
        additional->prevTree = root->subTree;
        root->subTree = additional;
        root->size += additional->size;
    }

    BinominalHeap(Node && tree)
    {
        heap.resize(InitialSize);
        heap[0] = tree;
        curSize = 1;
    }

    BinominalHeap(vector<Node> & nodes)
    {
        heap.swap(nodes);
        RecalcSize();
    }

    BinominalHeap(vector<Node> && nodes)
    {
        heap.swap(nodes);
        RecalcSize();
    }

    Node MergeTrees(Node first, Node second)
    {
        if (first->data < second->data)
        {
            AddSubTree(first, second);
            return first;
        }
        else
        {
            AddSubTree(second, first);
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
        while (heap.back() == nullptr && heap.size() > InitialSize)
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
        for_each(heap.begin(), heap.end(), [](Node &ptr) mutable
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

        Node tree = heap[index];
        heap[index] = nullptr;
        Meld(BinominalHeap(getChildren(tree)));
        tree->subTree = nullptr;
        delete tree;
        tree = nullptr;
        CompressSize();
        return min;
    }

    void Meld(IMergeableHeap <int> *heap)
    {
        if (heap is BinominalHeap)
           Meld (*heap);
        else
           while (!heap->IsEmpty ())
           {
               AddElement (heap->ExtractMin ());
           }
    }

    void Meld(BinominalHeap &add_heap)
    {
        uint max_size = max(add_heap.heap.size(), heap.size());
        add_heap.heap.resize(max_size);
        heap.resize(max_size);

        Node additional = nullptr, result = nullptr, new_additional = nullptr;

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
        for_each(heap.begin(), heap.end(), [](Node &ptr) mutable
        {
            delete ptr;
            ptr = nullptr;
        });
        curSize = 0;
    }

    ~BinominalHeap()
    {
        Clear();
    }
};
