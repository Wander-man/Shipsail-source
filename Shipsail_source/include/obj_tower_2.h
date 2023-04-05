#include "obj_atower.h"

class Tower2 : public Atower
{
    private:

        //check if an enemy is in range of the tower
        //if it is, forces it to shoot
        bool checkinrange(elist& elist) override final; 
        
    public:

        //class constructor
        Tower2(sf::Vector2f pos, int damage, int range, float as, int type, float projspeed, prlist& m_projs);

        ~Tower2() = default;

        //fire at the enemy
        void fireat(sf::Vector2f target) override final;

        //manage a tower
        void manage(sf::RenderWindow& window, elist& elist, float currtime) override final;

        //get bullet id for 
        //controleed collision
        int getid();

        //create a tower and load all data to containers
        static void create(sf::Vector2f pos, int damage, int range, float adelay, float projspeed, prlist& m_projs, towlist& towlist);
};