#pragma once
#include "pch.hpp"
#include "animation.hpp"

class DrawableEntity 
{
    public:
        virtual void setPos(float x, float y) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
        virtual ~DrawableEntity() {}
};

struct LevelMap 
{
    char symbol;
    DrawableEntity* entity;
};

class StaticSprite : public DrawableEntity 
{
    private:
        sf::Sprite& s;
    public:
        StaticSprite(sf::Sprite& sprite);
        void setPos(float x, float y) override;
        void render(sf::RenderWindow& window) override;
};

class BuildLevel 
{
    private:
        char level_arr[18][22];
        int rows, columns;
        float tile_width, tile_height;

    public:
        BuildLevel(const char* level_file);
        void initialize_entities(LevelMap* mappings, int size);
        void draw_level(sf::RenderWindow& window, LevelMap* mappings, int size);
};