// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <chrono>
#include <vector>

#undef RAND_MAX
#define RAND_MAX 4 * 1024 * 1024


struct Report
{
    int64_t directTime;
    int64_t reversTime;
    int64_t randomTime;
    int size;
};

Report RunTest(int size)
{
    Report report;
    report.size = size;

    int count = size / 4;
    // Массив размером в size байт
    int *arr = new int[count];

    for (int i = 0; i < count; ++i)
        arr[i] = (i + 1)%count;

    int t;

    // прогревание кеша
    for (int i = 0; i < count; ++i)
        t = arr[i];

    auto timer_on = std::chrono::high_resolution_clock::now();
    // Прямой доступ
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < count; ++j)
            t = arr[t];
    }
    auto timer_of = std::chrono::high_resolution_clock::now();
    report.directTime = std::chrono::duration_cast<std::chrono::milliseconds>(timer_of - timer_on).count();

    for (int i = count - 1; i >= 0; --i)
        arr[i] = i - 1;
    arr[0] = count - 1;

    // прогревание кеша
    for (int i = 0; i < count; ++i)
        t = arr[i];

    timer_on = std::chrono::high_resolution_clock::now();
    // обратный доступ
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < count; ++j)
            t = arr[t];
    }
    timer_of = std::chrono::high_resolution_clock::now();
    report.reversTime = std::chrono::duration_cast<std::chrono::milliseconds>(timer_of - timer_on).count();

    for (int i = 0; i < count; ++i)
        arr[i] = rand() % count;

    // прогревание кеша
    for (int i = 0; i < count; ++i)
        t = arr[i];

    timer_on = std::chrono::high_resolution_clock::now();
    // случайный доступ
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < count; ++j)
            t = arr[t];
    }
    timer_of = std::chrono::high_resolution_clock::now();
    report.randomTime = std::chrono::duration_cast<std::chrono::milliseconds>(timer_of - timer_on).count();

    delete[]arr;
    return report;
}

#endif // INCLUDE_HEADER_HPP_
