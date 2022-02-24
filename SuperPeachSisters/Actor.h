#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class StudentWorld;


/*
GraphObject
    Actor
        Peach
        Block
            Pipes
            FlowerBlock
            MushroomBlock
            StarBlock
        Goodie
            Flowers
            Mushrooms
            Stars
        Goal

*/

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isAlive, bool isSolid);
    virtual ~Actor();
    virtual void doSomething() = 0;
    virtual void bonk(){}
    
    bool isAlive() const;
    bool isSolid() const;
    void kill();
    
    
    StudentWorld* getWorld() const;
    virtual int getScore() const;
    bool isDamageable();
    
private:
    bool m_alive;
    bool m_solid;
    StudentWorld* m_world;
    int m_health;
};

// PEACH 🍑
class Peach: public Actor
{
public:
    Peach(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
    // powers and health
    void setHealth(int h);
    void setShoot(bool s);
    void setStar(bool s);
    void setJumps(bool j);
    // checking
    bool hasStar();
    
private:
    int m_distance;
    bool m_starpower;
    bool m_shootpower;
    bool m_jumps;
    int m_health;
    int m_recharge;
    
};

// BLOCK 🧱
class Block: public Actor
{
public:
    Block(int imageID, int startX, int startY, StudentWorld* sWorld, bool isSolid, bool hasGoodie);
    virtual void doSomething();
    virtual void bonk();
    bool hasGoodie();
    void setGoodie(bool g);
    virtual void bringGoodie();

private:
    bool m_goodie;
};

// STAR BLOCK ⭐️🧱
class StarBlock: public Block
{
public:
    StarBlock(int imageID, int startX, int startY, StudentWorld* sWorld, bool hasGoodie);
    void bringGoodie();
};

// MUSHROOM BLOCK 🍄🧱
class MushroomBlock: public Block
{
public:
    MushroomBlock(int imageID, int startX, int startY, StudentWorld* sWorld, bool hasGoodie);
    void bringGoodie();
    
};

// FLOWER BLOCK 🌼🧱
class FlowerBlock: public Block
{
public:
    FlowerBlock(int imageID, int startX, int startY,  StudentWorld* sWorld, bool hasGoodie);
    void bringGoodie();
};

// GOAL 🚩
class Goal: public Actor
{
public:
    Goal(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
};


// GOODIES 😛
class Goodie: public Actor
{
public:
    Goodie(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isSolid);
    virtual void doSomething();
    virtual void changes() = 0;
};

// FLOWERS 🌼
class Flower: public Goodie
{
public:
    Flower(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void changes();
};

// MUSHROOMS 🍄
class Mushroom: public Goodie
{
public:
    Mushroom(int imageID, int startX, int startY,  StudentWorld* sWorld);
    virtual void changes();
};

// STARS ⭐️
class Star: public Goodie
{
public:
    Star(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void changes();
};

// PIRANHA FIREBALLS ☄️
class PiranhaFireball: public Actor
{
public:
    PiranhaFireball(int imageID, int startX, int startY, int dir, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
};

// PEACH FIREBALLS 🔥
class PeachFireball: public Actor
{
public:
    PeachFireball(int imageID, int startX, int startY, int dir, StudentWorld* sWorld);
    virtual void doSomething(); 
    virtual void bonk();
};

// SHELLS 🥥
class Shell: public Actor
{
public:
    Shell(int imageID, int startX, int startY, int dir, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
};

// GOOMBA 💩
class Goomba: public Actor
{
public:
    Goomba(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
};

// KOOPA 🐢
class Koopa: public Actor
{
public:
    Koopa(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
};

// PIRANHA 🌷
class Piranha: public Actor
{
public:
    Piranha(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
};


#endif // ACTOR_H_
