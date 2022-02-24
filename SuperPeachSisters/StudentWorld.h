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
    void damageActor(int x, int y);
    // collisions
    bool overlapped(int x, int y, bool checkBonk);
    Peach* getPeach() const;
    bool overlapPeach(int x, int y);
    bool overlapEnemy(int x, int y);
    
    // peach powers and health
    void changePeachHealth(int h);
    void peachShoot(bool s);
    void peachJump(bool j);
    void peachStar(bool s);
    // checking
    bool peachHasStar();
    int peachHeight();
    int peachWidth(); 
    

private:
    Peach* m_peach;
    PeachFireball* m_fireball;
    std::vector<Actor*> m_actors;
    int m_numActors; 
};

#endif // STUDENTWORLD_H_
