#include "obj_atower.h"
#include "obj_projectile.h"
#include "cmath"

extern Icashe cashe;
sf::Texture Atower::s_text{};

Atower::Atower(sf::Vector2f pos, int damage, int range, float as, int type, float projspeed, prlist& projs)
    : m_projs(projs)
{
    
    m_tow.type = (type);
    m_tow.damage = (damage);
    m_tow.range = (range);
    m_tow.attackdelay = (as);
    m_tow.coord = (pos);
    m_tow.projspeed = (projspeed);
    m_tow.shoottime = m_tow.attackdelay;
}

sf::FloatRect Atower::getrect()
{
    return m_tow.spr.getGlobalBounds();
}

sf::Vector2f Atower::getcoords()
{
    return sf::Vector2f(m_tow.coord.x + 50, m_tow.coord.y + 50);
}

float Atower::getrange()
{
    return m_tow.range * 100;
} 

int Atower::gettype()
{
    return m_tow.type;
}

void Atower::settexture(const char* tfile)
{
    if (!s_text.loadFromImage(cashe.getimg(tfile)))
    {
        std::cout << "\nfailed to load texture" << std::endl;
    }
}