
#include "StudentWorld.h"
#include "Actor.h"
#include "GraphObject.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;
// Create New World
GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}
// Constructor
StudentWorld::StudentWorld(std::string assetDir)
    : GameWorld(assetDir),firstTic(true), ticksPassed(0), m_protesters(0), m_player(nullptr), numBarrels(0)
{}
// Destructor
// CleanUp will take the function of a destructor
StudentWorld::~StudentWorld()
{
    cleanUp();
}
// Get Functions
// Return m_player
Tunnelman* StudentWorld::getPlayer()
{
    return m_player;
}
// Return Number of Barrels Left in Game
int StudentWorld::getBarrelsLeft()
{
    int counter = 0;
    vector<Actor*>::iterator it;
    it = m_actor.begin();
    while (it != m_actor.end())
    {
        if ((*it)->getID() == TID_BARREL)
        counter++;
        it++;
    }
    return counter;
}
// Decrease Functions
// Decrease Number of Barrels
void StudentWorld::decreaseBarrel()
{
    numBarrels--;
}
// Decrease Number of Protesters
void StudentWorld::decreaseProtester()
{
    m_protesters--;
}
//Checks
// Above Check: Check to see if boulder is currently above Earth
bool StudentWorld::aboveCheck(int x, int y)
{
    int k = x + 4;
    for (int i = x; i < k; i++)
    {
        // If there is Earth beneath boulder, return true
        if (m_Earth[i][y] != nullptr)
            return true;
    }
    // If none, return false
    return false;
}
// Earth Check
// Check if there is Earth in selected coordinates
bool StudentWorld::earthCheck(int x, int y)
{
    int k = x + 4;
    for (int i = x; i < k; i++) {
        for (int j = y; j < k; j++) {
            // If there is Earth, return true
            if (m_Earth[i][j] != nullptr)
                return true;
        }
    }
    // If not, return false
    return false;
}
// Boulder Check
// Check if there is a boulder in surrounding radius of given coordinates
bool StudentWorld::boulderCheck(int x, int y,int radius)
{
    vector<Actor*>::iterator it;
    for (it = m_actor.begin(); it != m_actor.end(); it++) {
        // Look for Boulder ID
        if ((*it)->getID() == TID_BOULDER)
            // Check to see if coordinates is within radius
            if(radiusCheck(x,y,(*it)->getX(),(*it)->getY(), radius))
            return true;
    }
    return false;
}
// Radius Check
bool StudentWorld::radiusCheck(int x, int y, int x1, int y1, int radius)
{
    // Use Radius Equation to check if Coordinates Fall Under Range
    if (pow((x-x1),2) + pow((y-y1),2) <= pow(radius,2))
        return true;
    else
        return false;
}
// Player Radius Check
// Inserting Player Coordinates to check its surrounding Radius
bool StudentWorld::playerRadiusCheck(Actor *actor, int radius){
    return radiusCheck(actor->getX(), actor->getY(), m_player->getX(), m_player->getY(), radius);
}
// Direction Check:
// Checks to see if the specified direction is free of obstacles
bool StudentWorld::directionCheck(int x,int y, GraphObject::Direction direction)
{
    switch (direction) {
    case GraphObject::none:
            return false;
            // return true if no earth or boulders in the up direction
    case GraphObject::up:
        return (earthCheck(x, y+1)==false && boulderCheck(x, y+1)==false && y != 60);
            // return true if no earth or boulders in the left direction
    case GraphObject::left:
        return (earthCheck(x-1,y)==false && boulderCheck(x,y)==false && x!= 0);
            // return true if no earth or boulders in the right direction
    case GraphObject::right:
        return (earthCheck(x+1, y)==false && boulderCheck(x+1, y)==false && x!= 60);
            // return true if no earth or boulders in the down direction
    case GraphObject::down:
        return (earthCheck(x, y-1) == false && !boulderCheck(x, y-1) == false && y!= 0);
    }
    return false;
}
// Dig
// Dig through Earth, set each Earth element to invisible
bool StudentWorld::dig(int x, int y) {
   bool check = false;
    // For specificed 4x4 area, remove the Earth element
        for (int i = x; i < x + 4; i++){
            for (int j = y; j < y + 4; j++)
            {
                if (m_Earth[i][j] != nullptr)
                {
                    // play digging sound, remove Earth
                    playSound(SOUND_DIG);
                    m_Earth[i][j] = nullptr;
                    check = true;
                }
            }
        }
    // Return True once digging is done
        return check;
}
// Add Actors
void StudentWorld::addActor(Actor* actor) {
    m_actor.push_back(actor);
}
// Add Barrels Into Game
void StudentWorld::addBarrel(){
    int x, y;
    int num = min( 2 + (int)getLevel(), 21);
    for (int i = 0; i < num; i++) {
        do {
            // Add Barrels in certain coordinates in Map
            x = rand() % 60 + 1;
            y = rand() % 56 + 1;
        } while ((x > 26 && x < 34 && y>0));
        // While Avoiding the Center Tunnel, add Barrels
        addActor(new oilBarrel(this, x, y));
        numBarrels++;
    }
}
// Add Boulders in Game
void StudentWorld::addBoulder(){
    int x, y;
    int num = min((int)getLevel()/2 + 2, 9);;
    for (int i = 0; i < num; i++) {
        do {
            // Add Boulders in certain coordinates in Map
            x = rand() % 60 + 1;
            y = rand() % 36 + 20;
        } while ((x > 26 && x < 34 && y>0));
        // While Avoiding the Center Tunnel, add Boulders
        addActor(new Boulders(this, x, y));
    }
}
// Add Gold in Game
void StudentWorld::addGold(){
    int x, y;
    int num = max((int)getLevel()/2, 2);
    for (int i = 0; i < num; i++) {
        do {
            // Add Barrels in certain coordinates in Map
            x = rand() % 60 + 1;
            y = rand() % 56 + 1;
        } while ((x > 26 && x < 34 && y>0));
        // While Avoiding the Center Tunnel, add Gold
        addActor(new goldNugget(this, x, y, false, true));
    }
}
// Add Sonar Kit or Water
void StudentWorld::addSonarOrWater(){
    int x, y;
    int g = 1;
    int G = ((int)getLevel()*25) + 300;
    if (rand()%G == g)
       {
           // 20% Chance of Adding Sonar Kit
           if (rand() % 5 == 1)
           {
               int val = 300 - 10 * getLevel();
               // Determines the amount of Ticks the Water Pool will last
               int T = max(100, val);
               // Add Sonar Kit to Game
               Actor *actor = new sonarKit(this, 0, 60, T);
               addActor(actor);
           }
           // 80% Chance of Adding Water Pool
           else
           {
               // Randomizing Location
               x = rand() % 56;
               y = rand() % 56;
               // Only allowed to add to open area with no Earth
               while (earthCheck(x, y) == false)
               {
                   x = rand() % 56;
                   y = rand() % 56;
               }
               int val = 300 - 10 * getLevel();
               // Determines the amount of Ticks the Water Pool will last
               int T = max(100, val);
               // Add Water Pool to Game
               Actor *actor = new waterPool(this,x,y,T);
               addActor(actor);
           }
       }
}
void StudentWorld::addProtestor()
{
    int T = max(25, 200 - (int)getLevel());
    int P = fmin(15, 2 + getLevel() * 1.5);

    if (firstTic || (ticksPassed > T && m_protesters < P)) {
 
    addActor(new Protester(this));
        ticksPassed = 0;
        m_protesters++;
        firstTic = false;
    }
    ticksPassed++;
}



// Init
int StudentWorld::init()
{
    // Reset All Variables Back to 0
    numBarrels = 0;
    firstTic = true;
    ticksPassed = 0;
    m_protesters = 0;
    // Create Oil Field
    for (int x = 0; x < 64 ; x++)
    {
        for (int y = 0;  y<60; y++)
        {
            // Avoiding the Center Tunnel, Add Earth
            if(x < 30||x > 33||y < 4)
            m_Earth[x][y] = std::unique_ptr<Earth>(new Earth(this, x, y));
        }
    }
    // Create New Player
    m_player = new Tunnelman(this);
    // Add Permanent Objects
    addBarrel();
    addBoulder();
    addGold();
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    setDisplayText();

    vector<Actor*>::iterator it;
    // While Tunnelman is Alive, ask all actors to do Something
        for (it = m_actor.begin(); it!=m_actor.end(); it++) {
            if ((*it)->isAlive()) {
                (*it)->doSomething();
            }
            // If Tunnelman has died, return Player Had Died
            if (m_player->isAlive()==false) {
                decLives(); //from GameWorld Class
                return GWSTATUS_PLAYER_DIED;
            }
            // If All Barrels have been Collected, return Level Finsihed
            if (numBarrels == 0) {
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
        // Player makes move
        m_player->doSomething();
        // Add in Temporary Objects
        addSonarOrWater();
        addProtestor();
        // Delete All Actors who have Died
        for (it = m_actor.begin(); it != m_actor.end();) {
            if ((*it)->isAlive()==false) {
                delete *it;
                it = m_actor.erase(it);
            }
            else it++;
        }
   return GWSTATUS_CONTINUE_GAME;
}
// Clean Up
// Basically the destructor
void StudentWorld::cleanUp()
{
    // Delete All Earth Elements
        for (int i = 0; i < 60; i++)
        {
            for (int j = 0; j < 64; j++)
            {
                if (m_Earth[i][j] != nullptr)
                    m_Earth[i][j].reset();
            }
        }
    // Delete Player
    delete m_player;
    // Delete All Actors
        vector<Actor*>::iterator it = m_actor.begin();
        while (it != m_actor.end()) {
            delete *it;
            it = m_actor.erase(it);
        }
}
// Display Game Stats
void StudentWorld::setDisplayText()
{
    int level = getLevel();
    int lives = getLives();
    int health = m_player->getHP();
    int squirts = m_player->getSquirts();
    int gold = m_player->getGold();
    int barrelsLeft = getBarrelsLeft();
    int sonar = m_player->getSonar();
    int score = getScore();
    string stats = formatDisplay(level, lives, health, squirts, gold, barrelsLeft, sonar, score);
    setGameStatText(stats);
}
// Display Format
string StudentWorld::formatDisplay(int level, int lives, int health, int squirt, int gold, int barrelsLeft, int sonar, int score)
{
    ostringstream oss;
    oss <<  "Lvl: " << setw(2) << level << "  ";
    oss <<  "Lives: " << setw(1) << lives << "  ";
    oss <<  "Hlth: " << setw(3) << health*10 << "%" << "  ";
    oss <<  "Wtr: " << setw(2) << squirt << "  ";
    oss <<  "Gld: " << setw(2) << gold << "  ";
    oss <<  "Oil Left: " << setw(2) << barrelsLeft << "  ";
    oss <<  "Sonar: " << setw(2) << sonar << "  ";
    oss.fill('0');
    oss <<  "Scr: " << setw(6) << score << "  ";
    string stats = oss.str();
    return stats;
}
// Exit
// Once protestor is in leave field mode, it will naviagte its way out of the Game
// as efficiently as possible
void StudentWorld::exit(Protester * protestor)
{
    // Define map
    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++){
            m_map[i][j]=0;
        }
    }
    int xc = protestor->getX();
    int yc = protestor->getY();
    queue<Grid> temp;
    temp.push(Grid(60,60));
     m_map[60][60] = 1;
    while (temp.empty() == false) {
        Grid c = temp.front();
        temp.pop();
        
        int x=c.x;
        int y=c.y;

        // UP
        if(directionCheck(x,y, GraphObject::up)&& m_map[x][y+1]==0){
            temp.push(Grid(x,y+1));
            m_map[x][y+1] = m_map[x][y]+1;
        }
        // LEFT
        if(directionCheck(x,y, GraphObject::left)&& m_map[x-1][y]==0){
            temp.push(Grid(x-1,y));
            m_map[x-1][y] = m_map[x][y]+1;
        }
        // RIGHT
        if(directionCheck(x,y, GraphObject::right)&& m_map[x+1][y]==0){
            temp.push(Grid(x+1,y));
            m_map[x+1][y] = m_map[x][y]+1;
        }
        // DOWN
        if(directionCheck(x,y, GraphObject::down)&& m_map[x][y-1]==0){
            temp.push(Grid(x,y-1));
            m_map[x][y-1] = m_map[x][y]+1;
        }
    }
    // Move UP
    if(directionCheck(xc,yc, GraphObject::up)&& m_map[xc][yc+1]<m_map[xc][yc])
        protestor->moveProtester(GraphObject::up);
    // Move LEFT
    if(directionCheck(xc,yc, GraphObject::left)&& m_map[xc-1][yc]<m_map[xc][yc])
        protestor->moveProtester(GraphObject::left);
    // Move RIGHT
    if(directionCheck(xc,yc, GraphObject::right)&& m_map[xc+1][yc]<m_map[xc][yc])
        protestor->moveProtester(GraphObject::right);
    // Move DOWN
    if(directionCheck(xc,yc, GraphObject::down)&&m_map[xc][yc-1]<m_map[xc][yc])
        protestor->moveProtester(GraphObject::down);
    return;
}
Protester* StudentWorld::protesterRadiusCheck(Actor* actor, int radius)
{
    vector<Actor*>::iterator it;
    for (it = m_actor.begin(); it != m_actor.end(); it++) {
            if (radiusCheck(actor->getX(), actor->getY(),(*it)->getX(), (*it)->getY(), radius))
                return dynamic_cast <Protester*> (*it);
    }
    return nullptr;
}
