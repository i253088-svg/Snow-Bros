#include "pre_compiled.hpp"

class Stats
{
    private:
        int score, lives, gem_count, curr_level, curr_powerup_timer;
        std::string curr_powerup;
        
        int hud_size = 30, hud_text_size = 27;
        sf::Color hud_color = sf::Color::White;
        sf::Font gaming_font;

        // hud elements
        FontLoader hud[6] = { 
                {gaming_font, "Score: ", hud_size, hud_color, {890.f, 60.f}}, {gaming_font, "Lives: ", hud_size, hud_color, {890.f, 180.f}}, 
                {gaming_font, "Gems: ", hud_size, hud_color, {890.f, 300.f}}, {gaming_font, "Level: ", hud_size, hud_color, {890.f, 420.f}}, 
                {gaming_font, "Power-Up: ", hud_size, hud_color, {890.f, 540.f}}, {gaming_font, "Boss Health: ", hud_size, hud_color, {890.f, 660.f}} 
        };

        // actual numbers
        FontLoader hud_text[6] = { 
            {gaming_font, "0 ", hud_text_size, hud_color, {900.f, 100.f}}, {gaming_font, "2", hud_text_size, hud_color, {900.f, 220.f}}, 
            {gaming_font, "0 ", hud_text_size, hud_color, {900.f, 340.f}}, {gaming_font, "1/10 ", hud_text_size, hud_color, {900.f, 460.f}}, 
            {gaming_font, "15s ", hud_text_size, hud_color, {900.f, 580.f}}, {gaming_font, "100 ", hud_text_size, hud_color, {900.f, 680.f}} 
        };

    public:
        Stats(sf::Font& usr_font) : score(0), lives(2), gem_count(0), curr_level(1), curr_powerup(""), curr_powerup_timer(0) , gaming_font(usr_font)
        {}

        void displayStats(sf::RenderWindow& window, sf::Color& rgb);
};

struct AnimSet
{
    AnimationLoader* anims;
    int count;
};

class Player
{
    private:
        Stats player_stats;
        AnimSet* player_anim;
        sf::Vector2f pos;

    public:
        Player(sf::Font& game_font, AnimSet* ptr) : player_stats(game_font), player_anim(ptr)     
        { 
            pos = {player_anim[0].anims[0].rect.getPosition().x, player_anim[0].anims[0].rect.getPosition().y};
        }
        void draw_stats(sf::RenderWindow& window, sf::Color& rgb);
        void draw_player(sf::RenderWindow& window, int& curr_player);
        void move_player(int& curr_player);
        AnimSet* get_player_anim()  {   return player_anim;     }

};