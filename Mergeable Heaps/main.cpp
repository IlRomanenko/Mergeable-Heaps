#define _CRT_SECURE_NO_WARNINGS
#include <vld.h>
#include "BinominalHeap.h"
#include "AVLTree.h"
#include "LeftistHeap.h"
#include <cstdio>
#include <queue>

#define m_p(x, y) make_pair(x, y)

void Binominal()
{
    BinominalHeap heap;

    int temp;

    vector<int> tv;
    for (int i = 0; i < 500; i++)
    {
        temp = rand();
        tv.push_back(temp);
        heap.AddElement(temp);
    }

    sort(tv.begin(), tv.end());

    for_each(tv.begin(), tv.end(), [](int x) { cout << x << ' '; });

    cout << endl;

    while (!heap.IsEmpty())
    {
        cout << heap.ExtractMin() << ' ';
    }
}

void Leftist()
{
    LeftistHeap heap;

    int temp;

    vector<int> tv;
    for (int i = 0; i < 300; i++)
    {
        temp = rand();
        tv.push_back(temp);
        heap.AddElement(temp);
    }

    sort(tv.begin(), tv.end());

    for_each(tv.begin(), tv.end(), [](int x) { cout << x << ' '; });

    cout << endl;

    while (!heap.IsEmpty())
    {
        cout << heap.ExtractMin() << ' ';
    }
}

int main()
{
    
    Leftist();
    system("pause");
    return 0;
}