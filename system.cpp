#include "system.hpp"

// creating a source file for useful systems and effects

// rgb effect
RgbEffect::RgbEffect(float usr_speed) : speed(usr_speed), time(0.f), red(0), green(0), blue(0) {}
sf::Color RgbEffect::apply_rgb(float g_intensity, float b_intensity)
{
    time += speed;
    if (time >= (M_PI*2))
        time -= (M_PI*2);

    float wave = (sinf(time) + 1.0f) / 2.0f; 

    green = static_cast<unsigned char>(g_intensity * wave);
    blue  = static_cast<unsigned char>(b_intensity);  

    return sf::Color(0, green, blue, 255);
}

sf::Color RgbEffect::full_rgb(float intensity)
{
    time += speed;
    if (time >= (M_PI*2))
        time -= (M_PI*2);
    
    red = static_cast<unsigned char>(intensity + (intensity * sinf(time)));
    green = static_cast<unsigned char>(intensity + (intensity * sinf(time + 2.f)));
    blue = static_cast<unsigned char>(intensity + (intensity * sinf(time + 4.f)));

    return sf::Color(red, green, blue, 255);
}