#include "obj_aenemy.h"

Aenemy::Aenemy(const crdvect& path, float speed, int hp, float htime, int type)
    : m_path(path) 
{    
    m_obj.type = type;
    m_obj.coord.x = m_path.at(0).x;
    m_obj.coord.y = m_path.at(0).y;
    m_obj.speed = (speed);
    m_obj.multiplier = m_obj.speed / (m_obj.speed * 0.016f);
    m_obj.hp = (hp);
    m_obj.maxhp = hp;
    m_obj.holdtime = (htime);

    m_obj.healthbar.setPosition({0.0f,0.0f});
    m_obj.healthbar.setSize({10.0f,80.0f});
    m_obj.healthbar.setFillColor(sf::Color::Green);

    m_obj.animtime = (0);
    m_obj.animc.x = (0);
    m_obj.animc.y = (0);
    m_obj.prg.abs = (0);
    m_obj.prg.loc = (0);
    
    m_obj.isdone = (false);
    m_obj.todelete = (false);
    m_obj.killed = (false);
    m_obj.paid = false;
}

void Aenemy::getdir()
{
    if(fabs(m_obj.coord.x - m_path.at(m_obj.prg.abs + 1).x) < 0.1 && m_obj.coord.y > m_path.at(m_obj.prg.abs + 1).y) m_obj.cdir = {0.0f, -1.0f};
    if(fabs(m_obj.coord.x - m_path.at(m_obj.prg.abs + 1).x) < 0.1 && m_obj.coord.y < m_path.at(m_obj.prg.abs + 1).y) m_obj.cdir = {0.0f, 1.0f};
    if(fabs(m_obj.coord.y - m_path.at(m_obj.prg.abs + 1).y) < 0.1 && m_obj.coord.x > m_path.at(m_obj.prg.abs + 1).x) m_obj.cdir = {-1.0f, 0.0f};
    if(fabs(m_obj.coord.y - m_path.at(m_obj.prg.abs + 1).y) < 0.1 && m_obj.coord.x < m_path.at(m_obj.prg.abs + 1).x) m_obj.cdir = {1.0f, 0.0f};
}

void Aenemy::getdir(progress& prg)
{
    if(fabs(m_obj.coord.x - m_path.at(prg.abs + 1).x) < 0.1 && m_obj.coord.y > m_path.at(prg.abs + 1).y) m_obj.cdir = {0.0f, -1.0f};
    if(fabs(m_obj.coord.x - m_path.at(prg.abs + 1).x) < 0.1 && m_obj.coord.y < m_path.at(prg.abs + 1).y) m_obj.cdir = {0.0f, 1.0f};
    if(fabs(m_obj.coord.y - m_path.at(prg.abs + 1).y) < 0.1 && m_obj.coord.x > m_path.at(prg.abs + 1).x) m_obj.cdir = {-1.0f, 0.0f};
    if(fabs(m_obj.coord.y - m_path.at(prg.abs + 1).y) < 0.1 && m_obj.coord.x < m_path.at(prg.abs + 1).x) m_obj.cdir = {1.0f, 0.0f};
}

bool Aenemy::checkid(int id)
{
    for(auto i : m_bulletids)
    {
        if(id == i)
        {
            return true;
        }
    }
    return false;
}

void Aenemy::setid(int id)
{
    m_bulletids.push_back(id);
}

sf::Vector2f Aenemy::getcoords()
{
    sf::Vector2f buf = m_obj.sprite.getPosition();
    return sf::Vector2f(buf.x + 50, buf.y + 50);
}

sf::Vector2f Aenemy::getpredcoords(float delay)
{
    if(m_obj.killed)
    {
        return getcoords();
    }

    progress p{};

    p.abs = m_obj.prg.abs;
    p.loc = m_obj.prg.loc/100 + delay * m_obj.speed;

    while(p.loc >1)
    {
        p.abs++;
        p.loc -= 1;
    }    

    if(p.abs + 1 >= m_path.size())
    {
        return sf::Vector2f{-1000, -1000};
    }

    sf::Vector2f coords{(m_path.at(p.abs).x),(m_path.at(p.abs).y)};
    coords.x += 0.5f;
    coords.y += 0.5f;

    getdir(p);

    coords += m_obj.cdir * p.loc;

    return coords * 100.0f;
}

void Aenemy::healthbar()
{
    if(m_obj.hp < 0)
    {
        m_obj.hp = 0;
    }
    m_obj.healthbar.setSize({10.f, 80.0f / m_obj.maxhp * m_obj.hp});
}

int Aenemy::gettype()
{
    return m_obj.type;
}

bool Aenemy::isfinished()
{
    return m_obj.todelete;
}

bool Aenemy::iskilled()
{
    return m_obj.killed;
}

void Aenemy::paid()
{
    m_obj.paid = true;
}

bool Aenemy::ispaid()
{
    return m_obj.paid;
}

bool Aenemy::isdone()
{
    return m_obj.isdone;
}
