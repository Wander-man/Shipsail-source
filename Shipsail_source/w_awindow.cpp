#include "w_awindow.h"

Awindow::Awindow(sf::VideoMode vmode, const char* name, sf::Font& font, sf::Vector2i pos)
    : m_font(font),
    m_vmode(vmode),
    m_name(name),
    m_pos(pos)
{}