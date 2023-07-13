#include "../Headers/Utils/FileReader.hpp"

// compile from root g++ BS/readFile.cpp Utils/src/FileReader.cpp -I./Headers

int main()
{
    auto files = FileReader::listFiles("./lib");
    std::cout << "Files in current directory:" << std::endl;

    for (auto file : files)
    {
        std::cout << file << std::endl;
    }
}