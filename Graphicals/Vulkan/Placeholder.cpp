/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Placeholder
*/

#include <iostream>

#include "Placeholder.hpp"
#include "../../Headers/Abstracts/IGraphic.hpp"

Placeholder::Placeholder()
{
    std::cout << "Hello World!\n";
}

Placeholder::~Placeholder()
{
    std::cout << "Goodbye\n";
}

extern "C"
{
    Core::ModInfo GetHeader()
    {
        Core::ModInfo info;
        info.type = Core::ModInfo::Type::GRAPHIC;
        info.name = "Vulkan";
        return info;
    }
}