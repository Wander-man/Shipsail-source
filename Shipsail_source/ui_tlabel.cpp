#include "ui_tlabel.h"

Tlabel::Tlabel(sf::String text, sf::Font& font, sf::Vector2f pos, int tsize) 
    : m_ltext(text, font, tsize)
{
    m_ltext.setPosition(pos);
}

sf::Text& Tlabel::txt()
{
    sf::Text& buf = m_ltext;
    return buf;
}

void Tlabel::setstr(sf::String newtext)
{
    m_ltext.setString(newtext);
}

void Tlabel::draw(sf::RenderWindow& window)
{
    window.draw(m_ltext);
}