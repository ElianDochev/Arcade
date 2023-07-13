#include "../../../Headers/sfml/Sfml.hpp"
#include "../../../Headers/Utils/FileReader.hpp"
#include <signal.h>

bool sfml::init(Core::IMediator *mediator)
{
    _mediator = mediator;
    _window.create(sf::VideoMode(_width, _height), "Arcade");
    _window.setFramerateLimit(60);
    std::string fontPath = FileReader::getFontFilePath("Arial");
    if (fontPath.empty())
        throw std::runtime_error("Font not found");
    _defaultFont.loadFromFile(fontPath);
    return true;
}

sfml::~SFML()
{
    _window.close();
}

bool sfml::toClose()
{
    delete this;
    return true;
}

extern "C"
{
    Core::IMod *GetModule(Core::IMediator *mediator)
    {
        Graphical::IGraphic *obj = new sfml();
        obj->init(mediator);
        return obj;
    }
    Core::ModInfo GetHeader()
    {
        Core::ModInfo info;
        info.type = Core::ModInfo::Type::GRAPHIC;
        info.name = "SFML";
        return info;
    }
}