#pragma once

#include "pch.hpp"
#include "asset.hpp"
#define MAX_SNOWBALLS 200
#define SNOW_SIZE 225

class RgbEffect
{
    private:
        unsigned char red, green, blue;
        float speed, time;
    public:
        RgbEffect(float usr_speed);
        sf::Color apply_rgb(float g_intensity, float b_intensity);
        sf::Color full_rgb(float intensity);
};