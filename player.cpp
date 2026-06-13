#include "../header/player.hpp"

// stats methods
void Stats::displayStats(sf::RenderWindow& window, sf::Color& rgb)
{
    for (int i = 0; i < 5; ++i)
    {

        hud[i].update_color(rgb);
        hud_text[i].update_color(rgb);

        window.draw(hud[i].get_text());
        window.draw(hud_text[i].get_text());
    }
}


// player methods
void Player::draw_stats(sf::RenderWindow& window, sf::Color& rgb)
{
    player_stats.displayStats(window, rgb);
}

void Player::draw_player(sf::RenderWindow& window, int& curr_player)
{
    player_anim[curr_player].anims[0].update_animation();
    player_anim[curr_player].anims[0].draw_animation(window);
}

void Player::move_player(int& curr_player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        pos.x -= 5.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        pos.x += 5.f;
    }

    player_anim[curr_player].anims[0].update_position(pos.x, pos.y);
}