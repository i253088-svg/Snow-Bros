#pragma once
#include "pch.hpp"

class AnimationLoader
{

private:
    sf::Texture* tex;
    sf::Sprite* sprite;
    sf::Vector2f curr_pos;
    sf::Color curr_color;
    int curr_frame, total_frames, frame_speed;
    
public:
    sf::RectangleShape rect; 
    AnimationLoader(int total_usr_frames, int usr_frame_speed, sf::Vector2f pos, sf::Color color);
    void fill_paths(const char* file_path);
    void config_animation();
    void draw_animation(sf::RenderWindow& window);
    void update_animation();
    void update_position(float x, float& y);
    void free_memory();
    void update_scale(float scale_x, float scale_y);
};