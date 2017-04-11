#include "deck.h"

Deck::Deck(std::string  n = "<Insert Name Here>")
{
  name = n;
}
void Deck::addCards(std::vector<std::string> cards,Database db)
{
      /*"Air Elemental":{
      "layout":"normal",
      "name":"Air Elemental",
      "manaCost":"{3}{U}{U}",
      "cmc":5,
      "colors":["Blue"],
      "type":"Creature — Elemental",
      "types":["Creature"],
      "subtypes":["Elemental"],
      "text":"Flying",
      "power":"4",
      "toughness":"4",
      "imageName":"air elemental",
      "colorIdentity":["U"]},
      */
      //std::cout<<cards[1]<<"\n";
      Json::Value database = db.root;
      Json::Value::iterator iter;
      Json::Value tmp;
      for (int i=0;i<cards.size();i++)
      {
        iter = database.begin();
        for (;iter!=database.end();iter++)
        {
          if (boost::iequals((*iter)["name"].asString(),cards[i]))
          {
            //std::cout<<"WO";
            //std::cout<<(*iter)["name"].asString()<<"\n";
            if (root.isMember((*iter)["name"].asString()))
            {
              increment((*iter)["name"].asString());
            }
            else
            {
              tmp = (*iter);
              tmp["count"] = 1;
              root[tmp["name"].asString()] = tmp;
            }
          }
        }
      }
}
void Deck::increment(std::string n)
{
  root[n]["count"]= root[n]["count"].asInt()+1;
}
void Deck::printCards()
{
  std::cout<<name<<"-------\n";
  Json::Value::iterator iter = root.begin();
  for(;iter!=root.end();iter++)
  {
    std::cout<<"Count: "<<(*iter)["count"]<<"; "<<(*iter)["name"]<<"\n";
  }
}
float Deck::avgCMC()
{
  Json::Value::iterator iter;
  float avg = 0;
  for(iter=root.begin();iter!=root.end();iter++)
  {
    avg+=(*iter)["cmc"].asInt();
  }

  return avg/root.size();
}
