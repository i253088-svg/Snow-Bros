#include "animation.hpp"

AnimationLoader::AnimationLoader(int total_usr_frames, int usr_frame_speed, sf::Vector2f pos, sf::Color color)
{
    tex = new sf::Texture[100];
    sprite = new sf::Sprite[100];
    curr_frame = 0;   total_frames = total_usr_frames;   frame_speed = usr_frame_speed;
    curr_pos = pos;
    curr_color = color;
    rect.setPosition(curr_pos); rect.setSize((sf::Vector2f)tex->getSize());
};

void AnimationLoader::fill_paths(const char* file_path)
{
    for (int i = 0; i < total_frames; ++i)
    {
        std::string path = file_path + std::to_string(i+1) + ".png";
        tex[i].loadFromFile(path.c_str());
        sprite[i].setTexture(tex[i]);
        rect.setSize((sf::Vector2f)tex[i].getSize());
    }
}

void AnimationLoader::config_animation()
{
    for (int i = 0; i < total_frames; ++i)
    {
        sprite[i].setPosition(curr_pos);
        sprite[i].setColor(curr_color);
        rect.setScale(0.80f, 0.80f);    
    }
}

void AnimationLoader::update_animation()
{
    curr_frame++;
    if (curr_frame >= (total_frames * frame_speed))
    {
        curr_frame = 0;
    }   
}

void AnimationLoader::draw_animation(sf::RenderWindow& window)
{
    window.draw(sprite[curr_frame / frame_speed]);
}

void AnimationLoader::update_position(float x, float& y)
{
    for (int i = 0; i < total_frames; ++i)
    {
        sprite[i].setPosition(x, y);
    }
}

void AnimationLoader::update_scale(float scale_x, float scale_y)
{
    for (int i = 0; i < total_frames; ++i)
    {
        sprite[i].setScale(scale_x, scale_y);
        rect.setScale(scale_x * 0.8f, scale_y * 0.8f);
    }
}

void AnimationLoader::free_memory()
{ 
    delete[] tex;   tex = nullptr;
    delete[] sprite;    sprite = nullptr;
}