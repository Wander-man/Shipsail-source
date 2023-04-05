#include "ui_textbar.h"

Textbar::Textbar(sf::String name, sf::Font &font, sf::Vector2f pos, float length, int textsize)
    : m_name(name, font, pos, textsize), 
    m_text("", font, pos, textsize), 
    m_length(length), m_active(false)
{
    m_backgr.setSize({length * 10, 25.0f});
    m_backgr.setPosition(pos);
    m_backgr.setFillColor(sf::Color::Black);
    sf::Vector2f namepos = {pos.x - 5 - m_name.txt().getLocalBounds().width, pos.y + 5.0f};
    m_name.txt().setPosition(namepos);
    m_text.txt().setPosition(pos.x + 5, pos.y + 4);
}

std::string Textbar::manage(sf::Event &cond, sf::RenderWindow &window)
{
    sf::Vector2i mbcoord{0, 0};

    switch (cond.type)
    {
        case (sf::Event::MouseButtonPressed):

            mbcoord = {cond.mouseButton.x, cond.mouseButton.y};
            if (m_backgr.getGlobalBounds().contains(window.mapPixelToCoords(mbcoord)))
            {
                if (cond.mouseButton.button == sf::Mouse::Left)
                {
                    m_backgr.setOutlineColor(sf::Color::Magenta);
                    m_backgr.setOutlineThickness(-3);
                    m_active = true;
                }
            }
            else
            {
                m_active = false;
                m_backgr.setOutlineThickness(0);
            }
        break;

        case (sf::Event::TextEntered):

            if (m_active)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
                {
                    if (m_buf.getSize() >= 1)
                    {
                        m_buf.erase(m_buf.getSize() - 1);
                        m_text.setstr(m_buf);
                    }
                }
                else
                {
                    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                    {
                        if (m_buf.getSize() <= m_length)
                        {
                            if(cond.text.unicode <= 126 && cond.text.unicode >= 32)
                            m_buf += cond.text.unicode;
                            m_text.setstr(m_buf);
                        }
                    }                
                }
            }
        break;
    }
    
    return m_buf;
}

void Textbar::draw(sf::RenderWindow &window)
{
    window.draw(m_backgr);
    m_text.draw(window);
    m_name.draw(window);
}
