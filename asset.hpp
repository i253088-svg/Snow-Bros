#pragma once
#include "pch.hpp"

bool checkValid(sf::Texture& tex, const char* file_path);

class AssetsLoader 
{
private:
    sf::Texture tex;
    sf::Sprite sprite;
    
public:
    sf::RectangleShape rect;
    AssetsLoader(sf::Vector2f pos, const char* file_path);
    AssetsLoader();
    sf::Sprite& get_sprite();
    sf::Texture& get_texture();
};

class FontLoader
{

private:
    sf::Text text;
    sf::Vector2f position;
    std::string msg;
    int size;
    sf::Color color;

public:
    FontLoader(const sf::Font& usr_font, std::string usr_msg, int usr_size, sf::Color usr_color, sf::Vector2f pos);
    FontLoader(const sf::Font& usr_font, std::string usr_msg, int usr_size, sf::Color usr_color, sf::Vector2f pos, float letter_spacing);
    sf::Text get_text();
    void update_color(sf::Color& col);
    void update_text(std::string msg);
    sf::RectangleShape get_text_rect(int total_char);
};