//
//  Flatulan.hpp
//  cs32p1
//
//  Created by Aaron Kuo on 4/4/21.
//

#ifndef Flatulan_h
#define Flatulan_h

class City;

class Flatulan
{
  public:
        // Constructor
    Flatulan(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    bool haveIBeenConverted() const;

        // Mutators
    void move();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};

#endif /* Flatulan_hpp */
