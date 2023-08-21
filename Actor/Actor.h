#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
// Actor Class
class Actor : public GraphObject
{
private:
    StudentWorld* m_world;
    bool lifeStatus;
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth);
    virtual ~Actor();
    virtual void doSomething() = 0;
    void moveActor(int x, int y);
    void dead();
    bool isAlive();
    int getHP();
    StudentWorld* getWorld() const {
            return m_world;
        }
};

// Earth Class
class Earth : public Actor {
public:
    Earth(StudentWorld* world, int startX, int startY);
    virtual void doSomething();
};

// Person Class
class Person :public Actor {
public:
    Person(StudentWorld* world, int imageID, int startX, int startY, Direction dir, int hp);
    int getHP();
    void decreaseHP(int amount);
private:
    int hitPoints;
};

// Tunnelman Class
class Tunnelman : public Person
{
private:
    int m_water;
    int m_sonar;
    int m_nuggets;
public:
    Tunnelman(StudentWorld* world);
    void shootSquirt();
    virtual void doSomething();
    virtual void annoyed(int hp);
    int getSquirts();
    int getSonar();
    int getGold();
    void addInventory(int item);

};

// Boulder Class
class Boulders : public Actor
{
private:
    bool willFall;
    bool stableState;
    int m_ticks;
public:
    Boulders(StudentWorld* world, int startX, int startY);
    virtual void doSomething();
    void boulderAnnoy();
};

// Squirt Class
class Squirt : public Actor {
private:
    int m_waterTicks;
public:
    Squirt(StudentWorld* world, int startX, int startY, Direction startDirection);
    virtual void doSomething();
    bool annoyProtesters();
};

// Goodies Class
class Goodies : public Actor {
private:
    int m_ticks;
public:
    Goodies (StudentWorld* world, int imageID, int startX, int startY);
    ~Goodies();
    virtual void doSomething() = 0;
    void disappear(int ticks);
};

// Oil Barrel Class
class oilBarrel : public Goodies {
public:
    oilBarrel(StudentWorld* world, int startX, int startY);
    virtual ~oilBarrel();
    virtual void doSomething();
};

// Gold Nugget Class
class goldNugget : public Goodies {
private:
    bool mForPlayer;
    bool mTemporary;
    int mTicks;
public:
    goldNugget(StudentWorld* world, int startX, int startY, bool temporary, bool forPlayer);
    virtual ~goldNugget();
    virtual void doSomething();

};

// Sonar Kit Class
class sonarKit : public Goodies {
private:
    int mTicks;
public:
    sonarKit(StudentWorld* world, int startX, int startY, int ticks);
    virtual ~sonarKit();
    virtual void doSomething();

};

// Water Pool Class
class waterPool : public Goodies {
private:
    int mTicks;
public:
    waterPool(StudentWorld* world, int startX, int startY, int ticks);
    virtual ~waterPool();
    virtual void doSomething();
};

// Regular Protestor Class
class Protester : public Person {
private:
    bool m_leaveState;
    int m_numToMove;
    int m_tickSinceLastTurn;
    int m_noYell;
    int m_restingTicks;
public:
    Protester(StudentWorld* world);
    ~Protester();
    virtual void doSomething();
    void numSquaresToMoveInCurrentDirection();
    bool straightPathCheck(Direction dir);
    bool facingPlayerCheck();
    Direction directionToPlayer();
    Direction randomDirection();
    void moveProtester(Direction dir);
    virtual void bribe();
    virtual void annoyed(int hp);


    
};



#endif // ACTOR_H_
