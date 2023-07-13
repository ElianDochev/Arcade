#include <iostream>

extern "C"
{
    __attribute__((constructor)) void lib1()
    {
        std::cout << "lib1" << std::endl;
    }
    void entry_point()
    {
        std::cout << "entry_point 1" << std::endl;
    }
    int add(int a, int b)
    {
        return a + b;
    }
    void test(int a, int b)
    {
        std::cout << a + b << std::endl;
    }
    void test2(int &a, int &b)
    {
        a += b;
    }
    __attribute__((destructor)) void lib1_exit()
    {
        std::cout << "lib1_exit" << std::endl;
    }
}