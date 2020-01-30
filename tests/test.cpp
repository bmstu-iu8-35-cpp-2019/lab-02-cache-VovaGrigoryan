// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>

TEST(Example, EmptyTest) {
    for (int i = 64; i <= 4 * 1024; i *= 2)
    {
        Report rep = RunTest(i * 1024);
        std::cout << "Size:" << rep.size << " ";
        std::cout << "Direct:" << rep.directTime << " ";
        std::cout << "Revers:" << rep.reversTime << " ";
        std::cout << "Random:" << rep.randomTime << std::endl;
    }
}
