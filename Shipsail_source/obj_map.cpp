#include "obj_map.h"

extern Icashe cashe;

//--------------------map---------------------------------

Gamemaptext::Gamemaptext(const cellvector &gamemap, const crdvect &path, const ivect &towi, msize dim) 
    : m_map{map(gamemap)}, 
    m_path(path), 
    m_tow(towi), 
    m_dim(dim)
{}

bool Gamemaptext::load(const char *mapimg, sf::Vector2u tilesize)
{
    if (!m_maptiles.loadFromImage(cashe.getimg(mapimg)))
    {
        return false;
    }        

    m_vert.setPrimitiveType(sf::Quads);
    m_vert.resize(m_dim.x * m_dim.y * 4);
    
    for (int i = 0; i < m_dim.x; ++i)
    {
        for (int j = 0; j < m_dim.y; ++j)
        {
            msize tc{0, 0};
            cell cc = m_map.at(i + j * m_dim.x);

            while (1)
            {
                if (cc.cw.walkable && cc.cw.base == 1)
                {
                    tc.x = 1;
                    break;
                }
                if (cc.cw.walkable && cc.cw.base == 2)
                {
                    tc.x = 0;
                    break;
                }
                if (cc.cw.walkable)
                {
                    tc.x = 2;
                    break;
                }
                if (!cc.cw.walkable && !cc.cw.buildable)
                {
                    tc.x = 3;
                    break;
                }
                if (!cc.cw.walkable && cc.cw.buildable)
                {
                    for (int k = 0; k < 10; k++)
                    {
                        int c = 10 - (k + 1);
                        if (i + j * m_dim.x == m_tow.at(k))
                        {
                            tc.x = 5 + c;
                        }
                    }
                    if (tc.x == 0)
                    {
                        tc.x = 4;
                    }
                    break;
                }
            }

            sf::Vertex *quad = &m_vert[(i + j * m_dim.x) * 4];

            quad[0].position = sf::Vector2f(i * tilesize.x, j * tilesize.y);
            quad[1].position = sf::Vector2f((i + 1) * tilesize.x, j * tilesize.y);
            quad[2].position = sf::Vector2f((i + 1) * tilesize.x, (j + 1) * tilesize.y);
            quad[3].position = sf::Vector2f(i * tilesize.x, (j + 1) * tilesize.y);

            quad[0].texCoords = sf::Vector2f(tc.x * tilesize.x, tc.y * tilesize.y);
            quad[1].texCoords = sf::Vector2f((tc.x + 1) * tilesize.x, tc.y * tilesize.y);
            quad[2].texCoords = sf::Vector2f((tc.x + 1) * tilesize.x, (tc.y + 1) * tilesize.y);
            quad[3].texCoords = sf::Vector2f(tc.x * tilesize.x, (tc.y + 1) * tilesize.y);
        }
    }
    return true;
}

//--------------------(map)--------------------------------
