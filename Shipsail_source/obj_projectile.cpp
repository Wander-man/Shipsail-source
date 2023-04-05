#include "obj_projectile.h"

sf::Texture Projectile::s_text{};
extern Icashe cashe;

Projectile::Projectile(sf::Vector2f origin, sf::Vector2f dest, int damage, float speed, bool pierce, float htime)
{ 
    m_proj.id = xorshift();
    m_proj.pierce = (pierce); 
    m_proj.damage = (damage);
    m_proj.speed = (speed);
    m_proj.holdtime = (htime);
    m_proj.dir = (norm(dest - origin));

    sf::Vector2f buf = dest - origin;
    m_proj.pathlen_sqr = (SQR( ((buf) / static_cast <float> (TSIZE) ).x ) + SQR( ((buf) / static_cast <float> (TSIZE) ).y ));
    m_proj.travdist = (0);
    m_proj.animc = (0);
    m_proj.animtime = (0);
    m_proj.isdone = (false);
    m_proj.hit = false;

    m_proj.spr.setTexture(s_text);
    m_proj.spr.setTextureRect(sf::IntRect(0, 0, PRSIZE, PRSIZE));
    if(m_proj.pierce) m_proj.spr.setScale(5.0f, 5.0f);
    else m_proj.spr.setScale(2.5f, 2.5f);

    sf::Rect <float> bufrect = m_proj.spr.getLocalBounds();
    m_proj.spr.setOrigin(static_cast <int> (bufrect.width / 2), static_cast <int> (bufrect.height / 2));    
    m_proj.spr.setPosition(origin);

    m_proj.multiplier = m_proj.speed / (m_proj.speed * 0.016f);
}

void Projectile::anim()
{
    while (m_proj.animtime >= m_proj.holdtime)
    {  
        m_proj.animtime -= m_proj.holdtime;
        if(m_proj.animc == 3) m_proj.animc = 0;
        else m_proj.animc++;

        if(m_proj.hit) m_proj.spr.scale(1.3f, 1.3f);
        if(m_proj.spr.getScale().x > 9.0f && m_proj.pierce || m_proj.spr.getScale().x > 5.0f && !m_proj.pierce) m_proj.isdone = true;
    }
    setsprite();
}

void Projectile::setsprite()
{
    m_proj.spr.setTextureRect(sf::IntRect(m_proj.animc FCADJ(PRSIZE), 0, PRSIZE, PRSIZE)); 
}

void Projectile::nextmove(float timepassed)
{
    m_proj.travdist += (m_proj.speed * timepassed * m_proj.multiplier) / 100;
    m_proj.spr.move(m_proj.dir * m_proj.speed * timepassed * m_proj.multiplier);

    if(SQR(m_proj.travdist) > m_proj.pathlen_sqr + 8)
    {
        m_proj.isdone = true;
    }
}

sf::Vector2f Projectile::getcoord()
{
    return m_proj.spr.getPosition();
}

bool Projectile::finished()
{
    return m_proj.isdone;
}

int Projectile::damage()
{
    return m_proj.damage;
}

bool Projectile::piercing()
{
    return m_proj.pierce;
}

void Projectile::sethit()
{
    m_proj.hit = true;
}

int Projectile::getid()
{
    return m_proj.id;
}

void Projectile::manage(sf::RenderWindow& window, float currtime)
{
    m_proj.animtime += currtime;
    
    if(!m_proj.hit) nextmove(currtime);
    anim();

    window.draw(m_proj.spr);
}

void Projectile::settexture(const char *tfile)
{
    if (!s_text.loadFromImage(cashe.getimg(tfile)))
    {
        std::cout << "\nfailed to load texture" << std::endl;
    }
}