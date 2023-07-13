#include "./Utils/ReadDlib.hpp"

#include <iostream>
#include <errno.h>
#include <string.h>

DlibReader::DlibReader(std::string const &libPath, size_t mode)
{
    handle = nullptr;
    Open(libPath, mode);
}

DlibReader::~DlibReader()
{
    if (handle)
        dlclose(handle);
}

void DlibReader::Open(std::string const &libPath, size_t mode)
{
    void *new_handle = dlopen(libPath.c_str(), mode);
    if (!new_handle)
    {
        std::cerr << "Open failed, reason: " << dlerror() << '\n';
        throw LibNotFoundException(libPath);
    }
    if (handle)
        dlclose(handle);
    this->libPath = libPath;
    handle = new_handle;
}
