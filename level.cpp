#include "levelmanager.hpp"
#include "animation.hpp"

StaticSprite::StaticSprite(sf::Sprite& sprite) : s(sprite) {}
void StaticSprite::setPos(float x, float y) 
{ 
    s.setPosition(x, y); 
}
void StaticSprite::render(sf::RenderWindow& window) 
{ 
    window.draw(s); 
}

BuildLevel::BuildLevel(const char* level_file) : rows(18), columns(22), tile_width(40.f), tile_height(40.f)
{
    std::ifstream level_data(level_file);
    if (level_data.is_open()) 
    {
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                char tile;
                level_data.get(tile);
                if (tile == '\n') 
                {
                    level_data.get(tile);
                }
                level_arr[i][j] = tile;
            }
        }
        level_data.close();
    } 
    
    else 
    {
        std::cerr << "Unable to open file: " << level_file << std::endl;
    }
}

void BuildLevel::initialize_entities(LevelMap* mappings, int size) 
{
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            char currentTile = level_arr[i][j];
            
            for (int k = 0; k < size; ++k) 
            {
                if (currentTile == mappings[k].symbol)
                {
                    mappings[k].entity->setPos(j * tile_width, i * tile_height);
                }
            }
        }
    }
}

void BuildLevel::draw_level(sf::RenderWindow& window, LevelMap* mappings, int size) 
{
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            char currentTile = level_arr[i][j];

            if (currentTile == ' ') 
                continue;
            
            for (int k = 0; k < size; ++k) 
            {
                if (currentTile == mappings[k].symbol)
                {
                    mappings[k].entity->setPos(j * tile_width, i * tile_height);
                    mappings[k].entity->render(window);
                    break; 
                }
            }
        }
    }
}