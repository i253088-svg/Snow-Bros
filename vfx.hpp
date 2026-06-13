#pragma once
#include "pre_compiled.hpp"

struct SnowBallEffect
{
    sf::Vector2f* position;
    sf::Vector2u& curr_screen_size;
    sf::Texture snow_tex;
    sf::Sprite* snow_sprite;
    const float vel_x, vel_y;

    SnowBallEffect(sf::Texture& texture, sf::Vector2u& screen_size, unsigned int alpha);
    void draw_snow(sf::RenderWindow& window);
    void move_snow(float& time);
    ~SnowBallEffect();
};
