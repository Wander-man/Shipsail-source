#pragma once 

#include "obj_aenemy.h"

class Armship : public Aenemy
{
    private:

        static sf::Texture s_text;

        //set the part of the picture displayed
        void setsprite() override final;

        //move ship
        void nextmove(float timepassed) override final;

        //set frame
        void anim() override final;

        //check projectile collision
        bool checkcoll(prlist& prlist) override final;  

    public:

        //default constructor
        Armship(const crdvect& path, float speed, int hp, float htime, int type);

        //default destructor
        ~Armship() = default;

        //manage ship
        void manage(sf::RenderWindow &window, prlist& prlist, float currtime) override final;

        //get the speed of enemy (x/s)
        float getspeed();        
        
        //set enemy texture
        static void settexture(const char* tfile);

        //create an enemy and load all data to containers
        static void create(const crdvect& path, float speed, int hp, float htime, elist& elist);
};