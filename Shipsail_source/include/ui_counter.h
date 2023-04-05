#pragma once

#include <string>
#include "ui_tlabel.h"

class Counter
{
    private:

        Tlabel m_number;
        int m_amount;
        bool m_positive;

        //sets the amount to the label
        void settext();

    public:

        //constructor 
        Counter(sf::Vector2f pos, sf::Font& font, int textsize, int startvalue = 0, bool positive = true);

        //default destructor
        ~Counter() = default;

        //get amount
        int getamount();

        //add to the amount
        void add(int amount);

        //remove from the amount
        bool take(int amount);

        //draw label
        void draw(sf::RenderWindow& window);
};
