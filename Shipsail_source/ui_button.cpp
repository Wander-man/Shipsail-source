#include "ui_button.h"

Button::Button(const char* bname, sf::Font& font, sf::Vector2f pos, sf::Vector2f size, int charsize) 
    : m_btext(bname, font), m_but()
{
    pos.x += 5;
    pos.y += 5;
    m_but.setPosition(pos);
    m_but.setSize(size);
    m_but.setFillColor(sf::Color::Black);
    m_but.setOutlineColor(sf::Color::Black);
    m_but.setOutlineThickness(5);    
    m_btext.setCharacterSize(charsize);
    m_btext.setFillColor(sf::Color::White);
    m_btext.setOrigin(static_cast <int> (m_btext.getLocalBounds().width / 2), static_cast <int> (m_btext.getLocalBounds().height / 2));
    sf::Rect<float> bounds(m_but.getGlobalBounds());
    m_btext.setPosition(static_cast <int> (bounds.width/2 + bounds.left), static_cast <int> (bounds.height/2 + bounds.top));

}

bool Button::manage(sf::Event& cond, sf::RenderWindow& window)
{
    sf::Vector2i mbcoord{0,0};
    switch(cond.type)
    {
        case(sf::Event::MouseMoved):

            mbcoord = {cond.mouseMove.x, cond.mouseMove.y};
            
            if(m_but.getGlobalBounds().contains(window.mapPixelToCoords(mbcoord)))
            {               
                if(m_but.getOutlineColor() != sf::Color::Cyan && m_but.getOutlineColor() !=sf::Color::Magenta) m_but.setOutlineColor(sf::Color::Cyan);
            }
            else
            {
                m_but.setOutlineColor(sf::Color::Black);
            }
        break;
        
        case(sf::Event::MouseButtonPressed):

            mbcoord = {cond.mouseButton.x, cond.mouseButton.y};
            if(m_but.getGlobalBounds().contains(window.mapPixelToCoords(mbcoord)))
            {
                if(cond.mouseButton.button == sf::Mouse::Left)
                {
                    m_but.setOutlineColor(sf::Color::Magenta);
                    m_but.setOutlineThickness(-5);
                }
            }
        break;

        case(sf::Event::MouseButtonReleased):

            mbcoord = {cond.mouseButton.x, cond.mouseButton.y};
            if(m_but.getGlobalBounds().contains(window.mapPixelToCoords(mbcoord)))
            {
                if(cond.mouseButton.button == sf::Mouse::Left)
                {
                    m_but.setOutlineColor(sf::Color::Cyan);
                    m_but.setOutlineThickness(5);
                    return true;
                }
            }
            else
            {
                m_but.setOutlineThickness(5);                
            }
        break;
    }
    return false;   
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(m_but);
    window.draw(m_btext);
}