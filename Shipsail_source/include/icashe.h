#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <forward_list>
#include <string.h>

#define MAPTILES_PNG "img/Maptiles.png"
#define SSHIP_PNG "img/sship.png"
#define ARMSHIP_PNG "img/armship.png"
#define PROJECTILE_PNG "img/proj.png"
#define TOWERS_PNG "img/towers.png"

using fns = std::forward_list <const char*>;
using icashemap = std::unordered_map <std::string, const sf::Image>;

extern char sProgramRoot[255];

class Icashe
{
    private:

        //the map, that stores cashed images
        icashemap m_cashemap;

    public:

        //default constructor
        Icashe() = default;

        //constructor
        Icashe(fns filenames);

        //default destructor
        ~Icashe() = default;

        //cashe init
        void init(fns filenames);

        //get an image from cashe
        const sf::Image& getimg(const char*);
};

extern Icashe cashe;