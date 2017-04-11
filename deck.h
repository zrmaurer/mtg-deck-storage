#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include "boost/algorithm/string.hpp"
#include "json/json.h"
#include "database.h"

class Deck
{
  public:
    //constructor
    Deck(std::string);

    //set
    void addCards(std::vector<std::string>, Database);
    void setName(std::string);
    void increment(std::string);


    //get
    void printCards();
    float avgCMC();
    std::string getName(){return name;};

  private:
    Json::Value root;
    std::string name;
};
