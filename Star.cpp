#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Star.h"

Star::Star(const std::vector<std::string> &data, int ID) {
  data_.push_back(std::to_string(ID + 1));
  for (auto d : data)
    data_.push_back(d);
}

Star::~Star()
{
}

std::vector<std::string> Star::getVector(void) {
  return data_;
}

std::string Star::getID(void) {
  return data_.front();
}

bool operator==(Star &l, Star &r) {
  return l.getID() == r.getID();
}
 
