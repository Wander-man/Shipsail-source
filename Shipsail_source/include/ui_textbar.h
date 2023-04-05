#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "ui_tlabel.h"

class Textbar
{
    private:

        bool m_active;
        float m_length;
        Tlabel m_name;
        Tlabel m_text;
        sf::String m_buf;

        sf::RectangleShape m_backgr;

    public:

        //Constructor for a textbar (length is in characters)
        Textbar(sf::String name, sf::Font& font, sf::Vector2f pos, float length, int textsize);

        //Destructor
        ~Textbar() = default;

        //manage the textbar
        std::string manage(sf::Event& condition, sf::RenderWindow& window);

        //draw the textbar
        void draw(sf::RenderWindow& window);
};