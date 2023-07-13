#include "../../../Headers/NCurses/NCurses.hpp"
#include "../../../Headers/Utils/RGBReader.hpp"
#include <cmath>

namespace GameDisplay = g::Display;
using nc = Graphical::NCurses;
using gObj = GameDisplay::AObject;

void nc::draw(std::vector<std::unique_ptr<g::Display::AObject>> &objs)
{
    for (auto &obj : objs)
    {
        int type = obj->getType();
        switch (type)
        {
        case gObj::CIRCLE:
            draw(*dynamic_cast<Game::Display::Circle *>(obj.get()));
            break;
        case gObj::RECTANGLE:
            draw(*dynamic_cast<Game::Display::Rectangle *>(obj.get()));
            break;
        case gObj::TEXT:
            draw(*dynamic_cast<Game::Display::Text *>(obj.get()));
            break;
        case gObj::LINE:
            draw(*dynamic_cast<Game::Display::Line *>(obj.get()));
            break;
        case gObj::SPRITE:
            draw(*dynamic_cast<Game::Display::Sprite *>(obj.get()));
            break;
        default:
            throw gObj::AObjectUnknownException();
        }
    }
}

bool nc::draw(GameDisplay::Circle &obj)
{
    auto draw_circle = [](int x, int y, int radius, int ch)
    {
        for (int dy = -radius; dy <= radius; dy++)
        {
            for (int dx = -radius; dx <= radius; dx++)
            {
                if (dx * dx + dy * dy <= radius * radius)
                {
                    mvaddch(y + dy, x + dx, ch);
                }
            }
        }
    };
    auto pos = pos_from_percent(obj.pos);
    attron(COLOR_PAIR(_getColor(obj.backupColor)));
    draw_circle(std::round(pos.x), std::round(pos.y), obj.radius, '@');
    attroff(COLOR_PAIR(1));
    return true;
}

bool nc::draw(GameDisplay::Rectangle &obj)
{
    auto draw_rectangle = [](int x, int y, int width, int height, int ch)
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                mvaddch(y + j, x + i, ch);
            }
        }
    };
    auto pos = pos_from_percent(obj.pos);
    auto offset = pos_from_percent((GameDisplay::AObject::coordinates){(float)obj.width, (float)obj.height});
    attron(COLOR_PAIR(_getColor(obj.backupColor)));
    draw_rectangle(std::round(pos.x), std::round(pos.y), std::round(offset.x), std::round(offset.y), '*');
    attroff(COLOR_PAIR(_getColor(obj.backupColor)));
    return true;
}

bool nc::draw(GameDisplay::Text &obj)
{
    auto draw_text = [&](int x, int y, const std::string &text)
    {
        int i = 0;
        for (auto &c : text)
        {
            mvaddch(y, x + i, c);
            i++;
        }
        return i;
    };
    attron(COLOR_PAIR(_getColor(obj.backupColor)));
    auto pos = pos_from_percent(obj.pos);
    int size = draw_text(std::round(pos.x), std::round(pos.y), obj.text);
    obj.hitbox.x = _mediator->GetPositionMode() == true ? (size / max_x) * 100 : size;
    obj.hitbox.y = 2.f;
    attroff(COLOR_PAIR(_getColor(obj.backupColor)));
    return true;
}

bool nc::draw(GameDisplay::Line &obj)
{
    auto draw_line = [](int x1, int y1, int x2, int y2, int ch)
    {
        bool reverse = false;
        int dx = std::abs(x1 - x2);
        int dy = std::abs(y1 - y2);
        if (dx < dy)
        {
            reverse = true;
            std::swap(x1, y1);
            std::swap(x2, y2);
        }
        if (x2 < x1)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        int A = y2 - y1;
        int B = x1 - x2;
        int C = y1 * x2 - y2 * x1;
        int y = y1;
        for (int x = x1; x <= x2; ++x)
        {
            int f = A * x + B * y + C;
            int f_g = A * x + B * (y + 1) + C;
            while (std::abs(f_g) < std::abs(f))
            {
                y++;
                f = A * x + B * y + C;
                f_g = A * x + B * (y + 1) + C;
            }
            int f_l = A * x + B * (y - 1) + C;
            while (std::abs(f_l) < std::abs(f))
            {
                y--;
                f = A * x + B * y + C;
                f_l = A * x + B * (y - 1) + C;
            }
            if (!reverse)
            {
                mvaddch(y, x, ch);
            }
            else
            {
                mvaddch(x, y, ch);
            }
        }
    };
    auto pos = pos_from_percent(obj.pos);
    auto offset = pos_from_percent((GameDisplay::AObject::coordinates){(float)obj.x2, (float)obj.y2});
    attron(COLOR_PAIR(_getColor(obj.backupColor)));
    draw_line(std::round(pos.x), std::round(pos.y), std::round(offset.x), std::round(offset.y), '-');
    attroff(COLOR_PAIR(_getColor(obj.backupColor)));
    return true;
}

bool nc::draw(GameDisplay::Sprite &obj)
{
    auto draw_sprite = [](int x, int y, int width, int height, int ch)
    {
        for (int i = 0; i < width; i++)
        {
            mvaddch(y, x + i, ch);
            mvaddch(y + height, x + i, ch);
        }
        for (int i = 0; i < height; i++)
        {
            mvaddch(y + i, x, ch);
            mvaddch(y + i, x + width, ch);
        }
    };
    attron(COLOR_PAIR(_getColor(obj.backupColor)));
    auto pos = pos_from_percent(obj.pos);
    auto offset = pos_from_percent((GameDisplay::AObject::coordinates){(float)obj.sizeX, (float)obj.sizeY});
    draw_sprite(std::round(pos.x), std::round(pos.y), std::round(offset.x), std::round(offset.y), obj.backupChar);
    attroff(COLOR_PAIR(_getColor(obj.backupColor)));
    return true;
}

int nc::_getColor(unsigned color)
{
    if (color == gObj::WHITE)
        return 1;
    if (color == gObj::BLACK)
        return 5;
    if (color == gObj::RED)
        return 2;
    if (color == gObj::GREEN)
        return 3;
    if (color == gObj::BLUE)
        return 4;
    if (color == gObj::YELLOW)
        return 8;
    if (color == gObj::MAGENTA)
        return 6;
    if (color == gObj::CYAN)
        return 7;
    return 1;
}

GameDisplay::AObject::coordinates nc::pos_from_percent(GameDisplay::AObject::coordinates pos)
{
    GameDisplay::AObject::coordinates size;

    if (_mediator->GetPositionMode() == false)
        return pos;
    size.x = (pos.x * max_x) / 100;
    size.y = (pos.y * max_y) / 100;
    return size;
}

void Graphical::NCurses::_pos_to_percent(g::Display::AObject::coordinates &pos)
{
    if (_mediator->GetPositionMode() == false)
        return;
    pos.x = (pos.x / max_x) * 100;
    pos.y = (pos.y / max_y) * 100;
}