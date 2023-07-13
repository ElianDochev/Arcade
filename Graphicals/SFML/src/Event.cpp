#include "../../../Headers/sfml/Sfml.hpp"

namespace ev = Game::Events;

bool sfml::CheckEvents()
{
    return !_events.empty();
}

std::vector<std::unique_ptr<ev::AEvents>> sfml::GetEvents()
{
    return std::move(_events);
}

void sfml::event_loop()
{
    _events.clear();
    while (_window.isOpen() && _window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::KeyPressed)
        {
            _parseEventKeyboard();
            _events.back()->type = ev::KeyboardEvent::KeyPressed;
        }
        if (_event.type == sf::Event::KeyReleased)
        {
            _parseEventKeyboard();
            _events.back()->type = ev::KeyboardEvent::KeyReleased;
        }
        if (_event.type == sf::Event::MouseButtonPressed)
        {
            ev::MouseEvent::Key key;
            ev::MouseEvent::Type type;
            if (_event.mouseButton.button == sf::Mouse::Left)
                key = ev::MouseEvent::Left;
            else if (_event.mouseButton.button == sf::Mouse::Middle)
                key = ev::MouseEvent::Middle;
            else if (_event.mouseButton.button == sf::Mouse::Right)
                key = ev::MouseEvent::Right;
            type = ev::MouseEvent::MouseClick;
            _events.push_back(std::make_unique<ev::MouseEvent>(key, _posToPercent(_event.mouseButton.x, _event.mouseButton.y), type));
        }
    }
}

void sfml::_parseEventKeyboard()
{
    if (_event.key.code >= sf::Keyboard::A && _event.key.code <= sf::Keyboard::Z)     // A to Z
        _events.push_back(std::make_unique<ev::KeyboardEvent>(_event.key.code + 65)); // 65 is the our own code for A
    else if (_event.key.code >= sf::Keyboard::Enter)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::ENTER));
    else if (_event.key.code >= sf::Keyboard::Space)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::SPACE));
    else if (_event.key.code >= sf::Keyboard::Num0 && _event.key.code <= sf::Keyboard::Num9)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(_event.key.code + 22)); // 22 is the our own code for 0
    else if (_event.key.code >= sf::Keyboard::Numpad0 && _event.key.code <= sf::Keyboard::Numpad9)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(_event.key.code - 75 + 48)); // 48 is the our own code for 0
    else if (_event.key.code >= sf::Keyboard::F1 && _event.key.code <= sf::Keyboard::F12)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(_event.key.code + 27)); // 112 is the our own code for F1
    else if (_event.key.code == sf::Keyboard::Up)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::UP_ARROW));
    else if (_event.key.code == sf::Keyboard::Down)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::DOWN_ARROW));
    else if (_event.key.code == sf::Keyboard::Left)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::LEFT_ARROW));
    else if (_event.key.code == sf::Keyboard::Right)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::RIGHT_ARROW));
    else if (_event.key.code == sf::Keyboard::LControl)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::CTRL));
    else if (_event.key.code == sf::Keyboard::LShift)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::SHIFT));
    else if (_event.key.code == sf::Keyboard::LAlt)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::ALT));
    else if (_event.key.code == sf::Keyboard::RControl)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::CTRL));
    else if (_event.key.code == sf::Keyboard::BackSpace)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::BACKSPACE));
    else if (_event.key.code == sf::Keyboard::Escape)
        _events.push_back(std::make_unique<ev::KeyboardEvent>(ev::KeyboardEvent::ESCAPE));
}

Game::Display::AObject::coordinates sfml::_posToPercent(int x, int y)
{
    if (_mediator->GetPositionMode() == false)
        return {(float)x, (float)y};
    auto size = _window.getSize();
    return {((float)x / size.x) * 100, ((float)y / size.y) * 100};
}

Game::Display::AObject::coordinates sfml::_posToPercent(float x, float y)
{
    if (_mediator->GetPositionMode() == false)
        return {x, y};
    auto size = _window.getSize();
    return {(x / size.x) * 100, (y / size.y) * 100};
}