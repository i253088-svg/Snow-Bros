#include "../header/menu.hpp"
#include "../header/vfx.hpp"

#define ACTIVE_OUTLINE  sf::Color::Yellow
#define DEFAULT_OUTLINE sf::Color::White
#define ERROR_COLOR sf::Color(220, 60, 60)

static const char* DB_PATH = "../data/users.txt";

static sf::RectangleShape make_box(sf::Vector2f pos)
{
    sf::RectangleShape box(sf::Vector2f(510.f, 50.f));
    box.setPosition(pos);
    box.setFillColor(sf::Color(255, 255, 255, 40));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2.f);
    return box;
}

static void draw_field(sf::RenderWindow& window, sf::Font& font, const char* label, const std::string& display_str, sf::Vector2f label_pos, sf::RectangleShape& box)
{
    FontLoader lbl(font, label, 28, sf::Color::White, label_pos);
    window.draw(lbl.get_text());
    window.draw(box);

    sf::Vector2f text_pos(box.getPosition().x + 10.f, box.getPosition().y + 8.f);
    FontLoader val(font, display_str.c_str(), 26, sf::Color::White, text_pos);  
    window.draw(val.get_text());
}

bool display_signin(sf::RenderWindow& window, Database& db)
{
    sf::Font font;
    font.loadFromFile("../font/font.ttf");

    FontLoader header(font, "SIGN IN", 70, sf::Color::White, {330.f, 50.f});
    FontLoader btn_lbl(font, "SIGN IN", 30, sf::Color::White, {455.f, 473.f});

    AssetsLoader bg({0.f, 0.f}, "../gfx/bg/bg.png");
    bg.get_sprite().setColor(sf::Color(255, 255, 255, 185));

    sf::RectangleShape ubox = make_box({245.f, 240.f});
    sf::RectangleShape pbox = make_box({245.f, 360.f});

    sf::RectangleShape signin_btn(sf::Vector2f(510.f, 55.f));
    signin_btn.setPosition(245.f, 460.f);
    signin_btn.setFillColor(sf::Color(255, 255, 255, 60));
    signin_btn.setOutlineColor(sf::Color::White);
    signin_btn.setOutlineThickness(2.f);

    std::string username_input, password_input;
    std::string status_msg = "";
    sf::Color   status_color = sf::Color::White;

    const int FIELD_NONE = 0;
    const int FIELD_USERNAME = 1;
    const int FIELD_PASSWORD = 2;

    int active = FIELD_NONE;
    bool success = false;
    bool is_running = true;

    sf::Clock cursor_clock;
    bool cursor_visible = true;

    while (is_running)
    {
        if (cursor_clock.getElapsedTime().asSeconds() >= 0.5f)
        {
            cursor_visible = !cursor_visible;
            cursor_clock.restart();
        }

        ubox.setOutlineColor(active == FIELD_USERNAME ? ACTIVE_OUTLINE : DEFAULT_OUTLINE);
        pbox.setOutlineColor(active == FIELD_PASSWORD ? ACTIVE_OUTLINE : DEFAULT_OUTLINE);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                is_running = false;   
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (ubox.getGlobalBounds().contains(mouse)) 
                    active = FIELD_USERNAME;
                else if (pbox.getGlobalBounds().contains(mouse)) 
                    active = FIELD_PASSWORD;
                else if (signin_btn.getGlobalBounds().contains(mouse))
                {
                    if (username_input.empty() || password_input.empty())
                    {
                        status_msg = "Please fill in all fields.";
                        status_color = ERROR_COLOR;
                    }
                    else if (db.verify_user(username_input, password_input))
                    {
                        success = true;
                        is_running = false;
                    }
                    else
                    {
                        status_msg = "Invalid username or password.";
                        status_color = ERROR_COLOR;
                    }
                }
                else active = FIELD_NONE;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    is_running = false;   

                if (event.key.code == sf::Keyboard::Tab)
                    active = (active == FIELD_USERNAME) ? FIELD_PASSWORD : FIELD_USERNAME;

                if (event.key.code == sf::Keyboard::Return)
                {
                    if (db.verify_user(username_input, password_input))
                    {
                        success = true;
                        is_running = false;
                    }
                    else
                    {
                        status_msg = "Invalid username or password.";
                        status_color = ERROR_COLOR;
                    }
                }

                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    if (active == FIELD_USERNAME && !username_input.empty()) username_input.pop_back();
                    if (active == FIELD_PASSWORD && !password_input.empty()) password_input.pop_back();
                    status_msg = "";
                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                char c = static_cast<char>(event.text.unicode);
                if (c >= 32 && c < 127)
                {
                    if (active == FIELD_USERNAME && (int)username_input.size() < 20)
                        { username_input += c; status_msg = ""; }
                    if (active == FIELD_PASSWORD && (int)password_input.size() < 30)
                        { password_input += c; status_msg = ""; }
                }
            }
        }

        std::string u_disp = username_input + (active == FIELD_USERNAME && cursor_visible ? "|" : "");
        std::string p_disp = std::string(password_input.size(), '*') + (active == FIELD_PASSWORD && cursor_visible ? "|" : "");

        window.clear(sf::Color::Black);
        window.draw(bg.get_sprite());

        window.draw(header.get_text());

        draw_field(window, font, "USERNAME", u_disp, {245.f, 200.f}, ubox);
        draw_field(window, font, "PASSWORD", p_disp, {245.f, 320.f}, pbox);

        window.draw(signin_btn);
        window.draw(btn_lbl.get_text());

        if (!status_msg.empty())
        {
            FontLoader status(font, status_msg.c_str(), 22, status_color, {245.f, 530.f});
            window.draw(status.get_text());
        }

        window.display();
    }

    return success;
}


void display_signup(sf::RenderWindow& window, Database& db)
{
    sf::Font font;
    font.loadFromFile("../font/font.ttf");
    FontLoader header(font, "SIGN UP", 70, sf::Color::White, {330.f, 30.f});
    FontLoader btn_lbl(font, "CREATE ACCOUNT", 26, sf::Color::White, {390.f, 583.f});

    AssetsLoader bg({0.f, 0.f}, "../gfx/bg/bg.png");
    bg.get_sprite().setColor(sf::Color(255, 255, 255, 185));

    sf::RectangleShape ubox = make_box({245.f, 200.f});
    sf::RectangleShape pbox = make_box({245.f, 340.f});
    sf::RectangleShape ebox = make_box({245.f, 480.f});

    sf::RectangleShape signup_btn(sf::Vector2f(510.f, 55.f));
    signup_btn.setPosition(245.f, 570.f);
    signup_btn.setFillColor(sf::Color(255, 255, 255, 60));
    signup_btn.setOutlineColor(sf::Color::White);
    signup_btn.setOutlineThickness(2.f);

    std::string username_input, password_input, email_input;
    std::string status_msg   = "";
    sf::Color status_color = sf::Color::White;

    const int FIELD_NONE = 0;
    const int FIELD_USERNAME = 1;
    const int FIELD_PASSWORD = 2;
    const int FIELD_EMAIL = 3;

    int  active = FIELD_NONE;
    bool is_running = true;

    sf::Clock cursor_clock;
    bool cursor_visible = true;

    while (is_running)
    {
        if (cursor_clock.getElapsedTime().asSeconds() >= 0.5f)
        {
            cursor_visible = !cursor_visible;
            cursor_clock.restart();
        }

        ubox.setOutlineColor(active == FIELD_USERNAME ? ACTIVE_OUTLINE : DEFAULT_OUTLINE);
        pbox.setOutlineColor(active == FIELD_PASSWORD ? ACTIVE_OUTLINE : DEFAULT_OUTLINE);
        ebox.setOutlineColor(active == FIELD_EMAIL ? ACTIVE_OUTLINE : DEFAULT_OUTLINE);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                is_running = false;

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (ubox.getGlobalBounds().contains(mouse)) 
                    active = FIELD_USERNAME;

                else if (pbox.getGlobalBounds().contains(mouse)) 
                    active = FIELD_PASSWORD;

                else if (ebox.getGlobalBounds().contains(mouse)) 
                    active = FIELD_EMAIL;
                    
                else if (signup_btn.getGlobalBounds().contains(mouse))
                {
                    if (username_input.empty() || password_input.empty() || email_input.empty())
                    {
                        status_msg = "Please fill in all fields.";
                        status_color = ERROR_COLOR;
                    }
                    else if ((int)password_input.size() < 6)
                    {
                        status_msg = "Password must be at least 6 characters.";
                        status_color = ERROR_COLOR;
                    }
                    else if (db.user_exists(username_input))
                    {
                        status_msg   = "Username already taken.";
                        status_color = ERROR_COLOR;
                        ubox.setOutlineColor(ERROR_COLOR);
                    }
                    else
                    {
                        db.add_user(username_input, password_input, email_input);
                        db.save_to_file(DB_PATH);
                        status_msg = "Account created! You can now sign in.";
                        status_color = sf::Color::Green;
                        is_running = false;
                    }
                }
                else 
                    active = FIELD_NONE;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    is_running = false;

                if (event.key.code == sf::Keyboard::Tab)
                {
                    if (active == FIELD_USERNAME) 
                        active = FIELD_PASSWORD;
                    else if (active == FIELD_PASSWORD) 
                        active = FIELD_EMAIL;
                    else
                        active = FIELD_USERNAME;
                }

                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    if (active == FIELD_USERNAME && !username_input.empty()) 
                        username_input.pop_back();
                    if (active == FIELD_PASSWORD && !password_input.empty()) 
                        password_input.pop_back();
                    if (active == FIELD_EMAIL && !email_input.empty())    
                        email_input.pop_back();
                    status_msg = "";
                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                char c = static_cast<char>(event.text.unicode);
                if (c >= 32 && c < 127)
                {
                    if (active == FIELD_USERNAME && (int)username_input.size() < 20)
                        username_input += c; status_msg = ""; 
                    if (active == FIELD_PASSWORD && (int)password_input.size() < 30)
                        password_input += c; status_msg = ""; 
                    if (active == FIELD_EMAIL    && (int)email_input.size()    < 40)
                        email_input    += c; status_msg = ""; 
                }
            }
        }

        std::string u_disp = username_input + ((active == FIELD_USERNAME && cursor_visible) ? "|" : "");
        std::string p_disp = std::string(password_input.size(), '*') + ((active == FIELD_PASSWORD && cursor_visible) ? "|" : "");
        std::string e_disp = email_input + ((active == FIELD_EMAIL && cursor_visible) ? "|" : "");

        window.clear(sf::Color::Black);
        window.draw(bg.get_sprite());

        window.draw(header.get_text());

        draw_field(window, font, "USERNAME", u_disp, {245.f, 160.f}, ubox);
        draw_field(window, font, "PASSWORD", p_disp, {245.f, 300.f}, pbox);
        draw_field(window, font, "EMAIL",    e_disp, {245.f, 440.f}, ebox);

        window.draw(signup_btn);
        window.draw(btn_lbl.get_text());

        if (!status_msg.empty())
        {
            FontLoader status(font, status_msg.c_str(), 22, status_color, {245.f, 645.f});
            window.draw(status.get_text());
        }

        window.display();
    }
}

void display_leaderbord(sf::RenderWindow& window, sf::Vector2u& screen_size)
{
    sf::Font font;
    font.loadFromFile("../font/font.ttf");
    AssetsLoader bg({0.f, 0.f}, "../gfx/bg/bg.png");
    bg.get_sprite().setColor(sf::Color(255, 255, 255, 175));

    FontLoader header(font, "LEADERBOARD", 70, sf::Color::White, {245.f, 50.f});

    sf::Texture snow_tex;   snow_tex.loadFromFile("../gfx/elements/snow.png");
    SnowBallEffect snow_effect(snow_tex, screen_size, 255);

    sf::Clock clock;
    
    bool is_running = true;
    while (is_running ) 
    {
        float time = clock.getElapsedTime().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                is_running = false;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    is_running = false;
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(bg.get_sprite());

        snow_effect.move_snow(time);
        snow_effect.draw_snow(window);

        window.draw(header.get_text());  
        
        window.display();           
    }
    return;
}


void display_settings(sf::RenderWindow& window, sf::Vector2u& screen_size)
{
    sf::Font font;
    font.loadFromFile("../font/font.ttf");

    sf::Texture snow_tex;   snow_tex.loadFromFile("../gfx/elements/snow.png");
    SnowBallEffect snow_effect(snow_tex, screen_size, 255);

    AssetsLoader bg({0.f, 0.f}, "../gfx/bg/bg.png");
    bg.get_sprite().setColor(sf::Color(255, 255, 255, 175));

    FontLoader header(font, "SETTINGS", 70, sf::Color::White, {310.f, 50.f});
    sf::Clock clock;

    bool is_running = true;
    while (is_running)
    {
        float time = clock.getElapsedTime().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                is_running = false;

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    is_running = false;
        }

        window.clear(sf::Color::Black);
        window.draw(bg.get_sprite());

        snow_effect.move_snow(time);
        snow_effect.draw_snow(window);
        
        window.draw(header.get_text()); 
        window.display();
    }
    return;
}
