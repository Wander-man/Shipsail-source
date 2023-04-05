#include "strndef.h"

template <typename T>
bool inrange(T low, T high, T x)
{
    return ((x - low) * (x - high) <= 0);
}

template bool inrange <float> (float low, float high, float x);

sf::Vector2f norm(sf::Vector2f normed)
{
    float module = sqrt(SQR(normed.x) + SQR(normed.y));
    return sf::Vector2f(normed.x, normed.y) / module;
}

uint32_t xorshift()
{
    //seeds
    static uint32_t x(123456789);
    static uint32_t y(362436069);
    static uint32_t z(521288629);
    static uint32_t w(88675123);
    uint32_t t;
    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

sf::Vector2f numtocoords (int num, int sizex, int sizey, float adj)
{
    return sf::Vector2f( ((num % sizex) FCADJ(TSIZE)) + adj, ((num - num % sizex) FCADJ(TSIZE) / sizey) + adj );
}