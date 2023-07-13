#include <iostream>

extern "C"
{
    __attribute__((constructor)) void lib1()
    {
        std::cout << "lib3" << std::endl;
    }
    void entry_point()
    {
        std::cout << "entry_point 3" << std::endl;
    }
    __attribute__((destructor)) void lib1_exit()
    {
        std::cout << "lib3_exit" << std::endl;
    }
}