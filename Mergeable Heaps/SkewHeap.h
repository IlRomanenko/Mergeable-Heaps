#pragma once
#include "Base.h"
#include "IMergeableHeap.h"

class SkewHeap : public IMergeableHeap<int>
{
protected:

    struct SkewTreeData
    {
        int key;

        SkewTreeData()
        {
            key = 0;
        }

        SkewTreeData(int value)
        {
            key = value;
        }

        SkewTreeData(const SkewTreeData &data)
        {
            key = data.key;
        }
        ~SkewTreeData() { }
    };

    typedef BinaryTree<SkewTreeData> SkewTree;
    typedef SkewTree* pTree;

    pTree MergeTrees(pTree first, pTree second)
    {
        if (first == nullptr)
            return second;
        if (second == nullptr)
            return first;

        if (first->Data().key > second->Data().key)
            swap(first, second);

        first->Right(MergeTrees(first->Right(), second));

        swap(first->Left(), first->Right());

        return first;
    }

private:

    pTree root;

    SkewHeap(pTree && nroot)
    {
        root = nroot;
    }

    void ClearNode(pTree &node)
    {
        node->Left(nullptr);
        node->Right(nullptr);
        delete node;
        node = nullptr;
    }

public:

    SkewHeap()
    {
        root = nullptr;
    }

    // Унаследовано через IMergeableHeap
    void AddElement(const int& object) override
    {
        Meld(SkewHeap(new SkewTree(SkewTreeData(object))));
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

    int ExtractMin() override
    {
        int result = root->Data().key;
        pTree left = root->Left(), right = root->Right();
        ClearNode(root);
        root = MergeTrees(left, right);
        return result;
    }

    void Meld(SkewHeap &add_heap)
    {
        pTree nRoot = MergeTrees(root, add_heap.root);
        root = nRoot;
        add_heap.root = nullptr;
    }

    bool IsEmpty() override
    {
        return (root == nullptr);
    }

    void Clear() override
    {
        delete root;
        root = nullptr;
    }

    ~SkewHeap()
    {
        Clear();
    }
};