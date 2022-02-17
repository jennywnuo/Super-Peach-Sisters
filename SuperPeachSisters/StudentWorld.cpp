#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <vector>
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    std::vector<Actor> m_actors;
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
        // x=5, y=10
        for(int i = 0; i < 32; i++)
        {
            for(int j = 0; j < 32; j++)
            {
                ge = lev.getContentsOf(i, j);
                switch (ge)
                {
                    case Level::empty:
                        cout << "lol" << endl;
                        break;
                    case Level::koopa:
                        cout << "lol" << endl;
                        break;
                    case Level::goomba:
                        cout << "lol" << endl;
                        break;
                    case Level::peach:
                        m_peach = new Peach(IID_PEACH, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0 , 1 , 0, this);
                        break;
                    case Level::flag:
                        cout << "lol" << endl;
                        break;
                    case Level::block:
                        m_actors.push_back(new Block(IID_BLOCK, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0, 1, 2, this));
                        break;
                    case Level::star_goodie_block:
                        cout << "lol" << endl;
                        break;
                    case Level::piranha:
                        cout << "lol" << endl;
                        break;
                    case Level::mushroom_goodie_block:
                        cout << "lol" << endl;
                        break;
                    case Level::flower_goodie_block:
                        cout << "lol" << endl;
                        break;
                    case Level::pipe:
                        cout << "lol" << endl;
                        break;
                    case Level::mario:
                        cout << "lol";
                        break;
                }
            }
        }
    }
         
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    m_peach->doSomething();
    
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end())
    {
        (*it)->doSomething();
        it++;
    }

    decLives();
    return GWSTATUS_CONTINUE_GAME; // GWSTATUS_PLAYER_DIED
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

bool StudentWorld::overlappedLeft(int x, int y)
{
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end())
    {
        if((*it)->getX() + SPRITE_WIDTH + SPRITE_WIDTH - 1 == x && (*it)->getY() + SPRITE_HEIGHT - 1 == y)
        {
            return true;
        }
        it++;
    }
    return false;
}

bool StudentWorld::overlappedRight(int x, int y)
{
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end())
    {
        if((*it)->getX() + SPRITE_WIDTH - 1 == x + SPRITE_WIDTH && (*it)->getY() + SPRITE_HEIGHT - 1 == y)
        {
            return true;
        }
        it++;
    }
    return false;
    
}
