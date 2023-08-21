//
//  Game.hpp
//  cs32p1
//
//  Created by Aaron Kuo on 4/4/21.
//

#ifndef Game_h
#define Game_h
class City;
class History;
class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();

        // Mutators
    void play();

  private:
    City* m_city;
    History* mHistory;
};

#endif /* Game_hpp */
