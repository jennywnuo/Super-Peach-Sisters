#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
#include <iostream>
using namespace std;

// ACTOR 🎭

Actor::Actor(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isAlive, bool isSolid, bool isDamageable)
: GraphObject(imageID, startX, startY, startDirection, size, depth)
{
    m_alive = isAlive;
    m_world = sWorld;
    m_solid = isSolid;
    m_damageable = isDamageable;
}

// PEACH 🍑
Peach::Peach(int imageId, int startX, int startY, StudentWorld* sWorld) : Actor(imageId, startX, startY, 0, 1, 0, sWorld, true, false, true)
{
    m_distance = 0;
    m_shootpower = false;
    m_jumps = false;
    m_temp = false;
    m_recharge = 0;
    m_health = 1;
    m_starpower = 0;
    m_finishLevel = false;
    m_finishGame = false;
}

void Peach::doSomething()
{
    if (!isAlive())
        return;
        
    if(m_distance > 0)
    {
        if (!getWorld()->overlapped(getX(), getY() + 4, true))
        {
            moveTo(getX(), getY() + 4);
            m_distance--;
        }
        else
        {
            m_distance = 0;
        }
    }
    else if (!getWorld()->overlapped(getX(), getY()-1, true) && !getWorld()->overlapped(getX(), getY()-2, true) && !getWorld()->overlapped(getX(), getY()-3, true) && !getWorld()->overlapped(getX(), getY()-4, true))
        moveTo(getX(), getY() - 4);


    if (m_recharge > 0)
        m_recharge--;
    
    if (m_starpower > 0)
        m_starpower--;
    
    if (m_temp > 0)
        m_temp--;
        
    int ch;
    if (getWorld()->getKey(ch))
    {
        if (ch == KEY_PRESS_LEFT && !getWorld()->overlapped(getX() - 4, getY(), true))
        {
            setDirection(180);
            if (getX() > SPRITE_WIDTH)
                this->moveTo(getX()-4, getY());
        }

        if (ch == KEY_PRESS_RIGHT && !getWorld()->overlapped(getX() + 4, getY(), true))
        {
            setDirection(0);
            if (getX() < VIEW_WIDTH - SPRITE_WIDTH * 2)
                this->moveTo(getX()+4, getY());
        }
        
        if (ch == KEY_PRESS_UP)
        {
            if(getWorld()->overlapped(getX(), getY() - 2, false))
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

void Peach::getDamaged()
{
    cerr << "HEALTH:" << m_health << endl;
    if(m_health <= 0)
        kill();
    
    
    if (m_starpower > 0)
        return;

    if(m_shootpower)
    {
        m_shootpower = false;
        setTemp(true);
        m_health += 2;
    }
    else
        m_health--;

    if(m_jumps)
    {
        m_jumps = false;
        setTemp(true);
        m_health += 2;
    }
    else
        m_health--;

    if(m_health == 1)
        getWorld()->playSound(SOUND_PLAYER_HURT);
    
}

// BLOCK 🧱
Block::Block(int imageID, int startX, int startY, StudentWorld* sWorld, bool isSolid, bool hasGoodie) : Actor(imageID, startX, startY, 0, 1, 2, sWorld, isSolid, true, false)
{
    m_goodie = hasGoodie;
}


void Block::bonk()
{
    if (getWorld()->overlapPeach(getX(), getY() -  1) || getWorld()->overlapPeach(getX(), getY() -  2) || getWorld()->overlapPeach(getX(), getY() -  3))
    {
        if (!hasGoodie())
        {
            getWorld()->playSound(SOUND_PLAYER_BONK);
            return;
        }
    }
    
    if (hasGoodie())
    {
        bringGoodie();
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
    }
    setGoodie(false);
}


// STAR BLOCK ⭐️🧱
StarBlock::StarBlock(int imageID, int startX, int startY, StudentWorld* sWorld, bool hasGoodie) : Block(imageID, startX, startY, sWorld, true, true){}

void StarBlock::bringGoodie()
{
    getWorld()->playSound(SOUND_POWERUP_APPEARS);
    getWorld()->addActor(new Star(IID_STAR, getX(), getY()+8, getWorld()));
}

// MUSHROOM BLOCK 🍄🧱
MushroomBlock::MushroomBlock(int imageID, int startX, int startY,StudentWorld* sWorld, bool hasGoodie) : Block(imageID, startX, startY, sWorld, true, true){}

void MushroomBlock::bringGoodie()
{
    getWorld()->playSound(SOUND_POWERUP_APPEARS);
    getWorld()->addActor(new Mushroom(IID_MUSHROOM, getX(), getY()+8, getWorld()));
}

// FLOWER BLOCK 🌼🧱
FlowerBlock::FlowerBlock(int imageID, int startX, int startY, StudentWorld* sWorld, bool hasGoodie) : Block(imageID, startX, startY, sWorld, true, true){}

void FlowerBlock::bringGoodie()
{
    getWorld()->playSound(SOUND_POWERUP_APPEARS);
    getWorld()->addActor(new Flower(IID_FLOWER, getX(), getY()+8, getWorld()));
}

// GOAL 🚩
Goal::Goal(int imageID, int startX, int startY, StudentWorld*  sWorld): Actor(imageID, startX, startY, 0, 1, 1, sWorld, true, false, false){}

void Goal::doSomething()
{
    if (!isAlive())
        return;
    if (getWorld()->overlapPeach(getX(), getY()))
    {
        kill();
        getWorld()->increaseScore(1000);
        getWorld()->finishLevel();
    }
}


// MARIO 👨🏻
Mario::Mario(int imageID, int startX, int startY, StudentWorld*  sWorld): Goal(imageID, startX, startY, sWorld){}

void Mario::doSomething()
{
    if (!isAlive())
        return;
    if (getWorld()->overlapPeach(getX(), getY()))
    {
        kill();
        getWorld()->increaseScore(1000);
        getWorld()->finishGame();
    }
}


// GOODIES 😛
Goodie::Goodie(int imageID, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isSolid) : Actor(imageID, startX, startY, 0, 1, 1, sWorld, true, false, false){}

void Goodie::doSomething()
{
    
    if (!isAlive())
        return;
        
    if (getWorld()->overlapPeach(getX(), getY()))
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
Mushroom::Mushroom(int imageID, int startX, int startY, StudentWorld* sWorld) : Goodie(IID_MUSHROOM, startX, startY, 0, 1, 1, sWorld, false){}

void Mushroom::changes(){
    getWorld()->increaseScore(75);
    getWorld()->peachJump(true);
    getWorld()->changePeachHealth(2);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
}

// STARS ⭐️
Star::Star(int imageID, int startX, int startY, StudentWorld* sWorld) : Goodie(IID_STAR, startX, startY, 0, 1, 1, sWorld, false){}

void Star::changes(){
    getWorld()->increaseScore(100);
    getWorld()->peachStar(true);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
}


// PIRANHA FIREBALLS ☄️
PiranhaFireball::PiranhaFireball(int imageID, int startX, int startY, int dir, StudentWorld* sWorld) : Actor(imageID, startX, startY, dir, 1, 1, sWorld, true, false, false){}

void PiranhaFireball::doSomething()
{
    int dir = 2;
    if(getDirection() == 180)
        dir = -2;

    if(!getWorld()->overlapped(getX(), getY() - 2, false))
    {
        moveTo(getX(), getY() - 2);
    }

    if(!getWorld()->overlapped(getX() + dir, getY(), true))
        moveTo(getX() + dir, getY());
    else
    {
        kill();
        return;
    }
    if (getWorld()->overlapPeach(getX(), getY()))
    {
        getWorld()->peachDamage();
    }
}


// PEACH FIREBALLS 🔥
PeachFireball::PeachFireball(int imageID, int startX, int startY, int dir, StudentWorld* sWorld) : Actor(imageID, startX, startY, dir, 1, 1, sWorld, true, false, false){}

void PeachFireball::doSomething()
{
    int dir = 2;
    if(getDirection() == 180)
        dir = -2;
    
    if(!getWorld()->overlapped(getX(), getY() - 2, false))
    {
        moveTo(getX(), getY() - 2);
    }
    
    if(!getWorld()->overlapped(getX() + dir, getY(), true))
        moveTo(getX() + dir, getY());
    else
    {
        kill();
        return;
    }
    
    if (getWorld()->damageActor(getX(), getY())) {
        kill();
    }
}


// SHELLS 🥥
Shell::Shell(int imageID, int startX, int startY, int dir, StudentWorld* sWorld) : Actor(imageID, startX, startY, dir, 1, 0, sWorld, true, false, false){}

void Shell::doSomething()
{
    if (!isAlive())
        return;
    int dir = 2;
    if(getDirection() == 180)
        dir = -2;
    
    if (!getWorld()->overlapped(getX() + dir, getY(), false))
        moveTo(getX()+dir, getY());
    
    if (!getWorld()->overlapped(getX() + dir, getY() - 2, false))
        moveTo(getX(), getY() - 2);
    
    if (getWorld()->overlapped(getX() + dir, getY(), false))
    {
        kill();
        return;
    }
    if (getWorld()->damageActor(getX(), getY()))
    {
        kill();
        return;
    }
}


// GOOMBA 💩
Goomba::Goomba(int imageID, int startX, int startY, StudentWorld* sWorld) : Actor(imageID, startX, startY, (randInt(0, 1) * 180), 0, 1, sWorld, true, false, true){}


void Goomba::doSomething()
{
    if (!isAlive())
        return;

    int dir = 1;
    
    if(getDirection() == 180)
        dir = -1;
    
    if (!getWorld()->overlapped(getX() + dir, getY(), false))
        moveTo(getX()+dir, getY());
    
    if (!getWorld()->overlapped(getX() + (dir * SPRITE_WIDTH), getY() - 2, false) || getWorld()->overlapped(getX() + dir, getY(), false)) // if nothing under or if bonking object
        setDirection(dir == 1 ? 180 : 0);
}

void Goomba::bonk()
{
    if (getWorld()->overlapPeach(getX(), getY()))
    {
        if(getWorld()->peachHasStar())
        {
            getWorld()->playSound(SOUND_PLAYER_KICK);
            getDamaged();
        }
        if(getWorld()->peachHasJump() || getWorld()->peachHasFire())
        {
            getWorld()->peachTemp(true);
        }
        getWorld()->damagePeach();
    }
    else
        return;
    
}

void Goomba::getDamaged()
{
    getWorld()->increaseScore(100);
    this->kill();
    return;
}

// KOOPA 🐢
Koopa::Koopa(int imageID, int startX, int startY, StudentWorld* sWorld) : Actor(imageID, startX, startY, (randInt(0, 1) * 180), 0, 1, sWorld, true, false, true){}

void Koopa::doSomething()
{
    if (!isAlive())
        return;

    int dir = 1;
    if(getDirection() == 180)
        dir = -1;
    
    if (!getWorld()->overlapped(getX() + dir, getY(), false))
        moveTo(getX()+dir, getY());
    
    if (!getWorld()->overlapped(getX() + (dir * SPRITE_WIDTH), getY() - 2, false) || getWorld()->overlapped(getX() + dir, getY(), false)) // if nothing under or if bonking object
        setDirection(dir == 1 ? 180 : 0);
        
}

void Koopa::bonk()
{
    if (getWorld()->overlapPeach(getX(), getY()))
    {
        if(getWorld()->peachHasStar())
        {
            getWorld()->playSound(SOUND_PLAYER_KICK);
            getDamaged();
        }
        if(getWorld()->peachHasJump() || getWorld()->peachHasFire())
        {
            getWorld()->peachTemp(true);
        }
        getWorld()->peachDamage();
    }
    else
        return;
}

void Koopa::getDamaged()
{
    getWorld()->increaseScore(100);
    this->kill();
    return;
}

Koopa::~Koopa()
{
    int dir = getDirection();
    getWorld()->addActor(new Shell(IID_SHELL, getX(), getY(), dir, getWorld()));
}

// PIRANHA 🌷
Piranha::Piranha(int imageID, int startX, int startY, StudentWorld* sWorld) : Actor(imageID, startX, startY, (randInt(0, 1) * 180), 0, 1, sWorld, true, false, true)
{
    m_delay = 0;
}


void Piranha::doSomething()
{
    if (!isAlive())
        return;
    this->increaseAnimationNumber();
    
    if(getWorld()->overlapPeach(getX(), getY()))
    {
        bonk(); // BONK PEACH
        return;
    }
    
    if (getWorld()->peachHeight() <= this->getY() + (1.5 * SPRITE_HEIGHT) && getWorld()->peachHeight() >= this->getY() - (1.5 * SPRITE_HEIGHT))
    {
        if(getWorld()->peachWidth() < this->getX()) // left
        {
            this->setDirection(180);
            if (getWorld()->peachWidth() >= this->getX() - (8 * SPRITE_WIDTH))
            {
                if (m_delay == 0)
                {
                    getWorld()->playSound(SOUND_PIRANHA_FIRE);
                    getWorld()->addActor(new PiranhaFireball(IID_PIRANHA_FIRE, getX(), getY(), 180, getWorld()));
                    m_delay = 40;
                }
                else
                    m_delay--;
            }
        }
        if(getWorld()->peachWidth() > this->getX()) // right
        {
            this->setDirection(0);
            if (getWorld()->peachWidth() <= this->getX() + (8 * SPRITE_WIDTH))
            {
                if (m_delay == 0)
                {
                    getWorld()->playSound(SOUND_PIRANHA_FIRE);
                    getWorld()->addActor(new PiranhaFireball(IID_PIRANHA_FIRE, getX(), getY(), 0, getWorld()));
                    m_delay = 40;
                }
                else
                    m_delay--;
            }
        }
        
    }
    else
        return;
}


void Piranha::bonk()
{
    if (getWorld()->overlapPeach(getX(), getY()))
    {
        if(getWorld()->peachHasStar())
        {
            getWorld()->playSound(SOUND_PLAYER_KICK);
            getDamaged();
        }
        if(getWorld()->peachHasJump() || getWorld()->peachHasFire())
        {
            getWorld()->peachTemp(true);
        }
    }
    else
        return;
}

void Piranha::getDamaged()
{
    getWorld()->increaseScore(100);
    this->kill();
    return;
}
