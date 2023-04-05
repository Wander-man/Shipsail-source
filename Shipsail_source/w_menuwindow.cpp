#include "w_menuwindow.h"

Menuwindow::Menuwindow(sf::VideoMode vmode, const char* name, sf::Font& font, sf::Vector2i pos, std::string user)
    : Awindow(vmode, name, font, pos),
    m_curusr(user),
    m_stats(user)
{}

std::string Menuwindow::launch()
{
    if(m_curusr == "") return "";
    //main menu init
    Button play("play", m_font, sf::Vector2f(250.0f, 210.0f), sf::Vector2f(250.0f, 60.0f), 40);
    Button stats("user stats", m_font, sf::Vector2f(250.0f, 300.0f), sf::Vector2f(250.0f, 60.0f), 40);
    Button changeuser("change user", m_font, sf::Vector2f(250.0f, 390.0f), sf::Vector2f(250.0f, 60.0f), 40);    
    Button exit("exit", m_font, sf::Vector2f(250.0f, 480.0f), sf::Vector2f(250.0f, 60.0f), 40);
        
    Tlabel menu("Main menu", m_font, sf::Vector2f(250.0f, 100.0f), 60);
    //(main menu init)

    
    //level menu init
    Button level1("level1", m_font, sf::Vector2f(250.0f, 210.0f), sf::Vector2f(250.0f, 60.0f), 40);
    Button level2("level2", m_font, sf::Vector2f(250.0f, 300.0f), sf::Vector2f(250.0f, 60.0f), 40);
    Button level3("level3", m_font, sf::Vector2f(250.0f, 390.0f), sf::Vector2f(250.0f, 60.0f), 40);
    Button back("back", m_font, sf::Vector2f(250.0f, 480.0f), sf::Vector2f(250.0f, 60.0f), 40);
        
    Tlabel levelselect("Levels", m_font, sf::Vector2f(250.0f, 100.0f), 59); 
    //(level menu init)


    //stats menu init 
    Tlabel statsl("Stats", m_font, sf::Vector2f(250.0f, 100.0f), 50);

    Tlabel sships("Small ships killed: " + std::to_string(m_stats.getcount(skilled)), m_font, sf::Vector2f(200.0f, 200.0f), 25);
    Tlabel armships("Armored ships killed: " + std::to_string(m_stats.getcount(armkilled)), m_font, sf::Vector2f(200.0f, 270.0f), 25);
    Tlabel towers("Towers built: " + std::to_string(m_stats.getcount(tbuilt)), m_font, sf::Vector2f(200.0f, 340.0f), 25);
    Tlabel timepl("Time played: " + std::to_string(m_stats.getcount(tplayed)), m_font, sf::Vector2f(200.0f, 410.0f), 25);
    Tlabel victories("Victories obtained: " + std::to_string(m_stats.getcount(vict)), m_font, sf::Vector2f(200.0f, 480.0f), 25);
    Tlabel losses("Defeats suffered: " + std::to_string(m_stats.getcount(loss)), m_font, sf::Vector2f(200.0f, 550.0f), 25); 
    Button backs("back", m_font, sf::Vector2f(250.0f, 625.0f), sf::Vector2f(250.0f, 60.0f), 40);

    Tlabel currentuser("current user: " + m_curusr, m_font, sf::Vector2f(50.0f, 15.0f), 15);   
    //(stats menu init)


    wmode mode = mainm;
    sf::RenderWindow window(m_vmode, m_name, sf::Style::Titlebar);
    window.setPosition(m_pos);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                m_stats.savestats();
                return "";
            }
            switch(mode)
            {
                case mainm:
                    if (exit.manage(event, window))
                    {
                        window.close();
                        m_stats.savestats();
                        return "";
                    }
                    if (stats.manage(event, window))
                    {
                        mode = statsm;
                    }
                    if (changeuser.manage(event, window))
                    {
                        Logwindow userchange(sf::VideoMode(300, 200), "login", m_font, sf::Vector2i(500, 300));
                        std::string buf = userchange.launch();
                        if(buf == "") break;
                        else m_curusr = buf;
                        currentuser.txt().setString("current user: " + m_curusr);

                        m_stats.changeuser(m_curusr);    

                        sships.setstr("Small ships killed: " + std::to_string(m_stats.getcount(skilled)));
                        armships.setstr("Armored ships killed: " + std::to_string(m_stats.getcount(armkilled)));
                        towers.setstr("Towers built: " + std::to_string(m_stats.getcount(tbuilt)));
                        timepl.setstr("Time played: " + std::to_string(m_stats.getcount(tplayed)));
                        victories.setstr("Victories obtained: " + std::to_string(m_stats.getcount(vict)));
                        losses.setstr("Defeats suffered: " + std::to_string(m_stats.getcount(loss)));
                    }
                    if (play.manage(event, window))
                    {
                        mode = levelsm;
                    }
                break;

                case levelsm:
                    if (level1.manage(event, window))
                    {
                        window.close();
                        return "level1";
                    }
                    if (level2.manage(event, window))
                    {
                        window.close();
                        return "level2";
                    }
                    if (level3.manage(event, window))
                    {
                        window.close();
                        return "level3";
                    }
                    if (back.manage(event, window))
                    {
                        mode = mainm;
                    }
                break;

                case statsm:
                    if (backs.manage(event, window))
                    {
                        mode = mainm;
                    }
                break;
            }          
            
        }

        window.display();
        window.clear(sf::Color(120, 100, 100));

        switch(mode)
        {
            case mainm:
                play.draw(window); 
                stats.draw(window);               
                changeuser.draw(window);
                exit.draw(window);
                menu.draw(window);
            break;

            case levelsm:
                level1.draw(window);
                level2.draw(window);
                level3.draw(window);
                back.draw(window);
                levelselect.draw(window);
            break;

            case statsm:
                backs.draw(window);
                sships.draw(window);
                armships.draw(window);
                towers.draw(window);
                timepl.draw(window);
                victories.draw(window);
                losses.draw(window);
                statsl.draw(window);
            break;
        }       

        currentuser.draw(window);

    } //!main loop------
}

void Menuwindow::getuser(std::string user)
{
    m_curusr = user;
}

Stats& Menuwindow::getstats()
{
    return m_stats;
}