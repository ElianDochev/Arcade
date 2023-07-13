#include "../../Headers/Games/Nibbler.hpp"
#include "../../Headers/Abstracts/AObject.hpp"

#include <algorithm>
#include <random>
#include <set>

const Game::Display::Rectangle Game::NibblerGame::segment{Game::Display::Rectangle(
    0xFFFFFF, Game::Display::AObject::coordinates{0, 0}, 1, 1)};
const Game::Display::Circle Game::NibblerGame::food{Game::Display::Circle(
    0xFFFFFF, Game::Display::AObject::coordinates{0, 0}, 0)};

static const int GAME_OVER_X = 110;
static const int GAME_OVER_Y = 18;
static const int SCORE_X = 110;
static const int SCORE_Y = 14;

//! @brief texts for score and game over, set the coordinates from now
const Game::Display::Text Game::NibblerGame::game_over_text{{Game::Display::Text(
    0xFFFFFF, Game::Display::AObject::coordinates{GAME_OVER_X, GAME_OVER_Y}, "Game Over!", Game::Display::AObject::RED)}};
Game::Display::Text Game::NibblerGame::score_text{{Game::Display::Text(
    0xFFFFFF, Game::Display::AObject::coordinates{SCORE_X, SCORE_Y}, "Score: 0", Game::Display::AObject::MAGENTA)}};

const std::pair<int, int> Game::NibblerGame::directions[4]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

static const int LEFT_WALL_COORD = 25;
static const int RIGHT_WALL_COORD = 100;
static const int DOWN_WALL_COORD = 5;
static const int UPPER_WALL_COORD = 31;

static const Game::NibblerGame::Obstacle obs1 = {28,27,38,17};
static const Game::NibblerGame::Obstacle obs2 = {97,27,87,17};
static const Game::NibblerGame::Obstacle obs3 = {28,9,38,19};
static const Game::NibblerGame::Obstacle obs4 = {97,9,87,19};
static const Game::NibblerGame::Obstacle obs5 = {63,13,63,23};
static const Game::NibblerGame::Line l1 = {38,27,38,13};
static const Game::NibblerGame::Line l2 = {63,27,73,27};
static const Game::NibblerGame::Line l3 = {87,27,87,13};
static const Game::NibblerGame::Line l4 = {28,13,38,13};
static const Game::NibblerGame::Line l5 = {87,13,97,13};


std::mt19937 setGenerator()
{
    std::mt19937 gen;
    gen.seed(clock());
    return gen;
}

std::set<std::pair<int, int>> setFreeFields()
{
    std::set<std::pair<int, int>> fields;
    for (int i = LEFT_WALL_COORD + 1; i < RIGHT_WALL_COORD; ++i)
    {
        for (int j = DOWN_WALL_COORD + 1; j < UPPER_WALL_COORD; ++j)
        {
            if((i < obs1.x1 || i > obs1.x2 || j < obs1.y2 || j > obs1.y1) && (i < obs2.x1 || i > obs2.x2 || j < obs2.y2 || j > obs2.y1) && (i < obs3.x1 || i > obs3.x2 || j < obs3.y2 || j > obs3.y1) && (i < obs4.x1 || i > obs4.x2 || j < obs4.y2 || j > obs4.y1) && (i < obs5.x1 || i > obs5.x2 || j < obs5.y2 || j > obs5.y1) && (i < l1.x1 || i > l1.x2 || j < l1.y2 || j > l1.y1) && (i < l2.x1 || i > l2.x2 || j < l2.y2 || j > l2.y1) && (i < l3.x1 || i > l3.x2 || j < l3.y2 || j > l3.y1) && (i < l4.x1 || i > l4.x2 || j < l4.y2 || j > l4.y1) && (i < l5.x1 || i > l5.x2 || j < l5.y2 || j > l5.y1)) {
                fields.emplace(i, j);
            }
        }
    }
    return fields;
}

static std::mt19937 gen = setGenerator();

static std::set<std::pair<int, int>> freeFields = setFreeFields();

static const float START_HEAD_X = 50;
static const float START_HEAD_Y = 20;

bool Game::NibblerGame::init(Core::IMediator *mediator)
{
    mediator_ = mediator;
    return true;
}

bool Game::NibblerGame::toClose()
{
    delete this;
    return true;
}

void Game::NibblerGame::generateFood()
{
    size_t random_idx = gen() % freeFields.size();
    auto it = freeFields.begin();
    std::advance(it, random_idx);
    Game::Display::AObject::coordinates coords{(float)it->first, (float)it->second};
    food_->pos = coords;
}

void Game::NibblerGame::takeCoord(Game::Display::AObject::coordinates &coords)
{
    std::pair<int, int> coord_pair{(int)coords.x, (int)coords.y};
    freeFields.erase(coord_pair);
}

void Game::NibblerGame::freeCoord(Game::Display::AObject::coordinates &coords)
{
    std::pair<int, int> coord_pair{(int)coords.x, (int)coords.y};
    freeFields.insert(coord_pair);
}

Game::NibblerGame::NibblerGame()
{
    //left wall
    createWall(LEFT_WALL_COORD, UPPER_WALL_COORD, LEFT_WALL_COORD, DOWN_WALL_COORD);
    //upper wall
    createWall(LEFT_WALL_COORD, UPPER_WALL_COORD, RIGHT_WALL_COORD, UPPER_WALL_COORD);
    //lower wall
    createWall(RIGHT_WALL_COORD, DOWN_WALL_COORD, LEFT_WALL_COORD, DOWN_WALL_COORD);
    //right wall
    createWall(RIGHT_WALL_COORD, DOWN_WALL_COORD, RIGHT_WALL_COORD, UPPER_WALL_COORD);
    //obstacle 1
    createObstacle(obs1.x1, obs1.y1, obs1.x2, obs1.y2);
    //obstacle 2
    createObstacle(obs2.x1, obs2.y1, obs2.x2, obs2.y2);
    //obstacle 3
    createObstacle(obs3.x1, obs3.y1, obs3.x2, obs3.y2);
    //obstacle 4
    createObstacle(obs4.x1, obs4.y1, obs4.x2, obs4.y2);
    //obstacle 5
    createObstacle(obs5.x1, obs5.y1, obs5.x2, obs5.y2);
    //line 1
    createWall(l1.x1, l1.y1, l1.x2, l1.y2);
    //line 2
    createWall(l2.x1, l2.y1, l2.x2, l2.y2);
    //line 3
    createWall(l3.x1, l3.y1, l3.x2, l3.y2);
    //line 4
    createWall(l4.x1, l4.y1, l4.x2, l4.y2);
    //line 5
    createWall(l5.x1, l5.y1, l5.x2, l5.y2);


    createAt<Game::Display::Circle>(0, 0, food);
    food_ = objects_.back().get();

    createAt<Game::Display::Text>(SCORE_X, SCORE_Y, score_text);
    score_text_ref = dynamic_cast<Game::Display::Text *>(objects_.back().get());

    for (size_t i = 0; i < 4; ++i)
    {
        createAt<Game::Display::Rectangle>(START_HEAD_X, START_HEAD_Y - i, segment);
        snake_.push_back(objects_.back().get());
        takeCoord(snake_.back()->pos);
    }

    createAt<Game::Display::Circle>(0, 0, food);
    generateFood();
}

void Game::NibblerGame::MoveSnake(bool add_segment)
{
    auto *head = snake_.front();
    Game::Display::AObject::coordinates new_coordinates;
    new_coordinates.x = head->pos.x + directions[current_direction].first;
    new_coordinates.y = head->pos.y + directions[current_direction].second;
    takeCoord(snake_.back()->pos);
    for (size_t i = 0; i < snake_.size(); ++i)
    {
        if (!(i == snake_.size() - 1 && add_segment))
        {
            std::swap(new_coordinates, snake_[i]->pos);
        }
    }
}

//! @brief check if we collide with anything
void Game::NibblerGame::checkCollisions()
{
    auto *head = snake_.front();
    //! @brief skip the head
    for (size_t i = 1; i < snake_.size(); ++i)
    {
        if (head->pos.x == snake_[i]->pos.x && head->pos.y == snake_[i]->pos.y)
        {
            OverTheGame();
            return;
        }
    }
    if (head->pos.x == LEFT_WALL_COORD || head->pos.x == RIGHT_WALL_COORD ||
        head->pos.y == UPPER_WALL_COORD || head->pos.y == DOWN_WALL_COORD)
    {
        OverTheGame();
        return;
    }

    for (const auto& obstacle : {obs1, obs2, obs3, obs4, obs5})
    {
        if (head->pos.x >= obstacle.x1 && head->pos.x <= obstacle.x2 &&
            head->pos.y >= obstacle.y1 && head->pos.y <= obstacle.y2)
        {
            OverTheGame();
            return;
        }
    }

    for (const auto& line : {l1, l2, l3, l4, l5})
    {
        if ((head->pos.x == line.x1 && head->pos.y >= std::min(line.y1, line.y2) &&
             head->pos.y <= std::max(line.y1, line.y2)) ||
            (head->pos.y == line.y1 && head->pos.x >= std::min(line.x1, line.x2) &&
             head->pos.x <= std::max(line.x1, line.x2)))
        {
            OverTheGame();
            return;
        }
    }
}

//! @brief update the game objects
void Game::NibblerGame::OverTheGame()
{
    state = GameState::GAMEOVER;
    objects_.emplace_back(std::make_unique<Game::Display::Text>(game_over_text));
}

bool Game::NibblerGame::UpdateFrame()
{
    if (state == GameState::PLAYING)
    {
        auto *head = snake_.front();
        if (head->pos.x == food_->pos.x && head->pos.y == food_->pos.y)
        {
            objects_.emplace_back(std::make_unique<Game::Display::Rectangle>(
                *dynamic_cast<Game::Display::Rectangle *>(snake_.back())));
            snake_.push_back(objects_.back().get());
            MoveSnake(true);
            generateFood();
            score += 100;
            score_text_ref->text = "Score: " + std::to_string(score);
        }
        else
        {
            MoveSnake(false);
            freeCoord(snake_.back()->pos);
        }
        checkCollisions();
    }
    if (state == GameState::GAMEOVER)
    {
        if (--gameover_timer == 0)
        {
            return false;
        }
    }
    return true;
}

std::vector<std::unique_ptr<Game::Display::AObject>> &Game::NibblerGame::getObject()
{
    return objects_;
}

void Game::NibblerGame::handleEvent(Events::AEvents &event)
{
    if (event.type == Game::Events::KeyboardEvent::KeyPressed)
    {
        if (event.key == Game::Events::KeyboardEvent::LEFT_ARROW || event.key == Game::Events::KeyboardEvent::KEY_A)
        {
            current_direction = (current_direction + 1) % 4; // seems not right, but it is inverted. i have no fucking idea
        }
        else if (event.key == Game::Events::KeyboardEvent::RIGHT_ARROW || event.key == Game::Events::KeyboardEvent::KEY_D)
        {
            current_direction = (current_direction - 1) % 4;
        }
    }
}

void Game::NibblerGame::createWall(int x1, int y1, int x2, int y2)
{
    objects_.emplace_back(std::make_unique<Game::Display::Line>(0xFFFFFF, Game::Display::AObject::coordinates{(float)x1, (float)y1}, x2, y2, Game::Display::AObject::RED));
}

void Game::NibblerGame::createObstacle(int x1, int y1, int x2, int y2)
{
    createWall(x1, y1, x1, y2);
    createWall(x1, y1, x2, y1);
    createWall(x2, y2, x1, y2);
    createWall(x2, y2, x2, y1);
}

extern "C"
{
    Core::IMod *GetModule(Core::IMediator *mediator)
    {
        Game::IGame *obj = new Game::NibblerGame();
        obj->init(mediator);
        return obj;
    }
    Core::ModInfo GetHeader()
    {
        Core::ModInfo info;
        info.type = Core::ModInfo::Type::GAME;
        info.name = "Nibbler";
        return info;
    }
}