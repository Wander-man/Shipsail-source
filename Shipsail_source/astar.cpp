#include "astar.h"

#define alot 10000

Astar::Astar(begend begend, msize size, const bvect& grid) 
    : m_begend(begend),
    m_size(size),
    m_grid(grid),
    m_cd(m_size.x * m_size.y, {{static_cast <char> (250), static_cast <char> (250)},alot,alot,alot})
{}

bool Astar::isvalid(xy dot)
{
    return dot.x >= 0 && dot.x < m_size.x && dot.y >= 0 && dot.y < m_size.y;
}

bool Astar::isntblocked(xy dot)
{
    if(m_grid.at(dot.x + dot.y * m_size.x))
    {
        return true;
    }
    else
    {
        return false;
    }    
}

bool Astar::isdest(xy dot)
{
    if(dot.x == m_begend.end.x && dot.y == m_begend.end.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Astar::hval(xy dot)
{
    return abs(dot.x - m_begend.end.x) + abs(dot.y - m_begend.end.y);
}

xy Astar::cit(xy par, int num)
{
    xy a{0,0};

    switch(num)
    {
        case 1:
            a.x = par.x;
            a.y = par.y + 1;
        break;

        case 2:
            a.x = par.x + 1;
            a.y = par.y;
        break;

        case 3:
            a.x = par.x;
            a.y = par.y - 1;
        break;

        case 4:
            a.x = par.x - 1;
            a.y = par.y;
        break;

        default:
            std::cout << "\nWrong parameters" << std::endl;
        break;
    }
    return a;
}

void Astar::astarfind()
{
    if(!isvalid(m_begend.begin))
    {
        std::cout << "\nsource is invalid" << std::endl;
        return;
    }
    if(!isvalid(m_begend.end))
    {
        std::cout << "\ndestination is invalid" << std::endl;
        return;
    }
    if(!isntblocked(m_begend.begin) || !isntblocked(m_begend.begin))
    {
        std::cout << "\neither source or destination is blocked" << std::endl;
        return;
    }
    if(isdest(m_begend.begin))
    {
        std::cout << "\ndestination is already reached" << std::endl;
        return;
    }

    bvect closed(m_size.x * m_size.y, false);

    //m_cd already initialized
    int num = m_begend.begin.x + m_begend.begin.y * m_size.x;    
    m_cd.at(num).parcrd = m_begend.begin; 
    m_cd.at(num).g = 0; 
    m_cd.at(num).h = 0; 
    m_cd.at(num).f = 0; 

    std::set <pPair> open;
    open.insert(std::make_pair(0, std::make_pair(m_begend.begin.x, m_begend.begin.y))); //adding beginning to the open list

    bool found(false);

    while (!open.empty()) 
    {        
        xy coord;
        pPair p = *open.begin();
        open.erase(open.begin());       //erasing beginning from the open list

        coord.x = p.second.first;
        coord.y = p.second.second;
        int nump = coord.x + coord.y * m_size.x;

        closed.at(nump) = true;     //adding beginning to the closed list

        int gn(0), hn(0), fn(0);

        for(int i = 1; i <= 4; i++)
        {
            xy cell = cit(coord, i);
            int numc = cell.x + cell.y * m_size.x;

            if(isvalid(cell) == true)
            {
                if (isdest(cell) == true) 
                {                    
                    m_cd.at(numc).parcrd = coord;
                    //std::cout << "\ndestination found!" << std::endl;
                    printpath();
                    found = true;
                    return;
                }
                else
                {
                    if(closed.at(numc) == false && isntblocked(cell))
                    {
                        gn = m_cd.at(nump).g + 1;
                        hn = hval(cell);
                        fn = gn + hn;

                        if(m_cd.at(numc).f == alot || m_cd.at(numc).f > fn)
                        {
                            open.insert(std::make_pair(fn, std::make_pair(cell.x, cell.y)));

                            m_cd.at(numc).parcrd = coord; 
                            m_cd.at(numc).g = gn; 
                            m_cd.at(numc).h = hn; 
                            m_cd.at(numc).f = fn; 
                        }
                    }
                }                
            }
        }//forloop
    }//whileloop

    if(!found)
    {
        std::cout << "\nunable to find a path" << std::endl;
    }

    return;    
}

void Astar::printpath()
{
    m_path.clear();
    xy coord;
    //std::cout << "\nThe path is:" << std::endl;

    coord = m_begend.end;
    int num = coord.x + coord.y * m_size.x;

    std::stack <xy> path;

    while(!(m_cd.at(num).parcrd.x == coord.x && m_cd.at(num).parcrd.y == coord.y))
    {
        path.push(coord);
        coord = m_cd.at(num).parcrd;        
        num = coord.x + coord.y * m_size.x;
    }
    path.push(coord);
    //std::cout << path.size();

    while(!path.empty())
    {
        coord = path.top();
        m_path.push_back(coord);
        path.pop();
        //std::cout << "-> (" << static_cast <unsigned int> (coord.x) << "," << static_cast <unsigned int> (coord.y) << ") ";
    }

    return;
}

const crdvect& Astar::getpath()
{
    const crdvect& a = m_path;
    return a;
}

