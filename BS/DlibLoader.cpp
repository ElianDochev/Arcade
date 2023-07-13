#include "../Headers/Utils/ReadDlib.hpp"

// compile from root g++ BS/DlibLoader.cpp Utils/src/ReadDlib.cpp -I./Headers

typedef void (*entry_point_t)();

int main(void)
{
    std::string libs[] = {"./BS/lib1.so", "./lib2.so", "./lib3.so"};

    DlibReader dsymread(libs[0]);
    LibLoader loader(dsymread);

    int tmp = loader.call<int, int, int>("add", 1, 2);
    int tmp2 = 2;

    std::cout << tmp << std::endl;
    loader.call("entry_point");
    loader.call("test", 1, 2);
    loader.call("test2", tmp, tmp2);
    std::cout << tmp << std::endl;

    // std::cout << "Lib path: " << reader.getLibPath() << std::endl;
    // entry_point_t entry_point = reader.getSymbol<entry_point_t>("entry_point");
    // entry_point();
    // if (reader.Open(libs[1]))
    // {
    //     std::cout << "yes" << std::endl;
    // }
    return 0;
    // for (auto lib : libs)
    // {
    //     void *handle = dlopen(lib.c_str(), RTLD_LAZY);
    //     if (!handle)
    //     {
    //         std::cerr << "Cannot open library: " << dlerror() << std::endl;
    //         return 1;
    //     }

    //     // load the symbol
    //     typedef void (*entry_point_t)();
    //     entry_point_t entry_point = (entry_point_t)dlsym(handle, "entry_point");
    //     if (!entry_point)
    //     {
    //         std::cerr << "Cannot load symbol 'entry_point': " << dlerror() << std::endl;
    //         return 1;
    //     }

    //     // use it to do the calculation
    //     entry_point();

    //     // close the library
    //     if (dlclose(handle))
    //     {
    //         std::cerr << "Cannot close library: " << dlerror() << std::endl;
    //         return 1;
    //     }
    // }
}