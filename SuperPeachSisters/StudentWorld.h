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
    bool overlapped(int x, int y, bool checkBonk);
    Peach* getPeach() const;
    bool overlapPeach(int x, int y);
    void changePeachHealth(int h);
    void peachShoot(bool s);
    void peachJump(bool j);
    void peachStar(bool s); 
    

private:
    Peach* m_peach;
    std::vector<Actor*> m_actors;
    int m_numActors; 
};

#endif // STUDENTWORLD_H_
