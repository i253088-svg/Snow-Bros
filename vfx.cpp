#include "../header/vfx.hpp"

SnowBallEffect::SnowBallEffect(sf::Texture& tex, sf::Vector2u& screen_size, unsigned int alpha) : curr_screen_size(screen_size), vel_x(.25f), vel_y(.85f), snow_tex(tex)
{
    position = new sf::Vector2f[MAX_SNOWBALLS];
    snow_sprite = new sf::Sprite[MAX_SNOWBALLS];

    for (int i = 0; i < MAX_SNOWBALLS; ++i)
    {
        snow_sprite[i].setTexture(snow_tex);
        snow_sprite[i].setScale(0.043f, 0.043f);
        snow_sprite[i].setColor(sf::Color(255, 255, 255, alpha));
        position[i].x = (rand() % curr_screen_size.x) + (snow_sprite[i].getScale().x * SNOW_SIZE);
        position[i].y = (rand() % (curr_screen_size.y*2)) - (snow_sprite[i].getScale().y);
        snow_sprite[i].setPosition(position[i]);
    }
}

void SnowBallEffect::draw_snow(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_SNOWBALLS; ++i)
    {
        window.draw(snow_sprite[i]);
    }
}

void SnowBallEffect::move_snow(float& time)
{
    for (int i = 0; i < MAX_SNOWBALLS; ++i)
    {
        float horizontal_move = sinf(time * 1.2f + i) * (vel_x * 0.8f);
        snow_sprite[i].move(horizontal_move, vel_y);

        if (snow_sprite[i].getPosition().y > curr_screen_size.y)
        {
            position[i].x = (rand() % curr_screen_size.x) + (snow_sprite[i].getScale().x * SNOW_SIZE);
            position[i].y = (snow_sprite[i].getScale().y) - (rand() % (curr_screen_size.y*2));
            snow_sprite[i].setPosition(position[i]);
        }
    }
}

SnowBallEffect::~SnowBallEffect()
{
    delete[] position;  
    position = nullptr;
    delete[] snow_sprite;
    snow_sprite = nullptr;
}