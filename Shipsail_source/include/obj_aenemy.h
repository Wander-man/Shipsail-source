#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "astar.h"
#include "obj_projectile.h"

struct progress
{
    int abs;
    float loc;
};

struct mow_object
{
    //enemy sprite
    sf::Sprite sprite;
    sf::RectangleShape healthbar;

    //properties
    int type;

    sf::Vector2f cdir;
    xyt<float> coord;
    progress prg;    
    
    float holdtime;    
    float speed;
    int hp;
    int maxhp;

    xyt <int> animc;
    float animtime;   
    float multiplier;
    
    //conditions
    bool isdone;
    bool killed;
    bool todelete;
    bool paid;
};

class Aenemy
{
    protected:

        std::vector <int> m_bulletids;

        const crdvect& m_path;

        mow_object m_obj;

        //set the current animation frame
        //*VIRTUAL*
        virtual void setsprite() = 0;

        //get movement direction
        //
        //on current progress
        void getdir();      
        //on random progress
        void getdir(progress& prg);

        //manage the healthbar
        void healthbar();

        //move on path coord
        //*VIRTUAL*
        virtual void nextmove(float timepassed) = 0;

        //set frame
        //*VIRTUAL*
        virtual void anim() = 0;    

        //check for a collision with a projectile
        //*VIRTUAL*
        virtual bool checkcoll(prlist& prlist) = 0;  

        //get and set bullet ids 
        //for single collision
        bool checkid(int id);
        void setid(int id);
        
    public:

        //constructor for an enemy with a path
        Aenemy(const crdvect& path, float speed, int hp, float htime, int type);

        //default destructor
        //*VIRTUAL*
        virtual~Aenemy() = default;

        //object management function
        //*VIRTUAL*
        virtual void manage(sf::RenderWindow &window, prlist& prlist, float currtime) = 0;

        //get coords
        sf::Vector2f getcoords();

        //returns coordinates
        //after moving for some time
        sf::Vector2f getpredcoords(float delay);

        //get enemy type
        int gettype();

        //check if it is finished
        bool isfinished();

        //check if it is killed
        bool iskilled();

        //check if reached base
        bool isdone();

        //set paid
        void paid();

        //check if paid
        bool ispaid();
};

using eptr = std::shared_ptr <Aenemy>;
using elist = std::list <eptr>;