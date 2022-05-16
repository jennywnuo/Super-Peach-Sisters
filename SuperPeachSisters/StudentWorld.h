#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void addActor(Actor* a);
    bool damageActor(int x, int y);
    void damagePeach();
    // collisions
    bool overlapped(int x, int y, bool checkBonk);
    Peach* getPeach() const;
    bool overlapPeach(int x, int y);
    bool overlapEnemy(int x, int y, Actor* a);
    
    // peach powers and health
    void changePeachHealth(int h){m_peach->setHealth(h);}
    void peachShoot(bool s){m_peach->setShoot(s);}
    void peachJump(bool j){m_peach->setJumps(j);}
    void peachStar(bool s){m_peach->setStar(s);}
    void peachTemp(bool t){m_peach->setTemp(t);}
    void peachDamage(){m_peach->getDamaged();}
    void finishLevel(){m_peach->finishLevel();}
    void finishGame(){m_peach->finishGame();}
    
    // checking
    bool peachHasStar(){return m_peach->hasStar();}
    bool peachHasJump(){return m_peach->hasJump();}
    bool peachHasFire(){return m_peach->hasFire();}
    int peachHeight(){return m_peach->getY();}
    int peachWidth(){return m_peach->getX();}
    int peachHealth(){return m_peach->getHealth();}
    

private:
    Peach* m_peach;
    PeachFireball* m_fireball;
    std::vector<Actor*> m_actors;
    int m_numActors;
};

#endif // STUDENTWORLD_H_
