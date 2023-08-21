
#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor Class ---------------------------------------------
Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, Direction startDirection, float size, unsigned int depth)
    :GraphObject(imageID, startX, startY, startDirection, size, depth), m_world(world), lifeStatus(true)
{
    setVisible(true); //Actors start out visible unless stated otherwise
}
// Destructor
Actor::~Actor()
{
    setVisible(false);
    m_world = nullptr;
    delete m_world;
}
// Move Actor
void Actor::moveActor(int x, int y)
{
    // Wall Boundary Limits
    if (x < 0)
        x = 0;
    if (x > 60)
        x = 60;
    if (y < 0)
        y = 0;
    if (y > 60)
        y = 60;
    // Move Actor to Coordinates
    GraphObject::moveTo(x,y);
}
// Dead: If Actor is dead, set lifeStatus to false so actor will not be shown on screen
void Actor::dead()
{
    lifeStatus = false;
}
// Is Alive: Bool to check if actor is alive or not
bool Actor::isAlive(){
    return lifeStatus;
}
// ---------------------------------------------------------

// Person Class---------------------------------------------
Person::Person(StudentWorld* world, int imageID, int startX, int startY, Direction direction, int HP)
    :Actor(world, imageID, startX, startY, direction, 1, 0), hitPoints(HP) {}
// Return HP of person
int Person::getHP(){
    return hitPoints;
}
// Decrease HP of person
void Person::decreaseHP(int amount){
    hitPoints = hitPoints - amount;
}
// ---------------------------------------------------------

// Earth Class----------------------------------------------
Earth::Earth(StudentWorld* world, int startX, int startY)
    :Actor(world, TID_EARTH, startX, startY, right, 0.25, 3)
{}
void Earth::doSomething() { } // Does Nothing
// ---------------------------------------------------------

// Tunnelman Class------------------------------------------
Tunnelman::Tunnelman(StudentWorld* world)
    :Person(world, TID_PLAYER, 30,60, right, 10),m_water(5), m_sonar(1), m_nuggets(0){
            setVisible(true);
    }
// Shoot
// Tunnelman shoots water, function works by checking the direction the tunnelman
// is currently facing and checking to see if there is any Earth of Boulder in its path.
// If not, a squirt object is created and its accompanying sound is made.
void Tunnelman::shootSquirt() {
    switch (getDirection())
    {
    // Do Nothing
    case none:
            return;
    case up:
        if (getWorld()->earthCheck(getX(),getY() + 4) == false && getWorld()->boulderCheck(getX(),getY()+4) == false)
            getWorld()->addActor(new Squirt(getWorld(),getX(),getY()+4,getDirection()));
            break;
    case left:
        if (getWorld()->earthCheck(getX()-4,getY()) == false && getWorld()->boulderCheck(getX()-4, getY()) == false)
            getWorld()->addActor(new Squirt(getWorld(),getX()-4,getY(),getDirection()));
            break;
    case right:
        if (getWorld()->earthCheck(getX() + 4, getY()) == false && getWorld()->boulderCheck(getX()+4, getY())== false)
            getWorld()->addActor(new Squirt(getWorld(),getX()+4,getY(),getDirection()));
            break;
    case down:
        if (getWorld()->earthCheck(getX() , getY()-4) == false && getWorld()->boulderCheck(getX(), getY()-4) == false)
            getWorld()->addActor(new Squirt(getWorld(),getX(),getY()-4,getDirection()));
        break;
    }
    // Play Squirt Sound
    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
}
// Do Something: Most Important Tunnelman Function
void Tunnelman::doSomething(){
    // Check if Tunnelman currently alive
    // If not, return
    if (isAlive() == false)
        return;
    // Check if human player pressed Key
    int key;
    if (getWorld()->getKey(key) == true)
    {
        switch (key)
        {
        // Esc: User Escapes Level
        case KEY_PRESS_ESCAPE:
                    dead();
                    break;
        // Spacebar: TunnelMan will Fire Squirt
        case KEY_PRESS_SPACE:
                if (m_water >= 1) {
                    m_water--;
                    shootSquirt();
                    }
                    break;
        // Up: Move Up if Tunnelman already facing Up
        case KEY_PRESS_UP:
                // If not already facing up, make Tunnelman face up
                if (getDirection() != up){
                    setDirection(up);
                }
                // If already facing up
                else{
                    // Move Tunnelman Up 1 Space if no boulder in way
                    if (getWorld()->boulderCheck(getX(),getY()+1) == false)
                                moveActor(getX(), getY() + 1);
                    else
                    // Dig through Earth
                                moveActor(getX(), getY());
                                getWorld()->dig(getX(),getY());
                    }
                break;
        // Left: Move Up if Tunnelman already facing Left
        case KEY_PRESS_LEFT:
                if (getDirection() != left){
                    setDirection(left);
                }
                else{
                    if (getWorld()->boulderCheck(getX()-1,getY()) == false)
                                moveActor(getX()-1, getY());
                        else moveActor(getX(), getY());
                    getWorld()->dig(getX(),getY());

                    }
                break;
        // Right: Move Up if Tunnelman already facing Right
        case KEY_PRESS_RIGHT:
                        if (getDirection() != right){
                            setDirection(right);
                        }
                        else{
                            if (getWorld()->boulderCheck(getX()+1,getY()) == false){
                                getWorld()->dig(getX(),getY());

                                        moveActor(getX()+1, getY());
                            }
                                    else moveActor(getX(), getY());
                                    getWorld()->dig(getX(),getY());

                            }
                break;
        // Down: Move Up if Tunnelman already facing Down
        case KEY_PRESS_DOWN:
                if (getDirection() != down){
                    setDirection(down);
                }
                else{
                    if (getWorld()->boulderCheck(getX(),getY()-1) == false)
                                moveActor(getX(), getY()-1);
                            else moveActor(getX(), getY());
                        getWorld()->dig(getX(),getY());

            }
                break;
        // Tab: Leave behind a Gold Nugget as a Bribe
        case KEY_PRESS_TAB:
                    // If Tunnelman has sufficient amount of nuggets
                    if (m_nuggets >= 1) {
                        // Leave one on ground
                        getWorld()->addActor(new goldNugget(getWorld(),getX(),getY(),true,true));
                        m_nuggets--;
                        }
                        break;
        // 'Z' or 'z': Activate Sonar
        case ('Z'|'z'):
                    if (m_sonar > 0)
                    {
                        m_sonar--;
                        //getWorld()->detectNearActors(getX(), getY(), 12);
                        getWorld()->playSound(SOUND_SONAR);
                    }
                    break;
        }
    }
}
// Annoyed: Tunnelman loses some HP if they get annoyed
void Tunnelman::annoyed(int hp){
    // Decreases HP by amount specified by program
    decreaseHP(hp);
    // If Tunnelman reaches 0 HP, they will die
    if (getHP() <= 0) {
            dead();
            getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
        }
}
// Get Private Members
// Get Number of Squirts
int Tunnelman::getSquirts()
{
    return m_water;
}
// Get Number of Sonars
int Tunnelman::getSonar()
{
    return m_sonar;
}
// Get Number of Gold Nuggets
int Tunnelman::getGold()
{
    return m_nuggets;
}
// Add Inventory: Adds a specified number of an object to Tunnelman's inventory
void Tunnelman::addInventory(int item)
{
    // Adds 5 squirts if Tunnelman collects water
    if (item == TID_WATER_POOL)
        m_water += 5;
    // Adds 1 gold nugget if Tunnelman collects gold
    if (item == TID_GOLD)
        m_nuggets++;
    // Adds 1 sonar if Tunnelman collects sonar kit
    if (item == TID_SONAR)
        m_sonar++;
}
// ---------------------------------------------------------

// Boulder Class--------------------------------------------
Boulders::Boulders(StudentWorld* world, int startX, int startY)
    : Actor(world, TID_BOULDER, startX, startY, down, 1.0, 1), stableState(true), m_ticks(0)
{
    world->dig(startX, startY);
}
// Do Something
void Boulders::doSomething(){
            // Check if Boulder is currently alive, if not, return
            if (isAlive() == false)
                return;
            // If Boulder is currently stable, meaning there the boulder is above Earth
            if (stableState == true){
                if (getWorld()->aboveCheck(getX(), getY() - 1))
                    // Return since it is just a boulder
                    return;
                else
                    // If there is no Earth under boulder, boulder is unstable
                    stableState = false;
                }
            // If Boulder is unstable, it will fall in 30 ticks
            if (stableState == false){
                // If 30 ticks have passed, play falling rock sound
                if (m_ticks == 30) {
                    willFall = true;
                    getWorld()->playSound(SOUND_FALLING_ROCK);
                    }
                // Keep iterating ticks until boulder falls
                m_ticks++;
                // If boulder is falling
                if (willFall == true) {
                    // Kill Boulder once it has fallen all the way
                    if (getY()==0 || getWorld()->aboveCheck(getX(), getY()-1)|| getWorld()->boulderCheck(getX(), getY()-4, 0))
                        dead();
                    // If Boulder is still falling, keep moving Boulder downwards
                    // Check to see if Tunnelman is Under Falling Boulder
                    else
                        moveTo(getX(), getY() - 1);
                        boulderAnnoy();
            }
    }
}
// Boulder Annoy: Check to see if Tunnelman is under Falling Boulder
void Boulders::boulderAnnoy(){
    if (getWorld()->playerRadiusCheck(this, 3)) {
            // If Tunnelman is under, instantly lose one life by losing 100HP.
            getWorld()->getPlayer()->annoyed(100);
        }
}
// ---------------------------------------------------------

// Squirt Class---------------------------------------------
Squirt::Squirt(StudentWorld* world, int startX, int startY, Direction dir)
    :Actor(world, TID_WATER_SPURT, startX, startY, dir, 1.0, 1) {}

void Squirt::doSomething(){
    // If squirt is not alive, return
    if (isAlive() == false)
        return;
    // If squirt has been out for 4 ticks, kill it
    if (m_waterTicks == 4 ) {
            dead();
            return;
        }
    // If the squirt hits a protester, kill it
    if (annoyProtesters() == true){
            dead();
            return;
    }
    // Check which direction Tunnelman is facing
    switch (getDirection()) {
        // Facing up, check if there is enough space to shoot
        case up:
            // If not enough space, kill squirt
            if (getWorld()->earthCheck(getX(), getY() + 1) || getWorld()->boulderCheck(getX(), getY() + 1)) {
                dead();
                return;
            }
            // If enough space, move squirt in that direction
            else
                moveTo(getX(), getY() + 1);
                break;
        // Facing left, check if there is enough space to shoot
        case left:
            if (getWorld()->earthCheck(getX() - 1, getY()) || getWorld()->boulderCheck(getX() - 1, getY())) {
                dead();
                return;
            }
            else
                moveTo(getX() - 1, getY());
                break;
        // Facing right, check if there is enough space to shoot
        case right:
            if (getWorld()->earthCheck(getX() + 1, getY()) || getWorld()->boulderCheck(getX() + 1, getY())) {
                dead();
                return;
            }
            else
                moveTo(getX() + 1, getY());
                break;
        // Facing down, check if there is enough space to shoot
        case down:
            if (getWorld()->earthCheck(getX(), getY() - 1) || getWorld()->boulderCheck(getX(), getY() - 1)) {
                dead();
                return;
            }
            else
                moveTo(getX(), getY() - 1);
                break;
        // None, should not happen and just return
        case none:
                return;
        }
        // Keep iterating ticks until squirt has to be kiled
        m_waterTicks++;
}
// Annoy Protester: Check to see if Protester was hit by squirt
bool Squirt::annoyProtesters()
{
    // Check to see if protester is within 3 spaces of squirt
    Protester* protester= getWorld()->protesterRadiusCheck(this, 3);
    // If yes, protester loses 2 HP for getting hit and return true
    if (protester != nullptr) {
        protester->annoyed(2);
        return true;
    }
    // Return false if not hit
    return false;
}
// ---------------------------------------------------------

// Goodies Class-----------------------------------------------
// This class contains all the collectible items
Goodies::Goodies(StudentWorld* world, int imageID, int startX, int startY)
    :Actor(world, imageID, startX, startY, right, 1.0, 2) {}
// Destructor
Goodies::~Goodies()
{
    setVisible(false);
}
// Dissapear: All goodies in this game are temporary and disappear after a certain
// number of ticks.
void Goodies::disappear(int ticks){
    // If max number of ticks item can last in game is reached, kill the goodie
    if (m_ticks == ticks)
        dead();
    // If not reached, keep counting
    else
        m_ticks++;
}
// ---------------------------------------------------------

// Oil Barrel Class-----------------------------------------
oilBarrel::oilBarrel(StudentWorld* world, int startX, int startY)
    :Goodies(world, TID_BARREL, startX, startY)
{
    // Starts off Hidden, point of game is to find them
    setVisible(false);
}
// Destructor
oilBarrel::~oilBarrel(){
    setVisible(false);
}
// Do Something
void oilBarrel::doSomething(){
    // If barrel is currenty not alive, return
    if (isAlive() == false)
        return;
    // If player is within 3 units away, Tunnelman has found barrel
    if (getWorld()->playerRadiusCheck(this, 3) == true){
            // Remove barrel from screen, play sound, increase score by 1000 points
            // Decrease total number of barrels left to find in game and return
            dead();
            getWorld()->playSound(SOUND_FOUND_OIL);
            getWorld()->increaseScore(1000);
            getWorld()->decreaseBarrel();
            return;
    }
    // If player is within 4 units away from barrel, make barrel visible and return
    if (getWorld()->playerRadiusCheck(this, 4) == true){
        setVisible(true);
        return;
    }
}
// ---------------------------------------------------------

// Gold Nugget Class----------------------------------------
goldNugget::goldNugget(StudentWorld* world, int startX, int startY, bool temporary, bool forPlayer)
    :Goodies(world, TID_GOLD, startX, startY)
{
    mTemporary = temporary;
    mForPlayer = forPlayer;
    mTicks = 0;
    setVisible(false);
}
// Destructor
goldNugget::~goldNugget(){
    setVisible(false);
}
// Do Something
void goldNugget::doSomething(){
    // Check to see if nugget is currently alive, if not, return
    if (isAlive() == false)
        return;
    // If the gold is meant for player to pick up
    if (mForPlayer == true){
            // If player is within 4 units, make nugget visible
            if (getWorld()->playerRadiusCheck(this, 4)== true)
                setVisible(true);
            // If player is within 3 units, Tunnelman has collected a nugget
            if (getWorld()->playerRadiusCheck(this,3)== true)
                {
                    // Remove nugget from screen, play sound, increase score by 10 points
                    // Decrease total number of barrels left to find in game and return
                    dead();
                    getWorld()->playSound(SOUND_GOT_GOODIE);
                    getWorld()->increaseScore(10);
                    getWorld()->getPlayer()->addInventory(TID_GOLD);
                }
            }
    if (mForPlayer == false){
        // If gold is meant for protester to pick up
        // If protester is within 3 units of gold, it has collected it
        Protester* protester = (getWorld()->protesterRadiusCheck(this, 3));
                if (protester != nullptr) {
                    // Kill the gold nugget and mark that protester has been bribed
                    dead();
                    protester -> bribe();
                };
                // If not picked up in 100 tics by protester, nugget dies
                disappear(100);
    }
    // If nugget is in temporary state, keep counting tics until it dies
    if (mTemporary == true){
        // If nugget reaches 100 ticks, dies
            if (mTicks == 100)
                dead();
        // Keep iterating
        mTicks++;
        }
}
// ---------------------------------------------------------

// Sonar Kit Class------------------------------------------
sonarKit::sonarKit(StudentWorld* world, int startX, int startY, int ticks)
    :Goodies(world, TID_SONAR, startX, startY) {
        mTicks = ticks;
        setVisible(true);
    }
// Destructor
sonarKit::~sonarKit()
{
    setVisible(false);
}
// Do something
void sonarKit::doSomething(){
    // If sonar is currently dead, return
    if (isAlive() == false)
        return;
    // If player is within 3 units, Tunnelmnan has collected a sonar kit
    if (getWorld()->playerRadiusCheck(this, 3)==true)
        {
            // Remove sonar from screen, play sound, increase score by 75 points
            // Decrease total number of barrels left to find in game and return
            dead();
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->increaseScore(75);
            getWorld()->getPlayer()->addInventory(TID_SONAR);
        }
    // Sonar always in temporary state, so keep deducting until no more ticks
    mTicks--;
        // The amount of ticks it can last is determined in another function
       if(mTicks == 0)
           dead();
}
// ---------------------------------------------------------

// Water Pool Class-----------------------------------------
waterPool::waterPool(StudentWorld* world, int startX, int startY, int ticks)
    :Goodies(world, TID_WATER_POOL, startX, startY) {
        mTicks = ticks;
        setVisible(true);
    }
// Destructor
waterPool::~waterPool()
{
    setVisible(false);
}
// Do Something
void waterPool::doSomething(){
    // If water pool is currently dead, return
    if (isAlive() == false)
        return;
    // If player is within 3 units of water pool, Tunnelman has collected it
    if (getWorld()->playerRadiusCheck(this, 3)==true)
        {
            // Remove pool from screen, play sound, increase score by 100 points
            // Decrease total number of barrels left to find in game and return
            dead();
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->increaseScore(100);
            getWorld()->getPlayer()->addInventory(TID_WATER_POOL);
        }
    // Water Pool is always in temporary state, so keep deducting until no more ticks
    mTicks--;
    // The amount of ticks it can last is determined in another function
       if(mTicks == 0)
           dead();
}
// ---------------------------------------------------------

// Protestor Class------------------------------------------
Protester::Protester(StudentWorld* world)//, int imageID, int hP)
: Person(world, TID_PROTESTER, 60, 60, left, 10){
    numSquaresToMoveInCurrentDirection();
    m_restingTicks = max(0, 3 - (int)getWorld()->getLevel() / 4);
    setVisible(true);
}
// Destrcutor
Protester::~Protester()
{
    setVisible(false);
}
// Do Something
void Protester::doSomething(){
    // If Protester is not alive currently, return
    if (isAlive() == false)
        return;
    // If Protester is in resting state, it must do nothing other than
    // update its resting tick count and return
    if (m_restingTicks >= 1) {
        m_restingTicks--;
            return;
        }
    // If protester in a leave the field state
    if (m_leaveState == true) {
            // If protester is at its exit point, set to dead so it will be removed
            if (getX() == 60 && getY() == 60) {
                dead();
                // Decrease number of protesters
                getWorld()->decreaseProtester();
                return;
            }
            // If not at exit, protester must move one square closer to exit
            getWorld()->exit(this);
            return;
        }
    // Check to see if Protester is within 4 units of the Tunnelman
    // AND if Protester is facing Tunnelman
    if (getWorld()->playerRadiusCheck(this, 4) && facingPlayerCheck()==true) {
            // If both are true and Protester has not shouted in 15 non-resting ticks
            if (m_noYell >= 15) {
                // Play shouting sound and deduce 2 HP from Tunnelman
                getWorld()->playSound(SOUND_PROTESTER_YELL);
                getWorld()->getPlayer()->annoyed(2);
                // Reset no yell ticks to 0
                m_noYell = 0;
                return;
            }
            return;
        }
    // Otherwise, if Protester is in a straight horizontal or vertical line
    // of sight to the TunnelMan AND more than 4 units away from the TunnelMan
        Direction dir = directionToPlayer();
        if (getWorld()->earthCheck(getX(),getY()) == false && getWorld()->boulderCheck(getX(),getY()) == false && straightPathCheck(dir) && (getWorld()->playerRadiusCheck(this, 4)) == false) {
            // Protester will change its direction to face in the direction
            // of the TunnelMan, AND then take one step toward him.
            setDirection(dir);
            moveProtester(dir);
            m_numToMove = 0;
            return;
        }
    // Otherwise Protestor cannot directly see Tunnelman
        m_numToMove--;
        // If no more moves to be made
        if (m_numToMove == 0) {
            Direction dir = randomDirection();
                while (true) {
                    dir = randomDirection();
                    // If direction is clear for Protester to walk through, break
                    if (getWorld()->directionCheck(getX(),getY(),dir) == true)
                        break;
                }
                // If not, set new direction
                setDirection(dir);
                numSquaresToMoveInCurrentDirection();
            }
    //Finally, the Regular Protester will then attempt to take one step
    //in its currently facing direction
        moveProtester(getDirection());
    //If the Regular Protester is for some reason blocked from taking a
    //step in its currently facing direction, it will find a new Direction
        if (getWorld()->directionCheck(getX(),getY(),getDirection()) == false) {
            m_numToMove = 0;
        }
}
// Number Squares To Move in Current Direction
// Each Regular Protester must decide how many squares it will decide to move left
// before possibly switching its direction. This value must be between 8 and 60.
void Protester::numSquaresToMoveInCurrentDirection()
{
    m_numToMove = rand() % 51 + 8;
}
// Straight Path Check
// Check to see if the Protester is in a straight horizontal or vertical
// line of sight to the TunnelMan
bool Protester::straightPathCheck(Direction direction)
{
    // Get Tunnelman's current location
    int x = getWorld()->getPlayer()->getX();
    int y = getWorld()->getPlayer()->getY();
    // Check which direction Protester is facing
    switch (direction) {
    // None: Return False
    case none:
        return false;
    // Up:
    case up:
        // For the player y-coordinate to the protester y-coordinate, check if any boulder or
        // earth in path
        for (int i = getY(); i <= y; i++) {
            // If there is, return false
            if (getWorld()->earthCheck(getX(), i) == true || getWorld()->boulderCheck(getX(), i) == true)
                return false;
        }
        // If not, return true
        return true;
        break;
    // Left:
    case left:
        // For the player x-coordinate to the protester x-coordinate, check if any boulder or
        // earth in path
        for (int i = getX(); i >= x; i--) {
            // If there is, return false
            if (getWorld()->earthCheck(i, getY() == true) || getWorld()->boulderCheck(i, getY()) == true)
                return false;
        }
        return true;
        break;
    // Right:
    case right:
        for (int i = getX(); i <= x; i++) {
            if (getWorld()->earthCheck(i, getY() == true) || getWorld()->boulderCheck(i, getY()) == true)
                return false;
        }
        return true;
        break;
    // Down:
    case down:
        for (int i = getY(); i >= y; i--) {
            if (getWorld()->earthCheck(getX(), i)==true || getWorld()->boulderCheck(getX(), i)==true)
                return false;
        }
        return true;
        break;
    }
}
// Facing Player Check
// Check to see if Protester is currently facing the direction of Tunnelman
bool Protester::facingPlayerCheck(){
    switch (getDirection()) {
            case none:
                return false;
            case up:
                // If facing up, Protester's y-coordinates must be smaller than Tunnelman's
                return getY() <= getWorld()->getPlayer()->getY();
            case left:
            // If facing left, Protester's x-coordinates must be greater than Tunnelman's
                return getX() >= getWorld()->getPlayer()->getX();
            case right:
            // If facing right, Protester's x-coordinates must be smaller than Tunnelman's
                return getX() <= getWorld()->getPlayer()->getX();
            case down:
            // If facing down, Protester's y-coordinates must be greater than Tunnelman's
                return getY() >= getWorld()->getPlayer()->getY();
        }
        return false;
}
// Direction of Player
// Determining which direction Protester has to face to face Tunnelman
GraphObject::Direction Protester::directionToPlayer()
{
    // Get Tunnelman's coordinates
    int X = getWorld()->getPlayer()->getX();
    int Y = getWorld()->getPlayer()->getY();
    // If Tunnelman's exact coordinates match Protester's
    // Return Direction Protester is facing
    if (getX() == X && getY() == Y)
            return getDirection();
    // If X-coordinate is equal and Tunnelman is above Protester
    if (getX() == X && getY() < Y)
        // Face Up
            return up;
    if (getX() > X && getY() == Y)
            return left;
    if (getX() < X && getY() == Y)
            return right;
    if (getX() == X && getY() > Y)
            return down;
    else
            return none;
}
// Random Direction
// Picks a random direction for Protester to Face
GraphObject::Direction Protester::randomDirection()
{
    int r = rand() % 4;
    switch (r) {
        case 0: return up;
        case 1: return left;
        case 2: return right;
        case 3: return down;
    }
    return none;
}
// Move Protester
// Move Protestor in direction it is currently facing
void Protester::moveProtester(Direction direction)
{
    switch (direction) {
        case none:
            return;
        case up:
            if (getDirection() == up) {
                // If reached top border of map, set direction opposite
                if (getY() == 60)
                    setDirection(down);
                if (getWorld()->earthCheck(getX(), getY() + 1) || getWorld()->boulderCheck(getX(), getY() + 1))
                    return;
                else
                // Otherwise move one unit up
                moveTo(getX(), getY() + 1);
            }
            else
                setDirection(up);
            break;
        case left:
            if (getDirection() == left) {
                if (getX() == 0)
                    setDirection(right);
                if (getWorld()->earthCheck(getX()-1, getY()) || getWorld()->boulderCheck(getX()-1, getY()))
                    return;
                else
                    moveTo(getX() - 1, getY());
            }
            else
                setDirection(left);
            break;
        case right:
            if (getDirection() == right) {
                if (getX() == 60)
                    setDirection(left);
                if (getWorld()->earthCheck(getX()+1, getY()) || getWorld()->boulderCheck(getX()+1, getY()))
                    return;
                else
                    moveTo(getX() + 1, getY());
            }
            else
                setDirection(right);
            break;
        
        case down:
            if (getDirection() == down) {
                if (getY() == 0)
                    setDirection(up);
                if (getWorld()->earthCheck(getX(), getY() - 1) || getWorld()->boulderCheck(getX(), getY() - 1))
                    return;
                else
                moveTo(getX(), getY() - 1);
            }
            else
                setDirection(down);
            break;
    }
}
// Bribe: Mark Protester has been bribed with Gold Nugget
void Protester::bribe()
{
    // Play Sound, get 25 points, and set leave field state to true
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    getWorld()->increaseScore(25);
    m_leaveState = true;
}
// Annoyed: deduce HP from Protester
void Protester::annoyed(int hP)
{
    // If Protester is in a leave field state, return
    if(m_leaveState == true)
        return;
    // Decrease HP of protester by amount specified and play noise
    getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
    decreaseHP(hP);
    // Stun State
    m_restingTicks = max(50, 100-(int)getWorld()->getLevel()*10);
    // If HP is completely depleted
    if (getHP() <= 0) {
        // Change Leave Field State to True and play sound
        m_leaveState = true;
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        // Set resting Ticks to 0, so Protester leaves immediately
        m_restingTicks=0;
        // If hit by boulder, award 500 points
        if(hP == 100)
            getWorld()->increaseScore(500);
        // Otherwise, award 100 points
        else
            getWorld()->increaseScore(100);
    }
}
// ---------------------------------------------------------
