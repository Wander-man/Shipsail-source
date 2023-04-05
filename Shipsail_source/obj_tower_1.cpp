#include "obj_tower_1.h"

Tower1::Tower1(sf::Vector2f pos, int damage, int range, float as, int type, float projspeed, prlist& projs)
    : Atower(pos, damage, range, as, type, projspeed, projs)
{
    m_tow.spr.setTexture(s_text);
    m_tow.spr.setPosition(m_tow.coord);
    m_tow.spr.setTextureRect(sf::IntRect(m_tow.type FCADJ(TSIZE), 0, TSIZE, TSIZE));
}

void Tower1::fireat(sf::Vector2f target)
{
    m_projs.push_back({{m_tow.coord.x + 50, m_tow.coord.y + 50}, target, m_tow.damage, m_tow.projspeed, false, 0.15f});
}

bool Tower1::checkinrange(elist& elist)
{
    sf::Vector2f ecoordsbuf {-1,-1};

    for(auto i : elist)
    {
        if(i.get()->iskilled() || i.get()->isfinished()) continue;

        sf::Vector2f cbuf = i.get()->getcoords() - getcoords();
        if(cbuf + getcoords() == sf::Vector2f(-1000,-1000)) continue;
        float enterdist = sqrt(SQR(cbuf.x) + SQR(cbuf.y)) / 100;

        sf::Vector2f ecoords = i.get()->getpredcoords(enterdist / (m_tow.projspeed));
        cbuf = ecoords - getcoords();
        float exitdist = sqrt(SQR(cbuf.x) + SQR(cbuf.y))/100;

        ecoords = i.get()->getpredcoords(exitdist / (m_tow.projspeed));

        bool inrange = enterdist - 3 < m_tow.range && exitdist < m_tow.range;        
        
        if(i.get()->gettype() == 0)
        {
            if(inrange)
            {
                fireat(ecoords);
                return true;
            }
            else continue;            
        } 
        else
        {
            if(ecoordsbuf == sf::Vector2f(-1,-1) && inrange) 
            {
                ecoordsbuf = ecoords;
            }
        }  
    }
    
    if(ecoordsbuf != sf::Vector2f(-1,-1))
    {
        fireat(ecoordsbuf);
        return true;
    }

    return false;
}

void Tower1::manage(sf::RenderWindow& window, elist& elist, float currtime)
{
    if(m_tow.attackdelay <= m_tow.shoottime)
    {
        checkinrange(elist);
        m_tow.shoottime -= m_tow.attackdelay; 
    }
    else m_tow.shoottime += currtime;

    window.draw(m_tow.spr);
}

void Tower1::create(sf::Vector2f pos, int damage, int range, float adelay, float projspeed, prlist& projs, towlist& towlist)
{
    towlist.push_front(std::make_shared<Tower1>(pos, damage, range, adelay, 0, projspeed, projs));
}