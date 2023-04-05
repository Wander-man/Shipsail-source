#include "gamemap.h"

Gamemap::Gamemap() 
    : m_dim{0,0},
    m_size(0),
    m_bases{{0,0},{0,0}}
{}

int Gamemap::setquality(cellvector walkable)
{
    for(auto i : m_towerable)   //evaluating quality of all buildable cells
    {
        int num = m_tiles.at(i).coord.y * m_dim.x + m_tiles.at(i).coord.x;

        for(auto j : walkable)
        {
            if(abs(m_tiles.at(i).coord.x - j.coord.x) <= 2 && abs(m_tiles.at(i).coord.y - j.coord.y) <= 2)
            {                
                m_tiles.at(num).cw.quality++;                
            }
        }  
    }
    
    for(auto &i : m_towerable)       //sorting indexes of buildable tiles biggest quality to smallest
    {        
        for(auto &j : m_towerable)
        {
            if(m_tiles.at(j).cw.quality < m_tiles.at(i).cw.quality)
            {
                int buf = i;
                i = j;
                j = buf;
            }
        }    
    }

    if(m_towerable.size() > 10)     //cutting number of buildable tiles, marked by quality to 10
    {
        for(ivect::iterator i = m_towerable.begin()+11; i != m_towerable.end(); ++i)
        {  
            m_tiles.at(*i).cw.quality = 0;
        }        
    }
}

int Gamemap::create_tiles(const char* createfile)
{
    cellvector walkable;

    if(m_tiles.size() != 0)     //checking for a present map
    {
        std::cout << "\nCurrent map will be deleted from memory" << std::endl;
        m_tiles.clear();
        m_dim.x = 0;
        m_dim.y = 0;
        m_size = 0;
        if(m_towerable.size() != 0) m_towerable.clear();
    }

    std::ifstream crfile;       //initial map creation file
    crfile.open(createfile);

    if(!crfile.is_open())
    {
        std::cout << "\nUnable to open file" << std::endl;
        return 1;
    }

    std::string a;
    getline(crfile, a, '\n');
    m_dim.x = atoi(a.c_str());              //reading the dimensions
    getline(crfile, a, '\n');
    m_dim.y = atoi(a.c_str());
    m_size = m_dim.x * m_dim.y;


    for(int i = 0; i < m_size; i++)         //creating the tile matrix (map)
    {        
        cell cc{(0,0,0,0,0),(0,0)};

        char x = (i) % m_dim.x;
        char y = (i - x) / m_dim.y; 

        if(x == m_dim.x -1)
        {
            getline(crfile, a, '\n');
        }
        else
        {
            getline(crfile, a, ' ');
        }
        
        cc.cw.walkable = a.at(0) - '0';
        cc.cw.buildable = a.at(1) - '0';

        if(a.size() == 3)
        {
            cc.cw.base = a.at(2) - '0';
            if(cc.cw.base == 1)
            {
                m_bases.end.x = x;
                m_bases.end.y = y;
            }
            if(cc.cw.base == 2)
            {
                m_bases.begin.x = x;
                m_bases.begin.y = y;
            }
        }
        else
        {
            cc.cw.base = 0;
        }                

        cc.coord.x = x;
        cc.coord.y = y;

        cc.cw.stepped = 0;
        cc.cw.quality = 0;        

        m_tiles.push_back(cc);

        if(cc.cw.walkable)
        {
            walkable.push_back(cc);           //writing to a cell vector
            m_pthmap.push_back(1);
        }
        else
        {
            m_pthmap.push_back(0);
        }        
        
        if(cc.cw.buildable)
        {
            m_towerable.push_back(i);          //writing indexes of buildable tiles  
        }
    }

    crfile.close();

    walkable.shrink_to_fit();
    m_towerable.shrink_to_fit();
    m_tiles.shrink_to_fit();

    setquality(walkable);
}

int Gamemap::save_tiles(const char* savefile)
{
    std::ofstream mfile;
    mfile.open(savefile, std::ios::binary | std::ios::trunc);

    if(!mfile.is_open())
    {
        std::cout << "\nUnable to open file" << std::endl;
        return 1;
    }

    mfile.write(reinterpret_cast <char*> (&m_dim.x), sizeof(m_dim.x));
    mfile.write(reinterpret_cast <char*> (&m_dim.y), sizeof(m_dim.y));

    for(cellvector::iterator i = m_tiles.begin(); i != m_tiles.end(); ++i)
    {
        mfile.write(reinterpret_cast <char*> (&*i), sizeof(cell));
    }

    mfile.close();
    return 0;
}

int Gamemap::load_tiles(const char* loadfile)
{
    cellvector walkable;
    cell cc;
    std::ifstream wfile;
    wfile.open(loadfile, std::ios::binary);    

    if(!wfile.is_open())
    {
        std::cout << "\nUnable to open file" << std::endl;
        return 1;
    }

    wfile.read(reinterpret_cast <char*> (&m_dim.x), sizeof(m_dim.x));
    wfile.read(reinterpret_cast <char*> (&m_dim.y), sizeof(m_dim.y));
    m_size = m_dim.x * m_dim.y;
    
    if(m_tiles.size()) m_tiles.clear();
    if(m_pthmap.size()) m_pthmap.clear();
    if(m_towerable.size()) m_towerable.clear();

    for(int i = 0; i < m_dim.x * m_dim.y; i++)
    {
        wfile.read(reinterpret_cast <char*> (&cc), sizeof(cell));
        m_tiles.push_back(cc);

        if(cc.cw.base == 1)
        {
            m_bases.end.x = i % m_dim.x;
            m_bases.end.y = (i - m_bases.begin.x) / m_dim.y;
        }
        if(cc.cw.base == 2)
        {
            m_bases.begin.x = i % m_dim.x;
            m_bases.begin.y = (i - m_bases.end.x) / m_dim.y;
        }
        if(!cc.cw.walkable && cc.cw.buildable)
        {         
            m_towerable.push_back(i);
        }
        if(cc.cw.walkable)
        {
            walkable.push_back(cc);
            m_pthmap.push_back(1);
        }
        else
        {
            m_pthmap.push_back(0);
        }        
    }
    wfile.close();

    setquality(walkable);

    return 0;
}

int Gamemap::t(const char* savefile)
{
    std::ofstream mfile;
    mfile.open(savefile, std::ios::trunc);

    if(!mfile.is_open())
    {
        std::cout << "\nUnable to open file" << std::endl;
        return 1;
    }

    mfile << m_dim.x << '\n' << m_dim.y << '\n';

    for(cellvector::iterator i = m_tiles.begin(); i != m_tiles.end(); ++i)
    {
        mfile << (i->cw.walkable? "1":"0") << (i->cw.buildable? "1":"0") << static_cast <unsigned int> (i->cw.base) << static_cast <unsigned int> (i->cw.quality) << "(" << static_cast <unsigned int> (i->coord.x) << static_cast <unsigned int> (i->coord.y) << ")";
        if(i->coord.x == m_dim.x - 1)
        {
            mfile << '\n';
        }
        else
        {
            mfile << ' ';
        }
    }

    mfile.close();
    return 0;
}

const cellvector& Gamemap::getmap()
{
    return m_map;
}

const ivect& Gamemap::gettow()
{
    return m_tow;
}

const bvect& Gamemap::getbmap()
{
    const bvect& a = m_pthmap;
    return a;
}

msize Gamemap::getdim()
{
    return m_dim;
}

begend Gamemap::getbases()
{
    return m_bases;
}