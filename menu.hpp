#pragma once 
#include "pre_compiled.hpp"
#include "hashing.hpp"

//void display_signin(sf::RenderWindow& window, bool*& signin, sf::Vector2u& screen_size);
void display_leaderbord(sf::RenderWindow& window, sf::Vector2u& screen_size);
void display_settings(sf::RenderWindow& window, sf::Vector2u& screen_size);
bool display_signin(sf::RenderWindow& window, Database& db);   
void display_signup(sf::RenderWindow& window, Database& db);

void new_animation(sf::RenderWindow& window);