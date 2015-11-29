#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

typedef unsigned int uint;

template <typename T> unique_ptr<T> make_unique(T* object)
{
    return unique_ptr<T>(object);
}