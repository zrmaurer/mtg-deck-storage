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
    Deck();

    //set
    void addCards(std::vector<std::string>, Database);
    //void setName(std::string);
    void increment(std::string);
    void clear();

    //get
    void printCards();
    float avgCMC();
    float getPercent(char);
    int getCount(){return count;}
    Json::Value::iterator begin(){return root.begin();}
    Json::Value::iterator end(){return root.end();}
    //std::string getName(){return name;};


    //Other Functions
    void saveDeck(std::string);
  private:
    Json::Value root;
    int count;
    std::string name;
};
