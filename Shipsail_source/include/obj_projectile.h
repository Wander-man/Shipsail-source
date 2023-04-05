#pragma once

#include <list>
#include "strndef.h"
#include "icashe.h"

//projectile data structure
struct proj
{
    //projectile sprite
    sf::Sprite spr;

    //values to treat the projectile by
    sf::Vector2f dir;
    float pathlen_sqr;
    float travdist;

    //properties
    float speed;
    int damage;

    int animc;
    float animtime;
    float holdtime;  
    float multiplier; 

    //bullet id
    int id; 

    //conditions
    bool pierce;
    bool isdone;
    bool hit;
};

class Projectile
{
    private:

        static sf::Texture s_text;
        static float s_multiplier;

        proj m_proj;
        
        //set frame
        void anim();

        //set part of texture according to m_curranim
        void setsprite();      

        //move proj
        void nextmove(float timepassed);

    public:

        //constructor
        //speed is how much is traveled in 1s
        Projectile(sf::Vector2f origin, sf::Vector2f dest, int damage, float speed, bool pierce, float htime); 

        //default destructor
        ~Projectile() = default;

        //get coordinates
        sf::Vector2f getcoord();

        //tells whether a projectile 
        //reached destination
        bool finished();

        //return the damage
        int damage();

        //tells whether a projectil is piercing
        bool piercing();

        //sets projectile to hit mode
        void sethit();

        //get bullet id
        int getid();

        //manage the projectile
        void manage(sf::RenderWindow& window, float currtime);

        //set projectile texture
        static void settexture(const char* filename);
};

using prlist = std::list <Projectile>;