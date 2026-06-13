#include "asset.hpp"

bool checkValid(sf::Texture& tex, const char* file_path) 
{
    if (!tex.loadFromFile(file_path)) 
    {
        std::cerr << "Error: Could not load " << file_path << "\n";
        return false;
    }
    return true;
}

// defining constructors and methods
AssetsLoader::AssetsLoader(sf::Vector2f pos, const char* file_path) 
{
    if (checkValid(tex, file_path)) 
    {
        sprite.setTexture(tex);
    }
    sprite.setPosition(pos);
    rect.setPosition(pos);
    rect.setSize((sf::Vector2f)(tex.getSize()));
}

AssetsLoader::AssetsLoader()
{
}

sf::Sprite& AssetsLoader::get_sprite() 
{
    return sprite;
}

sf::Texture& AssetsLoader::get_texture() 
{
    return tex;
}

// FontLoader
FontLoader::FontLoader(const sf::Font& usr_font, std::string usr_msg, int usr_size, sf::Color usr_color, sf::Vector2f pos) : position(pos)
{
    msg = usr_msg;  size = usr_size;    color = usr_color;    
    text.setFont(usr_font);  
    text.setString(msg);   
    text.setCharacterSize(size);    
    text.setFillColor(color);   
    text.setPosition(position); 
}

FontLoader:: FontLoader(const sf::Font& usr_font, std::string usr_msg, int usr_size, sf::Color usr_color, sf::Vector2f pos, float letter_spacing) : position(pos)
{
    msg = usr_msg;  size = usr_size;    color = usr_color;    
    text.setFont(usr_font);  
    text.setString(msg);   
    text.setCharacterSize(size);    
    text.setFillColor(color);   
    text.setPosition(position); 
    text.setLetterSpacing(letter_spacing);
}

sf::Text FontLoader::get_text()
{
    return text;
}

void FontLoader::update_color(sf::Color& col)
{
    color = col;
    text.setFillColor(color);
}

sf::RectangleShape FontLoader::get_text_rect(int total_char)
{
    sf::RectangleShape curr_rect;
    curr_rect.setPosition(position.x, position.y);
    curr_rect.setSize(sf::Vector2f( ( (size / 2) * (total_char + 1) + size), size));
    return curr_rect;
}

void FontLoader::update_text(std::string new_msg)
{
    msg = new_msg;
}
