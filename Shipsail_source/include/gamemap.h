#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>

#pragma pack(push, 1)
struct cellwal
{
    bool walkable : 1;
    bool buildable : 1;
    bool stepped : 1;
    unsigned int quality : 5;    
    char base; //0-not a base 1-home 2-enemy
};
    
struct xy
{
    char x;
    char y;
};

struct cell
{
    cellwal cw;    
    xy coord;
};

struct msize
{
    int x;
    int y;
};

struct begend
{
    xy begin;
    xy end;
};
#pragma pack(pop)

using cellvector = std::vector <cell>;
using ivect = std::vector <int>;
using bvect = std::vector <bool>;

class Gamemap
{
    private:

        begend m_bases;

        msize m_dim;
        int m_size;
 
        cellvector m_tiles{}; 
        const cellvector& m_map = m_tiles;  

        ivect m_towerable{}; 
        const ivect& m_tow = m_towerable;

        bvect m_pthmap{};        

        //calculates the quality of buildable cells
        int setquality(cellvector walkable);   

    public:

        //default constructor
        Gamemap();

        //default destructor
        ~Gamemap() = default;

        //create a map in memory
        int create_tiles(const char* createfile);

        //save map to a file "filename"
        int save_tiles(const char* mapfile);

        //map check, prints current map to a text file
        int t(const char* mapfile);

        //load map from a file
        int load_tiles(const char* mapfile);

        //get map
        const cellvector& getmap();

        //get buildable tiles indexes
        const ivect& gettow();
       
        //get a boolean representation of the map (for pathfinding)
        const bvect& getbmap();

        //get dimesions of the map
        msize getdim();

        //get coordinates of bases
        begend getbases();
};