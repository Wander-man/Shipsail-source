#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "gamemap.h"
#include "astar.h"
#include "icashe.h"
#include "strndef.h"

class Gamemaptext : public sf::Drawable, public sf::Transformable
{
    private:

        msize m_dim;
        const crdvect& m_path;
        cellvector& m_map;
        const ivect& m_tow;

        sf::VertexArray m_vert;
        sf::Texture m_maptiles;

        cellvector& map(const cellvector &gamemap)
        {
            return const_cast <cellvector&> (gamemap);
        };

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();

            states.texture = &m_maptiles;

            target.draw(m_vert, states);
        };

    public:

        //deafult constructor
        Gamemaptext();

        //constructor with a map present
        Gamemaptext(const cellvector &gamemap, const crdvect &path, const ivect &towi, msize dim);

        //default destructor
        ~Gamemaptext() = default;

        //loading map image to sprites
        bool load(const char *mapimg, sf::Vector2u tilesize);
};