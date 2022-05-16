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
            FlowerBlock
            MushroomBlock
            StarBlock
        Goodie
            Flowers
            Mushrooms
            Stars
        PeachFireballs
        PiranhaFireballs
        Shells
        Goal
            Mario
        Goombas
        Koopas
        Piranhas
 */

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isAlive, bool isSolid, bool isDamageable);
    virtual ~Actor(){}
    virtual void doSomething() = 0;
    virtual void getDamaged(){}
    virtual void bonk(){}
    
    bool isAlive() const{return m_alive;}
    bool isSolid() const{return m_solid;}
    bool isDamageable() const{return m_damageable;}
    void kill(){m_alive = false;}
    
    
    StudentWorld* getWorld() const{return m_world;}
    virtual int getScore() const{return 0;}
    
private:
    bool m_alive;
    bool m_solid;
    bool m_damageable;
    StudentWorld* m_world;
};

// PEACH 🍑
class Peach: public Actor
{
public:
    Peach(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    // powers and health
    void setHealth(int h){m_health = h;}
    int getHealth(){return m_health;}
    void setShoot(bool s){m_shootpower = s;}
    void setStar(bool s){m_starpower = 150;}
    void setTemp(bool t){m_temp = 8;}
    void setJumps(bool j){m_jumps = j;}
    // checking
    bool hasStar(){return m_starpower > 0;}
    bool hasJump(){return m_jumps;}
    bool hasFire(){return m_shootpower;}
        virtual void getDamaged();
    // level 
    void finishLevel(){m_finishLevel = true;}
    void finishGame(){m_finishGame = true;}
    bool completed(){return m_finishLevel;}
    bool completedGame(){return m_finishGame;}
    
private:
    int m_distance;
    bool m_shootpower;
    bool m_jumps;
    int m_health;
    int m_recharge;
    int m_starpower;
    int m_temp;
    bool m_finishLevel;
    bool m_finishGame;
};

// BLOCK 🧱
class Block: public Actor
{
public:
    Block(int imageID, int startX, int startY, StudentWorld* sWorld, bool isSolid, bool hasGoodie);
    virtual void doSomething(){}
    virtual void bonk();
    bool hasGoodie(){return m_goodie;}
    void setGoodie(bool g){m_goodie = g;}
    virtual void bringGoodie(){}

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
};

// MARIO 👨🏻
class Mario: public Goal
{
public:
    Mario(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
};

// GOODIES 😛
class Goodie: public Actor
{
public:
    Goodie(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isSolid);
    virtual void doSomething();
    virtual void changes() = 0;
};

// FLOWER 🌼
class Flower: public Goodie
{
public:
    Flower(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void changes();
};

// MUSHROOM 🍄
class Mushroom: public Goodie
{
public:
    Mushroom(int imageID, int startX, int startY,  StudentWorld* sWorld);
    virtual void changes();
};

// STAR ⭐️
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
};

// PEACH FIREBALLS 🔥
class PeachFireball: public Actor
{
public:
    PeachFireball(int imageID, int startX, int startY, int dir, StudentWorld* sWorld);
    virtual void doSomething(); 
};

// SHELLS 🥥
class Shell: public Actor
{
public:
    Shell(int imageID, int startX, int startY, int dir, StudentWorld* sWorld);
    virtual void doSomething();
};

// GOOMBA 💩
class Goomba: public Actor
{
public:
    Goomba(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
    virtual void getDamaged();
};

// KOOPA 🐢
class Koopa: public Actor
{
public:
    Koopa(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
    virtual void getDamaged();
    virtual ~Koopa();
};

// PIRANHA 🌷
class Piranha: public Actor
{
public:
    Piranha(int imageID, int startX, int startY, StudentWorld* sWorld);
    virtual void doSomething();
    virtual void bonk();
    virtual void getDamaged();
private:
    int m_delay; 
};


#endif // ACTOR_H_
