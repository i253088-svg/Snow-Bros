#include "ui.hpp"

Button::Button(sf::Texture idle, sf::Texture hover, sf::Vector2f pos)
{
    button_idle = idle;
    button_hover = hover;
    curr_button.setTexture(button_idle);
    button_pos = pos;
    button_rect.setSize((sf::Vector2f)button_idle.getSize());
    button_rect.setPosition(button_pos);
    curr_button.setPosition(button_pos);
}

void Button::hover_effect(sf::RenderWindow& window, sf::Vector2f scale)
{
    sf::Vector2i raw_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos = window.mapPixelToCoords(raw_pos);

    if (button_rect.getGlobalBounds().contains(mouse_pos))
    {
        button_rect.setScale(curr_button.getScale());
        curr_button.setScale(scale);
        curr_button.setTexture(button_hover, true);
    }
    
    else
    {
        button_rect.setScale(curr_button.getScale());
        curr_button.setScale(scale);
        curr_button.setTexture(button_idle, true);
    }
}

bool Button::check_click(const sf::RenderWindow& window)
{
    sf::Vector2i raw_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos = window.mapPixelToCoords(raw_pos);    

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (button_rect.getGlobalBounds().contains(mouse_pos))
        {
            return true;
        }
    }
    return false;
}

bool Button::check_hover(const sf::RenderWindow& window)
{
    sf::Vector2i raw_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos = window.mapPixelToCoords(raw_pos);    

    if (button_rect.getGlobalBounds().contains(mouse_pos))
        return true;

    return false;
}

sf::Sprite Button::get_button()
{
    return curr_button;
}


// hover and click checks without assosiating to a specific object
bool check_hover(const sf::RenderWindow& window, const sf::RectangleShape& rect)
{
    sf::Vector2i raw_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos = window.mapPixelToCoords(raw_pos);    

    if (rect.getGlobalBounds().contains(mouse_pos))
        return true;

    return false;
}

bool check_click(const sf::RenderWindow& window, const sf::RectangleShape& rect, sf::Event& event)
{
    sf::Vector2i raw_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos = window.mapPixelToCoords(raw_pos);    

    if (rect.getGlobalBounds().contains(mouse_pos))
    {
        if (event.type == sf::Event::MouseButtonPressed and (event.mouseButton.button == sf::Mouse::Left))
        {
            return true;
        }
    }
    return false;
}