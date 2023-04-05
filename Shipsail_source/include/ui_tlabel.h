#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Tlabel
{
    private:

        sf::Text m_ltext;

    public:

        //label constructor
        Tlabel(sf::String text, sf::Font& font, sf::Vector2f pos, int texttsize);

        //default destructor
        ~Tlabel() = default;

        //get the text
        sf::Text& txt();

        //set string
        void setstr(sf::String newtext);

        //draw the label
        void draw(sf::RenderWindow& window);
};