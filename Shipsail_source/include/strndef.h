#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <cstdlib>

//tilesize
#define TSIZE 100
//projectile size
#define PRSIZE 20
//fitting coordinates to tilesize
#define FCADJ(x) *x
#define SCADJ(x) *x + x

//square
#define SQR(x) x *x

//struct for coords of any type
template <typename T>
struct xyt
{
    T x;
    T y;
};

//check if a number is in range
template <typename T>
bool inrange(T low, T high, T x);

//normalize a vector
sf::Vector2f norm(sf::Vector2f normed);

//randow number generetion
uint32_t xorshift();

//get coordinates of a 1-dim 
//array element num if it was a matrix
sf::Vector2f numtocoords (int num, int sizex, int sizey, float adj);