#include "Actor.h"
#include "StudentWorld.h"

#include <iostream>
using namespace std;

// ACTOR 🎭

Actor::Actor(int imageId, int startX, int startY, int startDirection, int depth, double size, StudentWorld* sWorld, bool isAlive)
: GraphObject(imageId, startX, startY, startDirection, size, depth)
{
    m_alive = isAlive;
    m_world = sWorld;
}

Actor::~Actor()
{
}

bool Actor::isAlive() const
{
    return m_alive;
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

// PEACH 🍑

Peach::Peach(int imageId, int startX, int startY, int dir, int depth, double size, StudentWorld* sWorld) : Actor(imageId, startX, startY, dir, depth, size, sWorld, true)
{
}

Peach::~Peach()
{
}

void Peach::doSomething()
{
    int currX = getX();
    int currY = getY();
    
    int ch;
    if (getWorld()->getKey(ch))
    {
        if (ch == KEY_PRESS_LEFT)
        {
            setDirection(180);
            this->moveTo(currX-4, currY);
        }
        
        if (ch == KEY_PRESS_RIGHT)
        {

            setDirection(0);
            this->moveTo(currX+4, currY);
        }
    }
    
    if(getWorld()->overlappedLeft(currX + SPRITE_WIDTH - 1, currY + SPRITE_HEIGHT - 1))
    {
        if (ch == KEY_PRESS_LEFT)
        {
            setDirection(180);
            this->moveTo(currX, currY);
        }
    }
    if(getWorld()->overlappedRight(currX + SPRITE_WIDTH - 1, currY + SPRITE_HEIGHT - 1))
    {
        if (ch == KEY_PRESS_RIGHT)
        {
            setDirection(0);
            this->moveTo(currX, currY);
        }
    }
}


// BLOCK 🧱

Block::Block(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* sWorld) : Actor(imageID, startX, startY, dir, depth, size, sWorld, true)
{
}

Block::~Block()
{
}

void Block::doSomething()
{
}
