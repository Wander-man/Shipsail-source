#pragma once

#include "w_awindow.h"
#include "w_logwindow.h"
#include "g_stats.h"

enum wmode
{
    mainm,
    levelsm,
    statsm
};

class Menuwindow : public Awindow
{
    private:

        std::string m_curusr;
        Stats m_stats;

    public:

        //constructor
        Menuwindow(sf::VideoMode vmode, const char* name, sf::Font& font, sf::Vector2i pos, std::string  user);

        //default destructor
        ~Menuwindow() = default;

        //get current user
        void getuser(std::string user);

        //run window
        std::string launch() override final;

        //returns a reference to the stats class
        Stats& getstats();
};