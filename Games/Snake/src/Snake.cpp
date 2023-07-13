#include "../../../Headers/Games/Snake.hpp"
#include "../../../Headers/Abstracts/AObject.hpp"
#include "../../../Headers/Abstracts/IMediator.hpp"

#include <algorithm>
#include <random>
#include <set>

const Game::Display::Rectangle Game::SnakeGame::segment{Game::Display::Rectangle(
    0xFFFFFF, Game::Display::AObject::coordinates{0, 0}, 1, 1)};
const Game::Display::Circle Game::SnakeGame::food{Game::Display::Circle(
    0xFFFFFF, Game::Display::AObject::coordinates{0, 0}, 0)};

static const int GAME_OVER_X = 110;
static const int GAME_OVER_Y = 18;
static const int SCORE_X = 110;
static const int SCORE_Y = 14;

//! @brief texts for score and game over, set the coordinates from now
const Game::Display::Text Game::SnakeGame::game_over_text{{Game::Display::Text(
    0xFFFFFF, Game::Display::AObject::coordinates{GAME_OVER_X, GAME_OVER_Y}, "Game Over!", Game::Display::AObject::RED)}};
Game::Display::Text Game::SnakeGame::score_text{{Game::Display::Text(
    0xFFFFFF, Game::Display::AObject::coordinates{SCORE_X, SCORE_Y}, "Score: 0", Game::Display::AObject::MAGENTA)}};

const std::pair<int, int> Game::SnakeGame::directions[4]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

static const int LEFT_WALL_COORD = 25;
static const int RIGHT_WALL_COORD = 100;
static const int DOWN_WALL_COORD = 5;
static const int UPPER_WALL_COORD = 31;

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
            fields.emplace(i, j);
        }
    }
    return fields;
}

static std::mt19937 gen = setGenerator();

static std::set<std::pair<int, int>> freeFields = setFreeFields();

static const float START_HEAD_X = 50;
static const float START_HEAD_Y = 20;

bool Game::SnakeGame::init(Core::IMediator *mediator)
{
    mediator_ = mediator;
    mediator->setScore(0);
    return true;
}

bool Game::SnakeGame::toClose()
{
    delete this;
    return true;
}

void Game::SnakeGame::generateFood()
{
    size_t random_idx = gen() % freeFields.size();
    auto it = freeFields.begin();
    std::advance(it, random_idx);
    Game::Display::AObject::coordinates coords{(float)it->first, (float)it->second};
    food_->pos = coords;
}

void Game::SnakeGame::takeCoord(Game::Display::AObject::coordinates &coords)
{
    std::pair<int, int> coord_pair{(int)coords.x, (int)coords.y};
    freeFields.erase(coord_pair);
}

void Game::SnakeGame::freeCoord(Game::Display::AObject::coordinates &coords)
{
    std::pair<int, int> coord_pair{(int)coords.x, (int)coords.y};
    freeFields.insert(coord_pair);
}

Game::SnakeGame::SnakeGame()
{
    createWall(LEFT_WALL_COORD, UPPER_WALL_COORD, LEFT_WALL_COORD, DOWN_WALL_COORD);
    createWall(LEFT_WALL_COORD, UPPER_WALL_COORD, RIGHT_WALL_COORD, UPPER_WALL_COORD);
    createWall(RIGHT_WALL_COORD, DOWN_WALL_COORD, LEFT_WALL_COORD, DOWN_WALL_COORD);
    createWall(RIGHT_WALL_COORD, DOWN_WALL_COORD, RIGHT_WALL_COORD, UPPER_WALL_COORD);

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

void Game::SnakeGame::MoveSnake(bool add_segment)
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
void Game::SnakeGame::checkCollisions()
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
    }
}

//! @brief update the game objects
void Game::SnakeGame::OverTheGame()
{
    state = GameState::GAMEOVER;
    objects_.emplace_back(std::make_unique<Game::Display::Text>(game_over_text));
}

bool Game::SnakeGame::UpdateFrame()
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
            mediator_->setScore(score);
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

std::vector<std::unique_ptr<Game::Display::AObject>> &Game::SnakeGame::getObject()
{
    return objects_;
}

void Game::SnakeGame::handleEvent(Events::AEvents &event)
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

void Game::SnakeGame::createWall(int x1, int y1, int x2, int y2)
{
    objects_.emplace_back(std::make_unique<Game::Display::Line>(0xFFFFFF, Game::Display::AObject::coordinates{(float)x1, (float)y1}, x2, y2, Game::Display::AObject::RED));
}

extern "C"
{
    Core::IMod *GetModule(Core::IMediator *mediator)
    {
        Game::IGame *obj = new Game::SnakeGame();
        obj->init(mediator);
        return obj;
    }
    Core::ModInfo GetHeader()
    {
        Core::ModInfo info;
        info.type = Core::ModInfo::Type::GAME;
        info.name = "Snake";
        return info;
    }
}
