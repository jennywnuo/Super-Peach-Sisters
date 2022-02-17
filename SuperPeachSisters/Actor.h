#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageId, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isAlive);
    virtual ~Actor();
    virtual void doSomething() = 0;
    bool isAlive() const;
    void kill();
    StudentWorld* getWorld() const;
    virtual int getScore() const;
    bool isDamageable();
    
private:
    bool m_alive;
    StudentWorld* m_world;
//    int m_health;
};

class Peach: public Actor
{
public:
    Peach(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* sWorld);
    virtual void doSomething();
    virtual ~Peach();
};

class Block: public Actor
{
public:
    Block(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* sWorld);
    virtual void doSomething();
    virtual ~Block();
private:
    bool hasGoodie;
};


#endif // ACTOR_H_
