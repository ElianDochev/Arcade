#include "MainMenu/MainMenu.hpp"
#include "Utils/FileReader.hpp"
#include "Utils/RGBReader.hpp"
#include <regex>
#include "Abstracts/IMediator.hpp"

using menu = Game::MainMenu;
namespace event = Game::Events;

bool menu::init(Core::IMediator *mediator)
{
    _mediator = mediator;
    _initResources();
    // libs and titles
    size_t size = graphLibs.size() + gameLibs.size() + 2;
    float offset = 0.f;
    for (size_t i = 0; i < size; i++)
    {
        _objects.push_back(std::make_unique<Display::Text>());
        _objects[i]->pos.x = 40;
        _objects[i]->pos.y = 25 + ((i + offset) * 5);
        _objects[i]->color = 0xFFFFFF;
        _objects[i]->backupColor = Display::AObject::WHITE;
        dynamic_cast<Display::Text *>(_objects[i].get())->path = "auriel";
        if (i == 0 || i == gameLibs.size() + 1) // Title text game or graph lib
        {
            _objects[i]->color = 0x7ec8e3;
            _objects[i]->backupColor = Display::AObject::MAGENTA;
            dynamic_cast<Display::Text *>(_objects[i].get())->FontSize = 20;
            if (i == 0) // Game title
                dynamic_cast<Display::Text *>(_objects[i].get())->text = "Game";
            else // Graphic title
            {
                offset = 2.f; // seperator from game and gpahic display
                _objects[i]->pos.y = 25 + ((i + offset) * 5);
                dynamic_cast<Display::Text *>(_objects[i].get())->text = "Graphical";
            }
        }
        else
            dynamic_cast<Display::Text *>(_objects[i].get())->FontSize = 15;
    }
    // score
    _objects.push_back(std::make_unique<Display::Text>());
    auto &text = dynamic_cast<Display::Text &>(*_objects.back());
    text.pos.x = 40;
    text.pos.y = 10;
    text.text = "Score : " + std::to_string(_mediator->getScore());
    text.color = 0x00ff00;
    text.backupColor = Display::AObject::GREEN;
    text.path = "auriel";
    text.FontSize = 20;
    // name_tag
    _objects.push_back(std::make_unique<Display::Text>());
    auto &name_tag = dynamic_cast<Display::Text &>(*_objects.back());
    name_tag.pos.x = 40;
    name_tag.pos.y = 15;
    name_tag.text = _mediator->getPlayerName();
    name_tag.color = 0xff0000;
    name_tag.backupColor = Display::AObject::RED;
    return true;
}

void menu::handleEvent(Events::AEvents &event)
{
    if (event.type == event::KeyboardEvent::KeyPressed)
    {
        if (_typeText) // if we are typing the name
        {
            auto &player = _mediator->getPlayerName();
            if (event.key == event::KeyboardEvent::BACKSPACE)
            {
                if (player.size() > 0)
                    player.pop_back();
                else
                {
                    _typeText = false;
                    player = "Enter your name";
                }
            }
            else if (event.key == event::KeyboardEvent::ENTER)
            {
                if (player.size() == 0)
                {
                    player = "Enter your name";
                }
                _typeText = false;
            }
            else if (event.key == event::KeyboardEvent::SPACE)
                player += " ";
            else if (event.key >= 32 && event.key <= 126)
                player += static_cast<char>(event.key);
            _mediator->setPlayerName(player);
            dynamic_cast<Display::Text *>(_objects.back().get())->text = player;
        }
        else if (event.key == event::KeyboardEvent::UP_ARROW || event.key == event::KeyboardEvent::KEY_W)
        {
            if (_selectedGame > 0)
                _selectedGame--;
            else
                _selectedGame = gameLibs.size() - 1;
        }
        else if (event.key == event::KeyboardEvent::DOWN_ARROW || event.key == event::KeyboardEvent::KEY_S)
        {
            if (_selectedGame < gameLibs.size() - 1)
                _selectedGame++;
            else
                _selectedGame = 0;
        }
        else if (event.key == event::KeyboardEvent::LEFT_ARROW || event.key == event::KeyboardEvent::KEY_A)
        {
            if (_selectedGraph > 0)
                _selectedGraph--;
            else
                _selectedGraph = graphLibs.size() - 1;
        }
        else if (event.key == event::KeyboardEvent::RIGHT_ARROW || event.key == event::KeyboardEvent::KEY_D)
        {
            if (_selectedGraph < graphLibs.size() - 1)
                _selectedGraph++;
            else
                _selectedGraph = 0;
        }
        else if (event.key == event::KeyboardEvent::ENTER) // corupts the mem if deleting is done here change to primer fuctioms instead
        {
            // std::cerr << "Graph: " << graphLibs[_selectedGraph] << std::endl;
            _mediator->changeGraph("./lib/" + graphLibs[_selectedGraph]);
            // std::cerr << "Game: " << gameLibs[_selectedGame] << std::endl;
            _mediator->changeGame("./lib/" + gameLibs[_selectedGame]);
        }
        else if (event.key == event::KeyboardEvent::KEY_P)
        {
            _typeText = true;
            _mediator->setPlayerName("");
            dynamic_cast<Display::Text *>(_objects.back().get())->text = "";
        }
        else if (event.key == event::KeyboardEvent::ESCAPE)
        {
            _mediator->exit();
        }
    }
    if (event.type == event::MouseEvent::MouseClick)
    {
        // std::cerr << "Mouse: " << mousePos.x << " , " << mousePos.y << " key: " << event.key << std::endl;
        if (event.key == event::MouseEvent::Left)
        {
            Game::Display::AObject::coordinates mousePos = static_cast<Game::Display::AObject::coordinates>(event.getMouse().value());
            for (size_t i = 0; i < gameLibs.size(); i++)
            {
                if (mousePos.x >= _objects[i + 1]->pos.x && mousePos.x <= _objects[i + 1]->pos.x + 10 && mousePos.y >= _objects[i + 1]->pos.y && mousePos.y <= _objects[i + 1]->pos.y + 5)
                    _selectedGame = i;
            }
            for (size_t i = 0; i < graphLibs.size(); i++)
            {
                if (mousePos.x >= _objects[i + gameLibs.size() + 2]->pos.x && mousePos.x <= _objects[i + gameLibs.size() + 2]->pos.x + 10 && mousePos.y >= _objects[i + gameLibs.size() + 2]->pos.y && mousePos.y <= _objects[i + gameLibs.size() + 2]->pos.y + 5)
                    _selectedGraph = i;
            }
            if (mousePos.x >= _objects.back()->pos.x && mousePos.x <= _objects.back()->pos.x + 10 && mousePos.y >= _objects.back()->pos.y && mousePos.y <= _objects.back()->pos.y + 5)
            {
                if (_typeText)
                    return;
                _typeText = true;
                _mediator->setPlayerName("");
                dynamic_cast<Display::Text *>(_objects.back().get())->text = "";
            }
        }
    }
}

std::vector<std::unique_ptr<Game::Display::AObject>> &menu::getObject()
{
    for (size_t i = 0; i < gameLibs.size(); i++)
    {
        if (i == _selectedGame)
        {
            _objects[i + 1]->color = 0x00FF00;
            _objects[i + 1]->backupColor = Display::AObject::GREEN;
        }
        else
        {
            _objects[i + 1]->color = 0xFFFFFF;
            _objects[i + 1]->backupColor = Display::AObject::WHITE;
        }
        dynamic_cast<Display::Text *>(_objects[i + 1].get())->text = gameLibs[i];
    }
    for (size_t i = 0; i < graphLibs.size(); i++)
    {
        if (i == _selectedGraph)
        {
            _objects[i + gameLibs.size() + 2]->color = 0x00FF00;
            _objects[i + gameLibs.size() + 2]->backupColor = Display::AObject::GREEN;
        }
        else
        {
            _objects[i + gameLibs.size() + 2]->color = 0xFFFFFF;
            _objects[i + gameLibs.size() + 2]->backupColor = Display::AObject::WHITE;
        }
        dynamic_cast<Display::Text *>(_objects[i + gameLibs.size() + 2].get())->text = graphLibs[i];
    }
    return _objects;
}

const std::vector<std::pair<std::string, std::string>> &menu::getResources() const
{
    return _resources;
}

void menu::_initResources()
{
    graphLibs = _mediator->getGraphLibs();
    gameLibs = _mediator->getGameLibs();
    auto indexs = _mediator->GetLibsIndex();
    _selectedGame = indexs.first;
    _selectedGraph = indexs.second;
}

extern "C"
{
    Core::IMod *GetModule(Core::IMediator *mediator)
    {
        Game::IGame *obj = new Game::MainMenu();
        obj->init(mediator);
        return obj;
    }
    Core::ModInfo GetHeader()
    {
        Core::ModInfo info;
        info.type = Core::ModInfo::Type::GAME;
        info.name = "MainMenu";
        return info;
    }
}
