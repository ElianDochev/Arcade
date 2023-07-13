#pragma once

#include <cstdint>
#include "../Abstracts/AObject.hpp"

namespace Game::Display
{
    /**
     * @defgroup ColorUtils Color Utilities
     * @brief Utility functions for working with color values
     * @{
     */

    /**
     * @brief the red component of a color in the form 0x00RRGGBB
     */
    uint8_t getRed(uint32_t color) { return (color >> 16) & 0xFF; }

    /**
     * @brief Returns the green component of a color in the form 0x00RRGGBB
     */
    uint8_t getGreen(uint32_t color) { return (color >> 8) & 0xFF; }

    /**
     * @brief Returns the blue component of a color in the form 0x00RRGGBB
     */
    uint8_t getBlue(uint32_t color) { return color & 0xFF; }

    /**
     * @brief Sets the red component of a color in the form 0x00RRGGBB
     */
    void setRed(uint32_t &color, uint8_t red) { color = (color & 0x00FFFF) | (static_cast<uint32_t>(red) << 16); }

    /**
     * @brief Sets the green component of a color in the form 0x00RRGGBB
     */
    void setGreen(uint32_t &color, uint8_t green) { color = (color & 0xFF00FF) | (static_cast<uint32_t>(green) << 8); }

    /**
     * @brief Sets the blue component of a color in the form 0x00RRGGBB
     */
    void setBlue(uint32_t &color, uint8_t blue) { color = (color & 0xFFFF00) | static_cast<uint32_t>(blue); }

    /**
     * @}
     */
    // End of ColorUtils group
    // bool is_space_occupied(AObject::coordinates obj_pos, AObject::coordinates obj_size, AObject::coordinates try_coor)
    // {
    //     // Calculate the AObject::coordinates of the object's bounding box
    //     AObject::coordinates obj_bb_top_left = {obj_pos.x - obj_size.x / 2, obj_pos.y - obj_size.y / 2};
    //     AObject::coordinates obj_bb_bottom_right = {obj_pos.x + obj_size.x / 2, obj_pos.y + obj_size.y / 2};

    //     // Calculate the AObject::coordinates of the space to check
    //     AObject::coordinates space_top_left = {try_coor.x - offset.x / 2, try_coor.y - offset.y / 2};
    //     AObject::coordinates space_bottom_right = {try_coor.x + offset.x / 2, try_coor.y + offset.y / 2};

    //     // Check if the space intersects with the object's bounding box
    //     if (space_bottom_right.x < obj_bb_top_left.x || space_top_left.x > obj_bb_bottom_right.x ||
    //         space_bottom_right.y < obj_bb_top_left.y || space_top_left.y > obj_bb_bottom_right.y)
    //     {
    //         // The space is outside the object's bounding box, so it is not occupied
    //         return false;
    //     }
    //     // The space intersects with the object's bounding box, so it is occupied
    //     return true;
    // }
    bool is_space_occupied(AObject::coordinates obj_pos, AObject::coordinates obj_size, AObject::coordinates try_coor)
    {
        return obj_pos.x <= try_coor.x && try_coor.x <= obj_pos.x + obj_size.x &&
            obj_pos.y <= try_coor.y && try_coor.y <= obj_pos.y + obj_size.y;
    }
}
