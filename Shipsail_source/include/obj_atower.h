#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "strndef.h"
#include "obj_projectile.h"
#include "obj_aenemy.h"

struct tdata
{
    sf::Sprite spr;
    int type;
    sf::Vector2f coord;

    float shoottime;     //equal to animtime
    float attackdelay;   //and holdtime

    float range;
    int damage;
    float projspeed;
       // n/s, where n is number of attacks
};

class Atower
{
    protected:

        prlist& m_projs;
        tdata m_tow;           

        static sf::Texture s_text;        

        //check if an enemy is in range of the tower
        //if it is, forces it to shoot
        //*VIRTUAL*
        virtual bool checkinrange(elist& elist) = 0;     

    public:        

        //constructor with all parameters
        Atower(sf::Vector2f pos, int damage, int range, float adelay, int type, float projspeed, prlist& m_projs);

        //default destructor
        virtual ~Atower() = default;

        //fire at target
        //*VIRTUAL*
        virtual void fireat(sf::Vector2f target) = 0;   
        
        //manage a tower
        //*VIRTUAL*
        virtual void manage(sf::RenderWindow& window, elist& elist, float currtime) = 0;

        //get bounding rectangle of a sprite
        sf::FloatRect getrect();
        
        //get coordinates of the tower
        sf::Vector2f getcoords();

        //get range of tower
        float getrange();  

        //returns the type number of a tower
        int gettype();   
        
        //load texture from cashe
        static void settexture(const char* tfile);    
};

using towlist = std::list <std::shared_ptr<Atower>>;