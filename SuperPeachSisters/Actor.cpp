#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
#include <iostream>
using namespace std;

// ACTOR 🎭

Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isAlive, bool isSolid)
: GraphObject(imageID, startX, startY, startDirection, size, depth)
{
    m_alive = isAlive;
    m_world = sWorld;
    m_solid = isSolid;
}

Actor::~Actor()
{
}

bool Actor::isAlive() const
{
    return m_alive;
}

bool Actor::isSolid() const
{
    return m_solid;
}

void Actor::kill()
{
    m_alive = false;
}

StudentWorld* Actor::getWorld() const
{
    return m_world;
}

int Actor::getScore() const
{
    return 0;
}

void Actor::bonk()
{
}

// PEACH 🍑
Peach::Peach(int imageId, int startX, int startY, StudentWorld* sWorld) : Actor(imageId, startX, startY, 0, 1, 0, sWorld, true, false)
{
    m_distance = 0;
    m_shootpower = false;
    m_starpower = false;
    m_jumps = false;
    m_recharge = 0;
}


void Peach::doSomething()
{
    if (!isAlive())
        return;
    
    int currX = getX();
    int currY = getY();
    
    if(m_distance > 0)
    {
        if (!getWorld()->overlapped(getX(), getY() + 4, true))
        {
            moveTo(getX(), getY() + 4);
            cout << m_distance << endl;
            m_distance--;
        }
        else
        {
            m_distance = 0;
        }
    }
    else if (!getWorld()->overlapped(currX, currY-1, true) && !getWorld()->overlapped(currX, currY-2, true) && !getWorld()->overlapped(currX, currY-3, true) && !getWorld()->overlapped(currX, currY-4, true))
        moveTo(currX, currY - 4);
    

    if (m_recharge > 0)
        m_recharge--;
    
    int ch;
    if (getWorld()->getKey(ch))
    {
        if (ch == KEY_PRESS_LEFT && !getWorld()->overlapped(getX() - 4, getY(), true))
        {
            setDirection(180);
            if (currX > SPRITE_WIDTH)
                this->moveTo(currX-4, currY);
        }
        
        if (ch == KEY_PRESS_RIGHT && !getWorld()->overlapped(getX() + 4, getY(), true))
        {
            setDirection(0);
            if (currX < VIEW_WIDTH - SPRITE_WIDTH * 2)
                this->moveTo(currX+4, currY);
        }
        
        if (ch == KEY_PRESS_UP)
        {
            if(getWorld()->overlapped(currX, currY - 2, false))
            {
                getWorld()->playSound(SOUND_PLAYER_JUMP);
                if (!m_jumps)
                    m_distance = 8;
                else
                    m_distance = 12;
            }
        }

        if( ch == KEY_PRESS_SPACE)
        {
            if (m_shootpower && m_recharge <= 0)
            {
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                m_recharge = 8;
                if (getDirection() == 0)
                    getWorld()->addActor(new PeachFireball(IID_PEACH_FIRE, getX() + 4, getY(), 0, getWorld()));
                if (getDirection() == 180)
                    getWorld()->addActor(new PeachFireball(IID_PEACH_FIRE, getX() - 4, getY(), 180, getWorld()));
            }
        }
    }
}

void Peach::bonk()
{
}

void Peach::setHealth(int h)
{
    m_health = h;
}

void Peach::setShoot(bool s)
{
    m_shootpower = s;
}

void Peach::setStar(bool s)
{
    m_starpower = s;
}

void Peach::setJumps(bool j)
{
    m_jumps = j;
}

// BLOCK 🧱
Block::Block(int imageID, int startX, int startY, StudentWorld* sWorld, bool isSolid, bool hasGoodie) : Actor(imageID, startX, startY, 0, 1, 2, sWorld, isSolid, true)
{
    m_goodie = hasGoodie;
}


void Block::doSomething()
{
}

void Block::bonk()
{
    if (hasGoodie())
    {
        bringGoodie();
    }
    setGoodie(false);
}

bool Block::hasGoodie()
{
    return m_goodie;
}

void Block::setGoodie(bool g)
{
    m_goodie = g;
}

void Block::bringGoodie()
{
}
// STAR BLOCK ⭐️🧱
StarBlock::StarBlock(int imageID, int startX, int startY, StudentWorld* sWorld, bool hasGoodie) : Block(imageID, startX, startY, sWorld, true, true)
{
}

void StarBlock::bringGoodie()
{
    getWorld()->addActor(new Star(IID_STAR, getX(), getY()+8, getWorld()));
}

// MUSHROOM BLOCK 🍄🧱
MushroomBlock::MushroomBlock(int imageID, int startX, int startY,StudentWorld* sWorld, bool hasGoodie) : Block(imageID, startX, startY, sWorld, true, true)
{
}

void MushroomBlock::bringGoodie()
{
    getWorld()->addActor(new Mushroom(IID_MUSHROOM, getX(), getY()+8, getWorld()));
}


// FLOWER BLOCK 🌼🧱
FlowerBlock::FlowerBlock(int imageID, int startX, int startY, StudentWorld* sWorld, bool hasGoodie) : Block(imageID, startX, startY, sWorld, true, true)
{
}

void FlowerBlock::bringGoodie()
{
    getWorld()->addActor(new Flower(IID_FLOWER, getX(), getY()+8, getWorld()));
}

// GOAL 🚩
Goal::Goal(int imageID, int startX, int startY, StudentWorld*  sWorld): Actor(imageID, startX, startY, 0, 1, 1, sWorld, true, false){
    
}

void Goal::doSomething()
{
    if (!isAlive())
        return;
    if (getWorld()->overlapPeach(getX(), getY()))
    {
        kill();
        getWorld()->increaseScore(1000);
    }
}

void Goal::bonk(){
    cout << "bonk!" << endl;
}


// GOODIES 😛
Goodie::Goodie(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isSolid) : Actor(imageID, startX, startY, 0, 1, 1, sWorld, true, false)
{
}

void Goodie::doSomething()
{
    
    if (!isAlive())
        return;
    
    int currX = getX();
    int currY = getY();
    
    if (getWorld()->overlapPeach(currX, currY))
    {
        kill();
        changes();
        return;
    }
    
    int dir = 2;
    if(getDirection() == 180)
        dir = -2;
    
    if (!getWorld()->overlapped(getX(), getY() - 2, false))
        moveTo(getX(), getY() - 2);
            
    if(!getWorld()->overlapped(getX() + dir, getY(), false))
        moveTo(getX() + dir, getY());
    else
        setDirection(dir == 2 ? 180 : 0);
}


// FLOWERS 🌼
Flower::Flower(int imageID, int startX, int startY, StudentWorld* sWorld) : Goodie(IID_FLOWER, startX, startY, 0, 1, 1, sWorld, false)
{
}

void Flower::changes(){
    getWorld()->increaseScore(50);
    getWorld()->peachShoot(true);
    getWorld()->changePeachHealth(2);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
}

// MUSHROOMS 🍄
Mushroom::Mushroom(int imageID, int startX, int startY, StudentWorld* sWorld) : Goodie(IID_MUSHROOM, startX, startY, 0, 1, 1, sWorld, false)
{
}

void Mushroom::changes(){
    getWorld()->increaseScore(75);
    getWorld()->peachJump(true);
    getWorld()->changePeachHealth(2);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
}

// STARS ⭐️
Star::Star(int imageID, int startX, int startY, StudentWorld* sWorld) : Goodie(IID_STAR, startX, startY, 0, 1, 1, sWorld, false)
{
}

void Star::changes(){
    getWorld()->increaseScore(100);
    getWorld()->peachStar(true); 
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
}


// PIRANHA FIREBALLS ☄️
PiranhaFireball::PiranhaFireball(int imageID, int startX, int startY, int dir, StudentWorld* sWorld) : Actor(imageID, startX, startY, dir, 1, 1, sWorld, true, true)
{
}

void PiranhaFireball::doSomething()
{
}

void PiranhaFireball::bonk()
{
    
}

// PEACH FIREBALLS 🔥
PeachFireball::PeachFireball(int imageID, int startX, int startY, int dir, StudentWorld* sWorld) : Actor(imageID, startX, startY, dir, 1, 1, sWorld, true, true)
{
}

void PeachFireball::doSomething()
{
    int currX = getX();
    int currY= getY();
    
    if(getDirection() == 0)
    {
        moveTo(currX + 2, currY);
    }
    if(getDirection() == 180)
    {
        moveTo(currX - 2, currY);
    }
    
    if(!getWorld()->overlapped(currX, currY - 2, false))
    {
        moveTo(currX, currY - 2);
        cout << "GWHGHSGHSGFGHGH " << endl;
    }
    
}

void PeachFireball::bonk()
{
    
}


// SHELLS 🥥
Shell::Shell(int imageID, int startX, int startY, int dir, StudentWorld* sWorld) : Actor(imageID, startX, startY, dir, 1, 0, sWorld, true, true)
{
}


void Shell::doSomething()
{
}

void Shell::bonk()
{
    
}


// GOOMBA 💩
Goomba::Goomba(int imageID, int startX, int startY, StudentWorld* sWorld) : Actor(imageID, startX, startY, (randInt(0, 1) * 180), 0, 1, sWorld, true, false)
{
}


void Goomba::doSomething()
{
    if (!isAlive())
        return;

    int dir = 1;
    
    if(getDirection() == 180)
        dir = -1;
    
    if (!getWorld()->overlapped(getX()+dir, getY(), true))
        moveTo(getX()+dir, getY());
    else
        setDirection(dir == 1 ? 180 : 0);
}

void Goomba::bonk()
{
    
}


// KOOPA 🐢
Koopa::Koopa(int imageID, int startX, int startY, StudentWorld* sWorld) : Actor(imageID, startX, startY, (randInt(0, 1) * 180), 0, 1, sWorld, true, false)
{
}


void Koopa::doSomething()
{
}

void Koopa::bonk()
{
}


// PIRANHA 🌷
Piranha::Piranha(int imageID, int startX, int startY, StudentWorld* sWorld) : Actor(imageID, startX, startY, (randInt(0, 1) * 180), 0, 1, sWorld, true, false)
{
}


void Piranha::doSomething()
{
}


void Piranha::bonk()
{
    
}
