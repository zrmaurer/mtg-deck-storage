#include "deck.h"

Deck::Deck()
{
    count = 0;
}
void Deck::clear()
{
  root.clear();
}
float Deck::getPercent(char color)
{
  float result=0;
  Json::Value::iterator iter = root.begin();
  for(;iter!=root.end();iter++)
  {

    Json::Value::iterator c_it = (*iter)["colors"].begin();
    for (;c_it!=(*iter)["colors"].end();c_it++)
    {
      if ((*c_it).asString()[2] == 'u' && color=='U')
      {
        result+=(*iter)["count"].asInt();
      }
      else if ((*c_it).asString()[0] == color)
      {

        result+=(*iter)["count"].asInt();
      }
    }
  }
  result = result/count;
  return result*100;
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
      Json::Value database = db.root;
      Json::Value::iterator iter;
      Json::Value tmp;
      for (unsigned int i=0;i<cards.size();i++)
      {
        iter = database.begin();
        for (;iter!=database.end();iter++)
        {
          if (boost::iequals((*iter)["name"].asString(),cards[i]))
          {
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

            count++;

          }
        }
      }
}
void Deck::increment(std::string n)
{
  root[n]["count"]= root[n]["count"].asInt()+1;
}
void Deck::saveDeck(std::string fname)
{
  std::ofstream ofs;
  ofs.open(fname);

  Json::Value::iterator iter = root.begin();
  for(;iter!=root.end();iter++)
  {
    ofs<<(*iter)["count"].asInt()<<" "<<(*iter)["name"].asString()<<"\n";
  }
  ofs.close();

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
