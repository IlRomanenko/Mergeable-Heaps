#pragma once
#include "Base.h"
#include "IMergeableHeap.h"


class LeftistHeap : public IMergeableHeap<int>
{
protected:
      
    struct LeftistTreeData
    {
        int key, dist;

        LeftistTreeData()
        {
            key = dist = 0;
        }

        LeftistTreeData(int value)
        {
            key = value;
            dist = 1;
        }

        LeftistTreeData(const LeftistTreeData &data)
        {
            key = data.key;
            dist = data.dist;
        }
        ~LeftistTreeData() { }
    };

    typedef BinaryTree<LeftistTreeData> LeftistTree;
    typedef LeftistTree* pTree;

    int getDist(pTree root)
    {
        if (!root)
            return 0;
        return root->Data().dist;
    }

    pTree MergeTrees(pTree first, pTree second)
    {
        if (first == nullptr)
            return second;
        if (second == nullptr)
            return first;

        if (first->Data().key > second->Data().key)
            swap(first, second);

        first->Right(MergeTrees(first->Right(), second));

        if (getDist(first->Right()) > getDist(first->Left()))
        {
            swap(first->Left(), first->Right());
        }

        first->Data().dist = min(getDist(first->Left()), getDist(first->Right())) + 1;

        return first;
    }

private:
    
    pTree root;

    LeftistHeap(pTree && nroot)
    {
        root = nroot;
    }

public:

    LeftistHeap() 
    {
        root = nullptr;
    }

    // Унаследовано через IMergeableHeap
    void AddElement(const int& object) override
    {
        Meld(LeftistHeap(new LeftistTree(LeftistTreeData(object))));
    }

    void MakeHeap(const vector<int>& v) override
    {
        for_each(v.begin(), v.end(), [this](int x)
        {
            AddElement(x);
        });
    }

    int PeekMin() const override
    {
        return root->Data().key;
    }

    int ExtractMin()
    {
        int result = root->Data().key;
        pTree nRoot = MergeTrees(root->Left(), root->Right());
        root = nRoot;
        return result;
    }


    void Meld(LeftistHeap &add_heap)
    {
        pTree nRoot = MergeTrees(root, add_heap.root);
        root = nRoot;
    }

    bool IsEmpty() override
    {
        return (root == nullptr);
    }

};