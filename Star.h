#ifndef ASTRODATABASE_STAR_H
#define ASTRODATABASE_STAR_H

#include <iostream>
#include <string>
#include <vector>

struct coordinate {
    double x, y, z;
};

std::ostream & operator<<(std::ostream &, coordinate &);

void addStarToFile(void);

class Star {
private:
  std::vector<std::string> data_;


public:
    Star(const std::vector<std::string> &, int);
    ~Star();

    std::vector<std::string> getVector(void); 
    std::string getID(void);

    friend bool operator==(Star &, Star &);
};


#endif //ASTRODATABASE_STAR_H
