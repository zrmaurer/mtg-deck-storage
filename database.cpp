#include "database.h"
Database::Database()
{

}
void Database::getData(std::string f)
{
  //Opening File
  std::ifstream IN;
  IN.open(f);
  if (!IN.is_open())
  {
    throw std::invalid_argument("ERROR: Failed to open card database");
  }
  //Puting file into database
  IN>>root;
  //Close File
  IN.close();

}
bool Database::verify(std::vector<std::string> v)
{
  bool check;
  Json::Value::iterator iter = root.begin();
  for (unsigned int i=0;i<v.size();i++)
  {
    check = false;
    for (;iter!=root.end();iter++)
    {
      if (boost::iequals((*iter)["name"].asString(),v[i]))
      {
        check = true;
      }
    }
    if (check ==false)
    {
      return false;
    }
  }
  return true;
}
