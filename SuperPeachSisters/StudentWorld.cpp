#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_numActors = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    Level lev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry ge;
        for(int i = 0; i < 32; i++)
        {
            for(int j = 0; j < 32; j++)
            {
                ge = lev.getContentsOf(i, j);
                switch (ge)
                {
                    case Level::empty:
                        break;
                    case Level::koopa:
                        addActor(new Koopa(IID_KOOPA, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                    case Level::goomba:
                        addActor(new Goomba(IID_GOOMBA, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                    case Level::peach:
                        m_peach = new Peach(IID_PEACH, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this);
                        break;
                    case Level::flag:
                        addActor(new Goal(IID_FLAG, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                    case Level::block:
                        addActor(new Block(IID_BLOCK, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this, true, false));
                        break;
                    case Level::star_goodie_block:
                        addActor(new StarBlock(IID_BLOCK, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this, true));
                        break;
                    case Level::mushroom_goodie_block:
                        addActor(new MushroomBlock(IID_BLOCK, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this, true));
                        break;
                    case Level::flower_goodie_block:
                        addActor(new FlowerBlock(IID_BLOCK, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this, true));
                        break;
                    case Level::pipe:
                        addActor(new Block(IID_PIPE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this, true, false));
                        break;
                    case Level::piranha:
                        addActor(new Piranha(IID_PIRANHA, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                    case Level::mario:
                        break;
                }
            }
        }
    }
         
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while(it != m_actors.end()) {
        if((*it)->isAlive())
        (*it)->doSomething();
        it++;
        
    }
    m_peach->doSomething();
    for (auto itr = m_actors.begin(); itr != m_actors.end(); itr++) {
        if (!(*itr)->isAlive()) {
            delete *itr;
            m_actors.erase(itr);
            itr = m_actors.begin();
        }
    }
    
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(0);
    oss << "Lives: " << getLives() << "  ";
    oss << "Score: " << getScore() << "  ";
    oss << "Level: " << getLevel() << "  ";
    
    setGameStatText(oss.str());
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end())
    {
        Actor* temp;
        temp = (*it);
        it = m_actors.erase(it);
        delete temp;
    }
}

void StudentWorld::addActor(Actor* a)
{
    m_actors.push_back(a);
    m_numActors++; 
}


bool StudentWorld::overlapped(int x, int y, bool checkBonk)
{
    for(Actor* a:m_actors)
    {
        if(a->getX() < x + SPRITE_WIDTH  && x < a->getX() + SPRITE_WIDTH  && a->getY() < y + SPRITE_HEIGHT  && y < a->getY() + SPRITE_HEIGHT )
        {
            if (checkBonk)
                a->bonk();
            if(a->isSolid())
                return true;
        }
    }
    return false;
}

bool StudentWorld::overlapPeach(int x, int y)
{
    if (m_peach->getX()< x+SPRITE_WIDTH-1 && x < m_peach->getX() + SPRITE_WIDTH - 1 && m_peach->getY()<y+SPRITE_HEIGHT-1 && y < m_peach->getY()+SPRITE_HEIGHT-1)
        return true;
    return false;
}

void StudentWorld::changePeachHealth(int h)
{
    m_peach->setHealth(h);
}

void StudentWorld::peachShoot(bool s)
{
    m_peach->setShoot(s);
}

void StudentWorld::peachJump(bool j)
{
    m_peach->setJumps(j);
}

void StudentWorld::peachStar(bool s)
{
    m_peach->setStar(s);
}

bool StudentWorld::peachHasStar()
{
    return m_peach->hasStar(); 
}
