#pragma once

#include "strndef.h"

#include "astar.h"
#include "obj_map.h"
#include "gamemap.h"
#include "icashe.h"

#include "ui_button.h"
#include "ui_tlabel.h"
#include "ui_textbar.h"
#include "ui_counter.h"

#include "w_logwindow.h"
#include "w_menuwindow.h"

#include "obj_enemy_sship.h"
#include "obj_enemy_armship.h"
#include "obj_projectile.h"
#include "obj_tower_1.h"
#include "obj_tower_2.h"
#include "obj_tower_3.h"

#include "g_stats.h"

using built = std::unordered_map <int, bool>;

class Game : public Awindow
{
    private:

        //precomputed data
        Gamemaptext& m_maptext;
        crdvect& m_path;
        ivect& m_tow;
        Stats& m_stats;

        //runtime data
        built m_built;
        Counter m_money;
        Counter m_basehp;
        

        //create a tower of a type no type
        bool tcreate(int type, sf::Event cond, prlist& proj, towlist& tows, sf::RenderWindow& window);

    public:

        //constructor
        Game(sf::VideoMode vmode, const char* name, sf::Font& font, sf::Vector2i pos, ivect& tow, crdvect& path, Gamemaptext& maptext, Stats& stats, int money, int basehp);

        //default destructor
        virtual ~Game() = default;

        //launch a window
        std::string launch() override final;

};