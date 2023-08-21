#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include <vector>
#include <queue>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class GraphObject;
class Actor;
class Tunnelman;
class Earth;
class Protester;
class goldNugget;


class StudentWorld : public GameWorld
{
private:
    std::vector<Actor*> m_actor;
    Tunnelman* m_player;
    std::unique_ptr<Earth> m_Earth[64][64];
    int m_map[64][64];
    bool firstTic;
    int ticksPassed;
    int m_protesters;
    int numBarrels;
    struct Grid {
           int x, y;
           Grid(int a, int b): x(a), y(b){}
        };
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    // Action
    bool dig(int x, int y);
    void exit(Protester* protester);
    // Display
    void setDisplayText();
    std::string formatDisplay(int level, int lives, int health, int squirt, int gold, int barrelsLeft, int sonar, int score);
    // Get Functions
    Tunnelman* getPlayer();
    int getBarrelsLeft();
    // Decrease
    void decreaseBarrel();
    void decreaseProtester();
    // Checks
    bool aboveCheck(int x, int y);
    bool earthCheck(int x, int y);
    bool boulderCheck(int x, int y, int radius = 3);
    bool radiusCheck(int x, int y, int x1, int y1, int radius);
    bool playerRadiusCheck(Actor *actor, int radius);
    Protester* protesterRadiusCheck(Actor* actor, int radius);
    bool directionCheck(int x, int y, GraphObject::Direction direction);
    // Add Objects to Game
    void addActor(Actor *actor);
    void addProtestor();
    void addGoodies();
    void addBarrel();
    void addBoulder();
    void addGold();
    void addSonarOrWater();
};

#endif // STUDENTWORLD_H_

