#pragma once

#include <utility>
#include <set>
#include <stack>
#include "gamemap.h"


using Pair = std::pair <char, char>;
using pPair = std::pair <int, Pair>; //pair for openlist

struct acell
{
    xy parcrd;
    int g;
    int h;
    int f;
};

using acvect = std::vector <acell>;         //celldata vector
using crdvect = std::vector <xy>;

class Astar
{
    private:

        begend m_begend;
        msize m_size;
        const bvect& m_grid;
        acvect m_cd;
        crdvect m_path;
        
        //check if a cell is on the map
        bool isvalid(xy dot);

        //check if a cell is blocked
        bool isntblocked(xy dot);

        //check if the cell is destination
        bool isdest(xy dot);

        //calculate h
        int hval(xy dot);

        //coordinates of child points (1 - north, 2 - east, 3 - south, 4 - west)
        xy cit(xy par, int num);

    public:

        //constructor with all the data
        Astar(begend begend, msize size, const bvect& grid);

        //default destructor
        ~Astar() = default;

        //print the existing path
        void printpath();

        //Astar algorithm
        void astarfind();

        //get shortest path in coordinates
        const crdvect& getpath();
};