#pragma once
#include <bits/stdc++.h>
#include <atomic>
using namespace std;
class SpinLock
{
private:
    atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock()
    {
        while (flag.test_and_set(memory_order_acquire))
            ;
    }

    void unlock()
    {
        flag.clear(memory_order_release);
    }
};