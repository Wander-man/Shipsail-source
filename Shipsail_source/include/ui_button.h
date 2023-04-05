#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "strndef.h"

class Button
{
    private:

        sf::Text m_btext;
        sf::RectangleShape m_but;

    public:

        //button constructor
        Button(const char* bname, sf::Font& font, sf::Vector2f pos, sf::Vector2f size = sf::Vector2f(150,100), int charsize = 40);

        //default destructor
        ~Button() = default;

        //manage the button, return 1 if pressed
        bool manage(sf::Event& condition, sf::RenderWindow& window);

        //draw the button
        void draw(sf::RenderWindow& window);
};