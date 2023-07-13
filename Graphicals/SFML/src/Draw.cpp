#include "../../../Headers/sfml/Sfml.hpp"
#include "../../../Headers/Utils/RGBReader.hpp"

namespace obj = Game::Display;

bool sfml::refresh_screen()
{
    for (auto &object : drawableObjects)
    {
        _window.draw(*object);
    }
    _window.display();
    return true;
}

bool sfml::clear_screen()
{
    drawableObjects.clear();
    _window.clear(); // might need to move this to the refresh_screen function
    return true;
}

void sfml::draw(std::vector<std::unique_ptr<obj::AObject>> &objects)
{
    for (auto &object : objects)
    {
        auto type = object->getType();
        switch (type)
        {
        case obj::AObject::CIRCLE:
            draw(*dynamic_cast<obj::Circle *>(object.get()));
            break;
        case obj::AObject::RECTANGLE:
            draw(*dynamic_cast<obj::Rectangle *>(object.get()));
            break;
        case obj::AObject::TEXT:
            draw(*dynamic_cast<obj::Text *>(object.get()));
            break;
        case obj::AObject::LINE:
            draw(*dynamic_cast<obj::Line *>(object.get()));
            break;
        case obj::AObject::SPRITE:
            draw(*dynamic_cast<obj::Sprite *>(object.get()));
            break;
        default:
            throw obj::AObject::AObjectUnknownException();
        }
    }
}

bool sfml::draw(obj::Text &object)
{
    auto pos = pos_from_percent(object.pos);
    drawableObjects.push_back(std::make_unique<sf::Text>(object.text, _defaultFont, object.FontSize));
    auto &text = dynamic_cast<sf::Text &>(*drawableObjects.back());
    text.setPosition(pos.x, pos.y);
    text.setFillColor(sf::Color(obj::getRed(object.color), obj::getGreen(object.color), obj::getBlue(object.color)));
    auto size = text.getGlobalBounds();
    auto size2 = _posToPercent(size.width, size.height);
    object.hitbox = size2;
    return true;
}

bool sfml::draw(obj::Circle &object)
{
    auto pos = pos_from_percent(object.pos);
    drawableObjects.push_back(std::make_unique<sf::CircleShape>(object.radius));
    auto &circle = dynamic_cast<sf::CircleShape &>(*drawableObjects.back());
    circle.setPosition(pos.x, pos.y);
    circle.setFillColor(sf::Color(obj::getRed(object.color), obj::getGreen(object.color), obj::getBlue(object.color)));
    return true;
}

bool sfml::draw(obj::Rectangle &object)
{
    auto pos = pos_from_percent(object.pos);
    drawableObjects.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(object.width, object.height)));
    auto &rectangle = dynamic_cast<sf::RectangleShape &>(*drawableObjects.back());
    rectangle.setPosition(pos.x, pos.y);
    rectangle.setFillColor(sf::Color(obj::getRed(object.color), obj::getGreen(object.color), obj::getBlue(object.color)));
    return true;
}

bool sfml::draw(obj::Sprite &object)
{
    auto pos = pos_from_percent(object.pos);
    drawableObjects.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(object.sizeX, object.sizeY)));
    auto &rectangle = dynamic_cast<sf::RectangleShape &>(*drawableObjects.back());
    rectangle.setPosition(pos.x, pos.y);
    rectangle.setFillColor(sf::Color(obj::getRed(object.color), obj::getGreen(object.color), obj::getBlue(object.color)));
    return true;
}

sfml::_Line::_Line(obj::Line &object, sfml *sfml) : _line(sf::Lines, 2)
{
    auto pos = sfml->pos_from_percent(object.pos);
    _line[0].position = sf::Vector2f(pos.x, pos.y);
    _line[1].position = sf::Vector2f(object.x2, object.y2);
    _line[0].color = sf::Color(obj::getRed(object.color), obj::getGreen(object.color), obj::getBlue(object.color));
    _line[1].color = sf::Color(obj::getRed(object.color), obj::getGreen(object.color), obj::getBlue(object.color));
    _line.setPrimitiveType(sf::Lines);
}

void sfml::_Line::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_line, states);
}

bool sfml::draw(obj::Line &object)
{
    drawableObjects.push_back(std::make_unique<_Line>(object, this));
    return true;
}

obj::AObject::coordinates sfml::pos_from_percent(obj::AObject::coordinates pos)
{
    if (_mediator->GetPositionMode() == false)
        return pos;
        // return {pos.x * 3, pos.y * 3};
    auto size = _window.getSize();
    return (obj::AObject::coordinates){(pos.x * size.x) / 100, (pos.y * size.y) / 100};
}