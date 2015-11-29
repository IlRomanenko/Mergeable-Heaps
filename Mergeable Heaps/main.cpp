#include <vld.h>
#include "BinominalHeap.h"

int main()
{
    BinominalHeap heap;

    int temp;
    
    vector<int> tv;
    for (int i = 0; i < 100; i++)
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

    system("pause");
    return 0;
}