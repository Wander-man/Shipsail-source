#pragma once

#include <SFML/Graphics.hpp>
#include "ui_textbar.h"
#include "ui_button.h"
#include <string>

class Awindow
{
    protected:

        sf::Font& m_font;
        sf::VideoMode m_vmode;
        std::string m_name;
        sf::Vector2i m_pos;

    public:

        //constructor
        Awindow(sf::VideoMode vmode, const char* name, sf::Font& font, sf::Vector2i pos = sf::Vector2i(0, 0));

        //default destructor
        virtual ~Awindow() = default;

        //launch window
        std::string virtual launch() = 0;
};