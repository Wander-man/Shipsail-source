#include "obj_enemy_sship.h"

extern Icashe cashe;

sf::Texture Sship::s_text{};

Sship::Sship(const crdvect &path, float speed, int hp, float htime, int type) 
    : Aenemy(path, speed, hp, htime, type)
{
    m_obj.sprite.setTexture(s_text);
    m_obj.sprite.setPosition(sf::Vector2f(m_obj.coord.x FCADJ(TSIZE), m_obj.coord.y FCADJ(TSIZE)));
    m_obj.healthbar.setPosition(sf::Vector2f(m_obj.coord.x FCADJ(TSIZE), m_obj.coord.y FCADJ(TSIZE)));
}

void Sship::setsprite()
{
    m_obj.sprite.setTextureRect(sf::IntRect(m_obj.animc.x FCADJ(TSIZE), m_obj.animc.y FCADJ(TSIZE), TSIZE, TSIZE));
}

void Sship::nextmove(float timepassed)
{
    bool next;
    m_obj.prg.loc += m_obj.speed * timepassed * m_obj.multiplier;

    if (m_obj.prg.loc > 100)
    {
        next = true;
        m_obj.prg.abs++;
        m_obj.prg.loc -= 100;
    }    

    if (m_obj.prg.abs == m_path.size() - 1)
    {
        m_obj.isdone = true;
        return;
    }

    if (next)
    {
        getdir();

        m_obj.sprite.move(m_obj.cdir * ((m_obj.speed * timepassed * m_obj.multiplier) - m_obj.prg.loc));
        m_obj.healthbar.move(m_obj.cdir * ((m_obj.speed * timepassed * m_obj.multiplier) - m_obj.prg.loc));

        m_obj.coord.x = m_obj.sprite.getPosition().x / 100.0f;
        m_obj.coord.y = m_obj.sprite.getPosition().y / 100.0f;

        getdir();

        m_obj.sprite.move(m_obj.cdir * m_obj.prg.loc);
        m_obj.healthbar.move(m_obj.cdir * m_obj.prg.loc);

        m_obj.coord.x = m_obj.sprite.getPosition().x / 100.0f;
        m_obj.coord.y = m_obj.sprite.getPosition().y / 100.0f;

        next = false;
    }
    else
    {
        getdir();

        m_obj.sprite.move(m_obj.cdir * m_obj.speed * timepassed * m_obj.multiplier);
        m_obj.healthbar.move(m_obj.cdir * m_obj.speed * timepassed * m_obj.multiplier);

        m_obj.coord.x = m_obj.sprite.getPosition().x / 100.0f;
        m_obj.coord.y = m_obj.sprite.getPosition().y / 100.0f;
    }
}

void Sship::anim()
{
    int incr(1);

    while (m_obj.animtime >= m_obj.holdtime)
    {       
        m_obj.animtime -= m_obj.holdtime;

        int cond = m_obj.cdir.x + 2 * m_obj.cdir.y;
        switch(cond)
        {
            case(-1):

                m_obj.animc.y = 0;
            break;

            case(2):

                m_obj.animc.y = 1;
            break;

            case(1):

                m_obj.animc.y = 2;
            break;

            case(-2):

                m_obj.animc.y = 3;
            break;  
        }

        if(m_obj.isdone)
        {
            incr = -1;
            if(m_obj.animc.x > 5) m_obj.animc.x = 5;
        }
        if(m_obj.killed)
        {
            incr = 1;
            m_obj.animc.y = 4;
            if(m_obj.animc.x > 5) m_obj.animc.x = 0;
        }

        if (m_obj.animc.x == 12) m_obj.animc.x = 5;
        else m_obj.animc.x += incr;    

        if(m_obj.animc.x < 0 || m_obj.animc.x > 4 && m_obj.killed) m_obj.todelete = true;    
    }
    setsprite();
}

bool Sship::checkcoll(prlist& prlist)
{    
    for (prlist::iterator i = prlist.begin(); i != prlist.end();)
    {
        if(m_obj.sprite.getGlobalBounds().contains(i->getcoord()) && !checkid(i->getid()))
        {
            setid(i->getid());

            if(i->piercing())
            {
                m_obj.hp -= i->damage();
            }
            else 
            {
                m_obj.hp -= i->damage();
                i->sethit();
            }
            
            if(m_obj.hp <=0) m_obj.killed = true;
        }
        i++;        
    }
}

void Sship::manage(sf::RenderWindow &window, prlist& prlist, float currtime)
{
    m_obj.animtime += currtime;
    if(!m_obj.isdone && !m_obj.killed) nextmove(currtime);
    anim();

    checkcoll(prlist);

    healthbar();

    window.draw(m_obj.healthbar);
    window.draw(m_obj.sprite);
}

float Sship::getspeed()
{
    return m_obj.speed;
}


//-------------------STATIC--------------

void Sship::settexture(const char *tfile)
{
    if (!s_text.loadFromImage(cashe.getimg(tfile)))
    {
        std::cout << "\nfailed to load texture" << std::endl;
    }
}

void Sship::create(const crdvect& path, float speed, int hp, float htime, elist& elist)
{
    elist.push_back(std::make_shared<Sship>(path, speed, hp, 0.15f, 0));
}