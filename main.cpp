#include "header/pre_compiled.hpp"
#include "header/vfx.hpp"
#include "header/states.hpp"
#include "header/menu.hpp"

int main()
{
    sf::Vector2u screen_size = {1080, 720};
    sf::RenderWindow window(sf::VideoMode(screen_size.x, screen_size.y), "Snow Bros", sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font game_font; game_font.loadFromFile("../font/font.ttf");

    Database db;
    db.load_from_file("../data/users.txt");

    int auth_state = 0;

    sf::RectangleShape btn_signup(sf::Vector2f(300.f, 55.f));
    btn_signup.setPosition(390.f, 250.f);
    btn_signup.setFillColor(sf::Color(255, 255, 255, 60));
    btn_signup.setOutlineColor(sf::Color::White);   
    btn_signup.setOutlineThickness(2.f);
 
    sf::RectangleShape btn_signin(sf::Vector2f(300.f, 55.f));
    btn_signin.setPosition(390.f, 340.f);
    btn_signin.setFillColor(sf::Color(255, 255, 255, 60));
    btn_signin.setOutlineColor(sf::Color::White);
    btn_signin.setOutlineThickness(2.f);

    sf::RectangleShape btn_guest(sf::Vector2f(300.f, 55.f));
    btn_guest.setPosition(390.f, 430.f);
    btn_guest.setFillColor(sf::Color(255, 255, 255, 60));
    btn_guest.setOutlineColor(sf::Color::White);
    btn_guest.setOutlineThickness(2.f);

    AssetsLoader auth_bg({0.f, 0.f}, "../gfx/bg/bg.png");
    auth_bg.get_sprite().setColor(sf::Color(255, 255, 255, 185));

    sf::Texture signin_snow_tex;   signin_snow_tex.loadFromFile("../gfx/elements/snow.png");
    SnowBallEffect signin_effect(signin_snow_tex, screen_size, 255);

    // clock timer
    sf::Clock clock;

    while (window.isOpen() && auth_state != 3)
    {
        if (auth_state == 1)
        {
            display_signup(window, db);
            auth_state = 0;  
        }

        else if (auth_state == 2)
        {
            bool signed_in = display_signin(window, db);
            if (signed_in) 
            {
                auth_state = 3;
            }   
            else 
            {
                auth_state = 0;
            }
        }

        else 
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (btn_signup.getGlobalBounds().contains(mouse)) 
                        auth_state = 1;
                    else if (btn_signin.getGlobalBounds().contains(mouse)) 
                        auth_state = 2;
                    else if (btn_guest .getGlobalBounds().contains(mouse)) 
                        auth_state = 3;
                }
            }

            float time = clock.getElapsedTime().asSeconds();

            window.clear(sf::Color::Black);
            window.draw(auth_bg.get_sprite());
            signin_effect.move_snow(time);
            signin_effect.draw_snow(window);

            FontLoader title(game_font, "SNOW BROS", 70, sf::Color::White, {330.f, 100.f});
            window.draw(title.get_text());

            window.draw(btn_signup);
            window.draw(btn_signin);
            window.draw(btn_guest);

            FontLoader lbl_signup(game_font, "SIGN UP", 30, sf::Color::White, {480.f, 255.f});
            FontLoader lbl_signin(game_font, "SIGN IN", 30, sf::Color::White, {480.f, 345.f});
            FontLoader lbl_guest (game_font, "PLAY AS GUEST", 26, sf::Color::White, {425.f, 440.f});

            window.draw(lbl_signup.get_text());
            window.draw(lbl_signin.get_text());
            window.draw(lbl_guest.get_text());

            window.display();
        }
    }

    FontLoader new_game(game_font, "New Game", 45, sf::Color::White, {395.f, 250.f - 35.f});
    FontLoader continue_game(game_font, "Continue", 45, sf::Color::White, {395.f, 325.f - 35.f});
    FontLoader leaderboard(game_font, "LeaderBoard", 45, sf::Color::White, {395.f, 400.f - 35.f});
    FontLoader settings(game_font, "Settings", 45, sf::Color::White, {395.f, 475.f - 35.f});
    FontLoader exit(game_font, "Exit", 45, sf::Color::White, {398.f, 550.f - 35.f});

    sf::RectangleShape new_game_rect = new_game.get_text_rect(8);
    sf::RectangleShape continue_rect = continue_game.get_text_rect(8);
    sf::RectangleShape leaderboard_rect = leaderboard.get_text_rect(11);
    sf::RectangleShape settings_rect = settings.get_text_rect(8);
    sf::RectangleShape exit_rect = exit.get_text_rect(4);

    // menu background
    RgbEffect new_rgb(0.045f);
    FontLoader menu_font(game_font, "Snow Bros", 65, sf::Color::White, {325.f, 60.f});

    AssetsLoader menu_bg({0.f, 0.f}, "../gfx/bg/bg.png");
    sf::Texture snow_tex;   snow_tex.loadFromFile("../gfx/elements/snow.png");
    SnowBallEffect snow_effect(snow_tex, screen_size, 255);

    // game variables
    sf::Color White = sf::Color::White;
    static int curr_player_selection = 0;
    static int curr_level_selection = 1;

    menu_bg.get_sprite().setColor(sf::Color(255, 255, 255, 175));

    while (window.isOpen())
    {
        sf::Color final_color = new_rgb.apply_rgb(255.f, 255.f);
        float time = clock.getElapsedTime().asSeconds();

        sf::Vector2i raw_mouse_pos = sf::Mouse::getPosition();
        sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(raw_mouse_pos);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

            if (check_click(window, new_game_rect, event))
            {
                player_selection(window, game_font, screen_size, curr_player_selection, curr_level_selection);
            }
    
            if (check_click(window, continue_rect, event))
            {
                // continue game
            }
    
            if (check_click(window, leaderboard_rect, event))
            {
                display_leaderbord(window, screen_size);
            }
    
            if (check_click(window, settings_rect, event))
            {
                display_settings(window, screen_size);
            }
    
            if (check_click(window, exit_rect, event))
            {
                window.close();
            }
        }

        new_game.update_color(check_hover(window, new_game_rect) ? final_color : White);
        continue_game.update_color(check_hover(window, continue_rect) ? final_color : White);
        leaderboard.update_color(check_hover(window, leaderboard_rect) ? final_color : White);
        settings.update_color(check_hover(window, settings_rect) ? final_color : White);
        exit.update_color(check_hover(window, exit_rect) ? final_color : White);

        window.clear(sf::Color(sf::Color::Black));

        window.draw(menu_bg.get_sprite());
        
        snow_effect.move_snow(time);
        snow_effect.draw_snow(window);

        window.draw(menu_font.get_text());

        window.draw(new_game.get_text());
        window.draw(continue_game.get_text());
        window.draw(leaderboard.get_text());
        window.draw(settings.get_text());
        window.draw(exit.get_text());

        window.display();
    }

    return 0;
}



// #include <iostream>

// int main()
// {
//     return 0;
// }
