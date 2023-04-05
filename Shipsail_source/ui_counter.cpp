#include "ui_counter.h"

Counter::Counter(sf::Vector2f pos, sf::Font& font, int textsize, int startvalue, bool positive)
    :  m_number(std::to_string(startvalue), font, pos, textsize), m_amount(startvalue), m_positive(positive)
{}

void Counter::settext()
{
    m_number.setstr(std::to_string(m_amount));
}

int Counter::getamount()
{
    return m_amount;
}

void Counter::add(int val)
{
    m_amount += val;
    settext();
}

bool Counter::take(int val)
{
    if(m_positive && m_amount < val) return false;
    else
    {
        m_amount -= val;
        settext();
        return true;
    }
}

void Counter::draw(sf::RenderWindow& window)
{
    m_number.draw(window);
}