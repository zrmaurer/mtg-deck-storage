#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "boost/algorithm/string.hpp"
#include "json/json.h"


class Database
{
  public:
    Database();
    void getData(std::string);
    bool verify(std::vector<std::string>);
    Json::Value root;
};
