#pragma once
#include "pch.hpp"

bool check_hover(const sf::RenderWindow& window, const sf::RectangleShape& rect);
bool check_click(const sf::RenderWindow& window, const sf::RectangleShape& rect, sf::Event& event);

class Button
{
private:
    sf::Texture button_idle, button_hover; 
    sf::Sprite curr_button;
    sf::Vector2f button_pos;   
    sf::RectangleShape button_rect;

public:
    Button(sf::Texture idle, sf::Texture hover, sf::Vector2f pos);
    void hover_effect(sf::RenderWindow& window, sf::Vector2f scale);
    bool check_click(const sf::RenderWindow& window);
    bool check_hover(const sf::RenderWindow& window);
    sf::Sprite get_button();
};