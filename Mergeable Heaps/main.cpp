#define _CRT_SECURE_NO_WARNINGS
#include <vld.h>
#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include "Heaps.h"

using namespace chrono;

class HeapTest : public ::testing::Test
{
protected:

    enum { Size = 1000, SpeedTestSize = 1000 * 100 };

    SkewHeap skewHeap;
    LeftistHeap leftistHeap;
    BinominalHeap binominalHeap;
    
    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {
        skewHeap.Clear();
        leftistHeap.Clear();
        binominalHeap.Clear();
    }

    
public:

    uniform_int_distribution<int> random;
    default_random_engine engine;
};


TEST_F(HeapTest, CanAddAndDeleteFromSkew)
{
    for (uint i = 0; i < Size; i++)
    {
        skewHeap.AddElement(i);
        EXPECT_EQ(false, skewHeap.IsEmpty());
    }
    skewHeap.Clear();
    EXPECT_EQ(true, skewHeap.IsEmpty());
}

TEST_F(HeapTest, CorrectSizeOfSkew)
{
    for (uint i = 0; i < Size; i++)
        skewHeap.AddElement(i);
    for (uint i = 0; i < Size; i++)
        EXPECT_EQ(i, skewHeap.ExtractMin());
}

TEST_F(HeapTest, CorrectExtractFromSkew)
{
    set<int> st;
    int temp;
    for (uint i = 0; i < Size; i++)
    {
        temp = random(engine);
        st.insert(temp);
        skewHeap.AddElement(temp);
    }

    while (!st.empty())
    {
        EXPECT_EQ(*st.begin(), skewHeap.PeekMin());
        st.erase(st.begin());
        skewHeap.ExtractMin();
    }
}

TEST_F(HeapTest, CanAddAndDeleteFromLeftist)
{
    for (uint i = 0; i < Size; i++)
    {
        leftistHeap.AddElement(i);
        EXPECT_EQ(false, leftistHeap.IsEmpty());
    }
    leftistHeap.Clear();
    EXPECT_EQ(true, leftistHeap.IsEmpty());
}

TEST_F(HeapTest, CorrectSizeOfLeftist)
{
    for (uint i = 0; i < Size; i++)
        leftistHeap.AddElement(i);
    for (uint i = 0; i < Size; i++)
        EXPECT_EQ(i, leftistHeap.ExtractMin());
}

TEST_F(HeapTest, CorrectExtractFromLeftist)
{
    set<int> st;
    int temp;
    for (uint i = 0; i < Size; i++)
    {
        temp = random(engine);
        st.insert(temp);
        leftistHeap.AddElement(temp);
    }

    while (!st.empty())
    {
        EXPECT_EQ(*st.begin(), leftistHeap.PeekMin());
        st.erase(st.begin());
        leftistHeap.ExtractMin();
    }
}

TEST_F(HeapTest, CanAddAndDeleteFromBinominal)
{
    for (uint i = 0; i < Size; i++)
    {
        binominalHeap.AddElement(i);
        EXPECT_EQ(false, binominalHeap.IsEmpty());
    }
    binominalHeap.Clear();
    EXPECT_EQ(true, binominalHeap.IsEmpty());
}

TEST_F(HeapTest, CorrectSizeOfBinominal)
{
    for (uint i = 0; i < Size; i++)
        binominalHeap.AddElement(i);
    for (uint i = 0; i < Size; i++)
        EXPECT_EQ(i, binominalHeap.ExtractMin());
}

TEST_F(HeapTest, CorrectExtractFromBinominal)
{
    set<int> st;
    int temp;
    for (uint i = 0; i < Size; i++)
    {
        temp = random(engine);
        st.insert(temp);
        binominalHeap.AddElement(temp);
    }

    while (!st.empty())
    {
        EXPECT_EQ(*st.begin(), binominalHeap.PeekMin());
        st.erase(st.begin());
        binominalHeap.ExtractMin();
    }
}


TEST_F(HeapTest, FastExtractFromSkew)
{
    set<int> st;
    vector<int> ans1, ans2, source;

    ans1.reserve(SpeedTestSize);
    ans2.reserve(SpeedTestSize);

    steady_clock clock;


    for (uint i = 0; i < SpeedTestSize; i++)
        source.push_back(random(engine));

    auto before_set_push = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
        st.insert(source[i]);

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        ans1.push_back(*st.begin());
        st.erase(st.begin());
    }

    auto after_set_pop = clock.now();

    auto before_heap_push = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
        skewHeap.AddElement(source[i]);

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        ans2.push_back(skewHeap.ExtractMin());
    }

    auto after_heap_pop = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        EXPECT_EQ(ans1[i], ans2[i]);
    }

    auto set_duration = after_set_pop - before_set_push;
    auto heap_duration = after_heap_pop - before_heap_push;

    cout << endl << endl;
    cout << "Set duration  : " << set_duration.count() / 1000.0 / 1000.0 << " ms" << endl;
    cout << "Skew duration : " << heap_duration.count() / 1000.0 / 1000.0 << " ms" << endl;
    cout << "Relative : " << heap_duration.count() / (double)set_duration.count() << endl;
    cout << endl << endl;
}


TEST_F(HeapTest, FastExtractFromLeftist)
{
    set<int> st;
    vector<int> ans1, ans2, source;

    ans1.reserve(SpeedTestSize);
    ans2.reserve(SpeedTestSize);

    steady_clock clock;


    for (uint i = 0; i < SpeedTestSize; i++)
        source.push_back(random(engine));

    auto before_set_push = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
        st.insert(source[i]);

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        ans1.push_back(*st.begin());
        st.erase(st.begin());
    }

    auto after_set_pop = clock.now();

    auto before_heap_push = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
        leftistHeap.AddElement(source[i]);

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        ans2.push_back(leftistHeap.ExtractMin());
    }

    auto after_heap_pop = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        EXPECT_EQ(ans1[i], ans2[i]);
    }

    auto set_duration = after_set_pop - before_set_push;
    auto heap_duration = after_heap_pop - before_heap_push;

    cout << endl << endl;
    cout << "Set     duration  : " << set_duration.count() / 1000.0 / 1000.0 << " ms" << endl;
    cout << "Leftist duration : " << heap_duration.count() / 1000.0 / 1000.0 << " ms" << endl;
    cout << "Relative : " << heap_duration.count() / (double)set_duration.count() << endl;
    cout << endl << endl;
}


TEST_F(HeapTest, FastExtractFromBinominal)
{
    set<int> st;
    vector<int> ans1, ans2, source;

    ans1.reserve(SpeedTestSize);
    ans2.reserve(SpeedTestSize);

    steady_clock clock;


    for (uint i = 0; i < SpeedTestSize; i++)
        source.push_back(random(engine));

    auto before_set_push = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
        st.insert(source[i]);

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        ans1.push_back(*st.begin());
        st.erase(st.begin());
    }

    auto after_set_pop = clock.now();

    auto before_heap_push = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
        binominalHeap.AddElement(source[i]);

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        ans2.push_back(binominalHeap.ExtractMin());
    }

    auto after_heap_pop = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        EXPECT_EQ(ans1[i], ans2[i]);
    }

    auto set_duration = after_set_pop - before_set_push;
    auto heap_duration = after_heap_pop - before_heap_push;

    cout << endl << endl;
    cout << "Set          duration  : " << set_duration.count() / 1000.0 / 1000.0 << " ms" << endl;
    cout << "BinominalHeap duration : " << heap_duration.count() / 1000.0 / 1000.0 << " ms" << endl;
    cout << "Relative : " << heap_duration.count() / (double)set_duration.count() << endl;
    cout << endl << endl;
}

TEST(SimpleTestCase, AVL)
{
    set<int> st;
    vector<int> ans1, ans2, source;

    const uint SpeedTestSize = 1000 * 100;

    ans1.reserve(SpeedTestSize);
    ans2.reserve(SpeedTestSize);

    steady_clock clock;

    uniform_int_distribution<int> random;
    default_random_engine engine;

    for (uint i = 0; i < SpeedTestSize; i++)
        source.push_back(random(engine));

    auto before_set_push = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
        st.insert(source[i]);

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        ans1.push_back(*st.begin());
        st.erase(st.begin());
    }

    auto after_set_pop = clock.now();


    p_avl root = nullptr;

    auto before_heap_push = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
        root = insert(root, source[i]);

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        ans2.push_back(getMin(root));
        root = removeMin(root);
    }

    auto after_heap_pop = clock.now();

    for (uint i = 0; i < SpeedTestSize; i++)
    {
        EXPECT_EQ(ans1[i], ans2[i]);
    }

    auto set_duration = after_set_pop - before_set_push;
    auto heap_duration = after_heap_pop - before_heap_push;

    cout << endl << endl;
    cout << "Set duration : " << set_duration.count() / 1000.0 / 1000.0 << " ms" << endl;
    cout << "AVL duration : " << heap_duration.count() / 1000.0 / 1000.0 << " ms" << endl;
    cout << "Relative : " << heap_duration.count() / (double)set_duration.count() << endl;
    cout << endl << endl;
}

int main(int argc, char** argv)
{
    cout.precision(9);
    cout.setf(cout.fixed);

    ::testing::InitGoogleTest(&argc, argv);

    RUN_ALL_TESTS();
    
    system("pause");

    return 0;
}