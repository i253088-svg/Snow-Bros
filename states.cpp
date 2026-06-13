#include "../header/states.hpp"
#include "../header/vfx.hpp"
#include "../header/player.hpp"

enum PAUSE_STATES {RESUME, SHOP, SAVE, LOGOUT, EXIT};

void main_gameplay(sf::RenderWindow& window, sf::Font& gaming_font, sf::Vector2u& screen_size, int& p_select, int& l_select)
{
    // buttons and text
    FontLoader pause_button(gaming_font, "Pause", 25, sf::Color::White, {890.f, 0.f});
    sf::RectangleShape pause_rect = pause_button.get_text_rect(5);

    AssetsLoader game_bg({0.f, 0.f}, "../gfx/bg/bg.png");
    game_bg.get_sprite().setColor(sf::Color(255, 255, 255, 255));
    AssetsLoader game_ui({880.f, 0.f}, "../gfx/bg/gameplay_ui.png");
   
    // player section
    sf::Color p1_color = sf::Color::White, p2_color = sf::Color::White, p3_color = sf::Color::White, p4_color = sf::Color::White;
    
    std::string folder_paths1[6] = {"idle", "run", "jump", "shoot", "hit", "death"};
    std::string folder_paths2[5] = {"idle", "walk", "attack", "hit", "death"};
    
    //                              IDLE                            RUN                           JUMP                              SHOOT                              HIT                                    DEATH
    AnimationLoader p1[6] = { {4, 8, {0.f, 0.f}, p1_color}, {4, 8, {0.0f, 0.0f}, p1_color}, {8, 16, {0.0f, 0.0f}, p1_color}, {3, 6, {0.0f, 0.0f}, p1_color}, {2, 4, {0.0f, 0.0f}, p1_color}, {6, 12, {0.0f, 0.0f}, p1_color} };
    AnimationLoader p2[6] = { {4, 8, {0.f, 0.f}, p2_color}, {4, 8, {0.0f, 0.0f}, p2_color}, {8, 16, {0.0f, 0.0f}, p2_color}, {3, 6, {0.0f, 0.0f}, p2_color}, {2, 4, {0.0f, 0.0f}, p2_color}, {6, 12, {0.0f, 0.0f}, p2_color} };
    //                              IDLE                            WALK                            ATTACK                              HIT                             DEATH
    AnimationLoader p3[5] = { {8, 16, {0.f, 0.f}, p3_color}, {10, 20, {0.0f, 0.0f}, p3_color}, {11, 22, {0.0f, 0.0f}, p3_color}, {4, 8, {0.0f, 0.0f}, p3_color}, {13, 26, {0.0f, 0.0f}, p3_color} };
    AnimationLoader p4[5] = { {8, 16, {0.f, 0.f}, p4_color}, {10, 20, {0.0f, 0.0f}, p4_color}, {11, 22, {0.0f, 0.0f}, p4_color}, {4, 8, {0.0f, 0.0f}, p4_color}, {13, 26, {0.0f, 0.0f}, p4_color} };
    
    //void (AnimationLoader::*p_paths[])(const char*) = {&AnimationLoader::fill_paths};     syntax for jump tables

    // loading all the functions for animation initialization
    for (int i = 0; i < 6; ++i)
    {
        std::string path1 = "../gfx/characters/1/" + folder_paths1[i] + "/";
        std::string path2 = "../gfx/characters/2/" + folder_paths1[i] + "/";
        p1[i].fill_paths(path1.c_str());    p1[i].config_animation();   p1[i].update_scale(2.5f, 2.5f);
        p2[i].fill_paths(path2.c_str());    p2[i].config_animation();   p2[i].update_scale(2.5f, 2.5f);
    }
    
    for (int i = 0; i < 5; ++i)
    {
        std::string path1 = "../gfx/characters/3/" + folder_paths2[i] + "/";
        std::string path2 = "../gfx/characters/4/" + folder_paths2[i] + "/";
        p3[i].fill_paths(path1.c_str());    p3[i].config_animation();   p3[i].update_scale(1.5f, 1.5f);
        p4[i].fill_paths(path2.c_str());    p4[i].config_animation();   p4[i].update_scale(1.5f, 1.5f);
    }
    
    AnimSet player_anim_ptr[4] = { {p1, 6}, {p2, 6}, {p3, 5}, {p4, 5} };
    Player player(gaming_font, player_anim_ptr);

    // level files
    sf::Texture platform_tex;   platform_tex.loadFromFile("../gfx/tileset/1.png");
    sf::Sprite platform_sprite; platform_sprite.setTexture(platform_tex);

    StaticSprite level_platform_sprite(platform_sprite);
    AnimatedSprite animated_sprite(player.get_player_anim()[p_select].anims[0], "../gfx/characters/1/idle/");

    LevelMap static_level_items[1] = {{'P', &level_platform_sprite}};
    LevelMap dynamic_level_items[1] = {{'C', &animated_sprite}};

    BuildLevel level_1("../levels/level1.txt");
    level_1.initialize_entities(dynamic_level_items, 1);

    // snow effect
    sf::Texture snow_tex;   snow_tex.loadFromFile("../gfx/elements/snow.png");
    SnowBallEffect snow_effect(snow_tex, screen_size, 200);

    RgbEffect rgb_eff(0.015f);

    sf::Clock clock;

    bool is_running = true;
    while (is_running)
    {
        float time = clock.getElapsedTime().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                is_running = false;
            }

            if (check_click(window, pause_rect, event))
            {
                is_running = false;
            }
        }

        sf::Color final_rgb = rgb_eff.full_rgb(128.f);

        snow_effect.move_snow(time);

        window.clear(sf::Color::Black);
        window.draw(game_bg.get_sprite());
        snow_effect.draw_snow(window);

        level_1.draw_level(window, static_level_items, 1);
        player.draw_player(window, p_select);
        player.move_player(p_select);

        window.draw(game_ui.get_sprite());
        player.draw_stats(window, final_rgb);
        
        window.draw(pause_button.get_text());
        window.display();
    }

    for (int i = 0; i < 6; ++i)
    {
        p1[i].free_memory();    p2[i].free_memory();
    }
    for (int i = 0; i < 5; ++i)
    {
        p3[i].free_memory();    p4[i].free_memory();
    }
    return;
}

void level_selection(sf::RenderWindow& window, sf::Font& gaming_font, sf::Vector2u& screen_size, int& p_select, int& l_selection)
{
    sf::Texture snow_tex;   snow_tex.loadFromFile("../gfx/elements/snow.png");
    SnowBallEffect snow_effect(snow_tex, screen_size, 65);

    AssetsLoader map({0.f, 0.f}, "../gfx/bg/map_bg.png");

    FontLoader back_button(gaming_font, "Back", 25, sf::Color::White, {5.f, 2.f});
    sf::RectangleShape back_rect = back_button.get_text_rect(4);

    FontLoader start_game(gaming_font, "Start Game", 35, sf::Color::White, {350.f, 650.f});
    sf::RectangleShape start_rect = start_game.get_text_rect(9);

    sf::Clock clock;

    bool is_running = true;
    while (is_running)
    {
        float time = clock.getElapsedTime().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                is_running = false;
            }

            if (check_click(window, back_rect, event))
            {
                is_running = false;
            }

            if (check_click(window, start_rect, event))
            {
                main_gameplay(window, gaming_font, screen_size, p_select, l_selection);
            }
        }

        snow_effect.move_snow(time);

        window.clear(sf::Color::Black);
        window.draw(map.get_sprite());
        snow_effect.draw_snow(window);

        window.draw(back_button.get_text());
        window.draw(start_game.get_text());
        window.display();
    }

    return;
}

void player_selection(sf::RenderWindow& window, sf::Font& gaming_font, sf::Vector2u& screen_size, int& player_select, int& l_select)
{
    AssetsLoader players[4] = { 
        { {0.f, 0.f}, "../gfx/characters/selection/1.png"}, { {0.f, 0.f}, "../gfx/characters/selection/2.png"},
        { {0.f, 0.f}, "../gfx/characters/selection/3.png"}, { {0.f, 0.f}, "../gfx/characters/selection/4.png"}
    };
    AssetsLoader menu_bg({0.f, 0.f}, "../gfx/bg/setting.png"); 
    menu_bg.get_sprite().setColor(sf::Color(255, 255, 255, 65));
    
    sf::Texture snow_tex;   snow_tex.loadFromFile("../gfx/elements/snow.png");
    SnowBallEffect snow_effect(snow_tex, screen_size, 80);

    FontLoader previous(gaming_font, "<", 60, sf::Color::White, {20, static_cast<float>(window.getSize().y/2)});
    FontLoader next(gaming_font, ">", 60, sf::Color::White, {static_cast<float>(window.getSize().x - 50), static_cast<float>(window.getSize().y/2)});
    sf::RectangleShape prev_rect = previous.get_text_rect(1);
    sf::RectangleShape next_rect = next.get_text_rect(1);

    AnimationLoader p1_idle(4, 8, {100.f, 300.f}, sf::Color::White);
    AnimationLoader p2_idle(4, 8, {100.f, 300.f}, sf::Color::White);
    AnimationLoader p3_idle(8, 4, {70.f, 300.f}, sf::Color::White);
    AnimationLoader p4_idle(8, 4, {70.f, 300.f}, sf::Color::White);

    p1_idle.fill_paths("../gfx/characters/1/idle/");     p1_idle.config_animation();
    p2_idle.fill_paths("../gfx/characters/2/idle/");    p2_idle.config_animation();
    p3_idle.fill_paths("../gfx/characters/3/idle/");     p3_idle.config_animation();
    p4_idle.fill_paths("../gfx/characters/4/idle/");     p4_idle.config_animation();

    p1_idle.update_scale(4.5f, 4.5f);   p2_idle.update_scale(4.5f, 4.5f);   p3_idle.update_scale(2.5f, 2.5f);   p4_idle.update_scale(2.5f, 2.5f);

    AnimationLoader curr_animation[4] = {p1_idle, p2_idle, p3_idle, p4_idle};

    FontLoader select_font(gaming_font, "Select: ", 37, sf::Color::White, {350.f, 670.f});
    sf::RectangleShape select_rect = select_font.get_text_rect(9);

    FontLoader level_select_font(gaming_font, "Select Level", 30, sf::Color::White, {20.f, 680.f});
    sf::RectangleShape level_select_rect = level_select_font.get_text_rect(12);

    FontLoader back_button(gaming_font, "Back", 25, sf::Color::White, {5.f, 2.f});
    sf::RectangleShape back_rect = back_button.get_text_rect(4);

    short curr_index = 0;
    sf::Clock clock;

    RgbEffect new_rgb(0.075f);

    bool is_running = true;
    while (is_running)
    {
        sf::Vector2i raw_mouse_pos = sf::Mouse::getPosition();
        sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(raw_mouse_pos);

        float time = clock.getElapsedTime().asSeconds();
        sf::Color final_color = new_rgb.apply_rgb(127.5f, 255.f);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed))
            {
                is_running = false;
            }

            if (check_click(window, prev_rect, event) and (curr_index > 0))
            {
                curr_index--;
            }
    
            if (check_click(window, next_rect, event) and (curr_index < 3))
            {
                curr_index++;
            }

            if (check_click(window, select_rect, event))
            {
                player_select = curr_index;
            }

            if (check_click(window, back_rect, event))
            {
                is_running = false;
            }

            if (check_click(window, level_select_rect, event))
            {
                level_selection(window, gaming_font, screen_size, player_select, l_select);
            }
        }

        std::string new_msg = "Select: " + std::to_string(player_select+1);
        FontLoader select_font(gaming_font, new_msg, 37, final_color, {350.f, 670.f});

        window.clear(sf::Color::Black);
        
        window.draw(players[curr_index].get_sprite());
        
        window.draw(menu_bg.get_sprite());
        snow_effect.move_snow(time);
        snow_effect.draw_snow(window);

        curr_animation[curr_index].update_animation();
        curr_animation[curr_index].draw_animation(window);
        
        window.draw(previous.get_text());
        window.draw(next.get_text());
        window.draw(select_font.get_text());
        window.draw(level_select_font.get_text());
        window.draw(back_button.get_text());

        window.display();
    }

    for (int i = 0; i < 4; ++i)
        curr_animation[i].free_memory();
    
    return;
}