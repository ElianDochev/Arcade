#include "../Headers/Core/CoreMediator.hpp"
#include "Utils/FileReader.hpp"

#include <functional>

#include <iostream>

#include <regex>

Core::CoreMediator::CoreMediator(const char *graphic_lib)
    : graphic_reader_(graphic_lib),
      menu_graphic_lib(graphic_lib)
{
    _initResources();
    game_reader_.Open(MainMenuLib);
    initGame();
    initGraph();
}

void Core::CoreMediator::changeGame(const std::string &game)
{
    pendingChanges.gameChange = true;
    pendingChanges.pendingGame = game;
}

void Core::CoreMediator::changeGraph(const std::string &graphic)
{
    pendingChanges.graphicChange = true;
    pendingChanges.pendingGraphic = graphic;
}

void Core::CoreMediator::initGame()
{
    auto game_handler = game_reader_.getSymbol<Game::IGame *(*)(Core::IMediator *)>("GetModule");
    game = game_handler(this);
}

void Core::CoreMediator::initGraph()
{
    auto graphic_handler = graphic_reader_.getSymbol<Graphical::IGraphic *(*)(Core::IMediator *)>("GetModule");
    graphics = graphic_handler(this);
}

void Core::CoreMediator::returnToMenu()
{
    changeGame(MainMenuLib);
    changeGraph(menu_graphic_lib);
}

void Core::CoreMediator::ExecChanges()
{
    if (pendingChanges.gameChange)
    {
        getGame()->toClose();
        game_reader_.Open(pendingChanges.pendingGame);
        initGame();
        pendingChanges.gameChange = false;
    }
    if (pendingChanges.graphicChange)
    {
        pendingChanges.graphicChange = false;
        // if (pendingChanges.pendingGraphic == "SFML" && pendingChanges.pendingGame != "MainMenu")
        //     return;
        getGraphic()->toClose();
        if (pendingChanges.pendingGraphic[0] == '.') {
            graphic_reader_.Open(pendingChanges.pendingGraphic);
        } else {
            graphic_reader_.Open("./lib/" + pendingChanges.pendingGraphic);
        }
        initGraph();
    }
}

void Core::CoreMediator::changeGraphLib(int dir)
{
    if (dir == 1)
    {
        if (graphicIndex + 1 < graphLibs.size())
            graphicIndex++;
        else
            graphicIndex = 0;
    }
    else if (dir == -1)
    {
        if ((long)graphicIndex - 1 >= 0)
            graphicIndex--;
        else
            graphicIndex = graphLibs.size() - 1;
    }
    else
    {
        return;
    }
    // LibLoader readerGame(game_reader_);
    // LibLoader readerGraphic(graphic_reader_);
    // auto grafMod = readerGraphic.call<Core::ModInfo>("GetHeader");
    // auto gameMod = readerGame.call<Core::ModInfo>("GetHeader");

    // if (grafMod.name == "SFML" && gameMod.name != "MainMenu")
    // {
    //       if (dir == 1)
    //     {
    //         if (graphicIndex + 1 < graphLibs.size())
    //             graphicIndex++;
    //         else
    //             graphicIndex = 0;
    //     }
    //     else if (dir == -1)
    //     {
    //         if ((long)graphicIndex - 1 >= 0)
    //             graphicIndex--;
    //         else
    //             graphicIndex = graphLibs.size() - 1;
    //     }
    // }
    changeGraph(graphLibs[graphicIndex]);
}

void Core::CoreMediator::exit()
{
    _exit = true;
    delete game;
    delete graphics;
}

void Core::CoreMediator::_initResources()
{
    auto files = FileReader::listFiles("./lib");
    std::regex mainMenu(".*[Mm]ain[_-]?[Mm]enu.*");
    LibLoader reader;

    for (auto file : files)
    {
        if (std::regex_match(file, mainMenu))
        {
            if (MainMenuLib != "")
                throw std::runtime_error("Multiple main menu libraries");
            MainMenuLib = "./lib/" + file;
            continue;
        }
        reader.reset("./lib/" + file);
        auto type = reader.call<Core::ModInfo>("GetHeader");
        if (type.type == Core::ModInfo::GRAPHIC)
            graphLibs.push_back(file);
        else if (type.type == Core::ModInfo::GAME)
            gameLibs.push_back(file);
        else
            throw std::runtime_error("Unknown library type");
    }
}
