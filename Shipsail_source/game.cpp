#include "game.h"

Game::Game(sf::VideoMode vmode, const char* name, sf::Font& font, sf::Vector2i pos, ivect& tow, crdvect& path, Gamemaptext& maptext, Stats& stats, int money, int m_basehp)
    : Awindow(vmode, name, font, pos),
    m_tow(tow),    
    m_path(path), 
    m_maptext(maptext),
    m_stats(stats),
    m_money({2100.0f, 1150.0f}, font, 30, money),
    m_basehp({2100, 950}, font, 30, m_basehp)
{
    for(auto i : tow)
    {
        m_built[i] = false;
    }
}

bool Game::tcreate(int type, sf::Event cond, prlist& proj, towlist& tows, sf::RenderWindow& window)
{    
    int price;
    switch(type)
    {
        case 0:
            price = 10;  
        break;

        case 1:
            price = 20;
        break;

        case 2:
            price = 50;
        break;
    }

    sf::Vector2f buf = window.mapPixelToCoords(sf::Vector2i{cond.mouseButton.x, cond.mouseButton.y});
    for(auto i : m_tow)
    {        
        if(!m_built.at(i))
        {
            sf::Vector2f coords = numtocoords (i, 20, 20, 50.0f);                 
            if(sqrt( SQR((buf - coords).x) + SQR((buf - coords).y )) < 50.0f && m_money.take(price))
            {
                m_built.at(i) = true;
                switch(type)
                {
                    case 0:

                        Tower1::create(sf::Vector2f(coords.x - 50.0f, coords.y - 50.0f), 4, 3, 1.0f, 5.0f, proj, tows);                        
                    break;

                    case 1:

                        Tower2::create(sf::Vector2f(coords.x - 50.0f , coords.y - 50.0f), 2, 3, 2.0f, 4.0f, proj, tows);  
                    break;

                    case 2:

                        Tower3::create(sf::Vector2f(coords.x - 50.0f , coords.y - 50.0f), 1, 5, 1.0f, 5.0f, proj, tows);
                    break;
                }
                m_stats.upcount(tbuilt);
            }
        }        
    }    
}


std::string Game::launch()
{
    Button exitb("Exit", m_font, {2100.0f, 100.0f});    

    Tlabel message1("LMB to set tower1\nRMB to set tower2\nMMB to set tower3", m_font, {2100.0f, 300.0f}, 30);
    Tlabel message2("tower1 is 10 gold\ntower2 is 20 gold\ntower3 is 50 gold", m_font, {2100.0f, 500.0f}, 30);
    Tlabel victorym("Victory", m_font, {1000.0f, 1000.0f}, 40);
    Tlabel defeatm("Defeat", m_font, {1000.0f, 1000.0f}, 35);

    Tlabel hp ("HP:", m_font, {2100.0f, 900.0f}, 34);
    Tlabel golde("Gold:", m_font, {2100.0f, 1100.0f}, 34);

    float sships(0), armships(0), total(0);
    float sdelay(2.0f), armdelay(5.0f);
    sf::Clock clock;
    elist enemies{};
    prlist projectiles{};
    towlist tlist{};    
    
    bool victory = false;
    bool defeat = false;

    sf::RenderWindow window(sf::VideoMode(1000, 750), "Shipsail", sf::Style::Titlebar);
    window.setView(sf::View(sf::Vector2f(13 FCADJ(TSIZE), 10 FCADJ(TSIZE)), sf::Vector2f(26 FCADJ(TSIZE), 20 FCADJ(TSIZE))));
    window.setPosition(sf::Vector2i(0, 0));

    //main loop------------------------------------------------------------------
    while (window.isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        sships += dt;
        armships += dt;
        total += dt;

        if(total > 60) victory = true;
        if(m_basehp.getamount() <= 0) defeat = true;

        window.clear(sf::Color(120, 100, 100));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (exitb.manage(event, window))
            {
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                tcreate(0, event, projectiles, tlist, window);
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                tcreate(1, event, projectiles, tlist, window);             
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle)
            {
                tcreate(2, event, projectiles, tlist, window);           
            }
        }
         
        if(!victory && !defeat)
        {
            if(total > 30) 
            {
                sdelay = 1.2f;
                armdelay = 4.0f;
            }
            if(total > 50) 
            {
                sdelay = 0.8f;
                armdelay = 3.0f;
            }

            if (sships > sdelay)
            {
                Sship::create(m_path, 4.5f, 20, 0.15f, enemies);
                sships = 0;
            }
            if (armships > armdelay)
            {
                Armship::create(m_path, 3.0f, 50, 0.15f, enemies);
                armships = 0;
            }       
        
            clock.restart();
            window.draw(m_maptext);                              

            for (towlist::iterator j = tlist.begin(); j != tlist.end(); ++j)
            {
                int f = j->get()->gettype();
                switch(f)
                {
                    case 0:

                        (dynamic_cast<Tower1*>(j->get()))->manage(window, enemies, dt);
                        break;

                    case 1:

                        (dynamic_cast<Tower2*>(j->get()))->manage(window, enemies, dt);
                        break;
                    
                    case 2:

                        (dynamic_cast<Tower3*>(j->get()))->manage(window, enemies, dt);
                        break;
                }
                
            }
            
            for (elist::iterator i = enemies.begin(); i != enemies.end();)
            {
                if ((i->get())->isfinished())
                {
                    i = enemies.erase(i);
                }
                else
                {
                    int f = i->get()->gettype();
                    switch(f)
                    {
                        case 0:
                            
                            if((i->get())->isdone() && !(i->get())->ispaid())
                            {
                                m_basehp.take(1);
                                (i->get())->paid();
                            } 
                            if((i->get())->iskilled() && !(i->get())->ispaid())
                            {
                                m_money.add(3);
                                (i->get())->paid();
                                m_stats.upcount(skilled);
                            } 
                            (dynamic_cast<Sship*>(i->get()))->manage(window, projectiles, dt);
                            break;

                        case 1:

                            if((i->get())->isdone() && !(i->get())->ispaid())
                            {
                                m_basehp.take(3);
                                (i->get())->paid();
                            } 
                            if((i->get())->iskilled() && !(i->get())->ispaid())
                            {
                                m_money.add(6);
                                (i->get())->paid();
                                m_stats.upcount(armkilled);
                            } 
                            (dynamic_cast<Armship*>(i->get()))->manage(window, projectiles, dt);
                            break;
                    } 
                    i++;
                }
            }
            
            for (prlist::iterator j = projectiles.begin(); j != projectiles.end();)
            {
                if (j->finished())
                {
                    j = projectiles.erase(j);
                }
                else
                {
                    j->manage(window, dt);
                    j++;
                }
            }
            
            message1.draw(window);
            message2.draw(window);
            m_money.draw(window);
            golde.draw(window);
            m_basehp.draw(window);
            hp.draw(window);
        }
        else 
        {
            if(!defeat && victory)
            {
                victorym.draw(window);                
            }
            else
            {
                defeatm.draw(window);
            }
        }

        exitb.draw(window);
        window.display();
    } //!main loop------------
    if(victory) m_stats.upcount(vict);
    if(defeat) m_stats.upcount(loss);
    
    m_stats.upcount(tplayed, static_cast <int> (total));

    return "end";
}