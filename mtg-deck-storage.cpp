#include <iostream>
#include <gtk/gtk.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <gtkmm.h>

#include "json/json.h"

#include "database.h"
#include "deck.h"


Glib::ustring filename;
Glib::RefPtr<Gtk::ListStore> treeModel;
Glib::RefPtr<Gtk::ListStore> statsModel;
Glib::RefPtr<Gtk::ListStore> cmcModel;
Gtk::Window* window;
//Gtk::Image* image_card;
Glib::RefPtr<Gtk::TextBuffer>statsBuff;
//Glib::RefPtr<Gtk::TreeSelection>tSelection;
Database data;
Deck d;

class Cols: public Gtk::TreeModel::ColumnRecord {
    public:
        Cols() {
            this->add(this->colA);
            this->add(this->colB);
            this->add(this->colC);
            this->add(this->colD);
        }
        Gtk::TreeModelColumn<gint> colA;
        Gtk::TreeModelColumn<Glib::ustring> colB;
        Gtk::TreeModelColumn<gint> colC;
        Gtk::TreeModelColumn<Glib::ustring> colD;
};
class statCols: public Gtk::TreeModel::ColumnRecord {
      public:
          statCols() {
              this->add(this->colA);
              this->add(this->colB);
          }

          Gtk::TreeModelColumn<Glib::ustring> colA;
          Gtk::TreeModelColumn<gfloat> colB;
};

class cmcCols: public Gtk::TreeModel::ColumnRecord {
      public:
          cmcCols() {
              this->add(this->colA);
              this->add(this->colB);
          }
          Gtk::TreeModelColumn<Glib::ustring> colA;
          Gtk::TreeModelColumn<gint> colB;
};
void quit_prog()
{
  Gtk::Main::quit();
}
void display_deck(Deck d)
{
  treeModel->clear();
  Json::Value::iterator iter = d.begin();
  Cols mycols;
  std::vector<gint> costs(8, 0);
  for(;iter!=d.end();iter++)
  {
    auto row = *(treeModel->append());


    Glib::ustring name = (*iter)["name"].asString();
    gint count = (*iter)["count"].asInt();
    gint cmc = (*iter)["cmc"].asInt();
    Glib::ustring color;
    char c;

    if ((*iter)["colors"].size()==0)
    {
      color = "Colorless";
    }
    else if ((*iter)["colors"].size() == 1)
    {
      Json::Value::iterator c_it = (*iter)["colors"].begin();
      if ((*c_it).asString()[2] == 'u')
      {
        c = 'U';
      }
      else
      {
        c = (*c_it).asString()[0];
      }

      switch (c)
      {
        case 'W':
          color = "White";
        break;
        case 'U':
          color = "Blue";
        break;
        case 'B':
          color = "Black";
        break;
        case 'R':
          color = "Red";
        break;
        case 'G':
          color = "Green";
        break;

        default:
          color = "Colorless";
      }
    }
    else
    {
      color = "Multicolored";
    }

    row[mycols.colA] = count;
    row[mycols.colB] = name;
    row[mycols.colC] = cmc;
    row[mycols.colD] = color;

    if(cmc>7)
    {
      cmc = 7;
    }
    costs[cmc]+=count;

  }
  cmcModel->clear();
  cmcCols cCols;
  std::ostringstream ssInt;
  for(int i=0;i<7;i++)
  {
    auto row = *(cmcModel->append());
    ssInt.str(std::string());
    ssInt.clear();

    ssInt<<i;
    row[cCols.colA] = Glib::ustring(ssInt.str());
    row[cCols.colB] = costs[i];
  }
  auto row = *(cmcModel->append());
  row[cCols.colA] = "7+";
  row[cCols.colB] = costs[7];
}
std::vector<std::string> openDeck(std::string fname)
{
  std::ifstream f;
  std::vector<std::string> deckVect;
  std::string card;
  std::string line;
  std::string temp;
  int count;
  f.open(fname);

  while(getline(f,line))
  {
    card = "";
    std::istringstream iss(line);
    iss>>count;
    while(iss>>temp)
    {
      card+=(" "+temp);
    }
    card.erase(0,1);
    for(int i=0;i<count;i++)
    {

      deckVect.push_back(card);
    }
  }

  f.close();
  return deckVect;
}
#if 0
void save_as()
{
  //
    Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*window);

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Save", Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:

    auto filter_deck = Gtk::FileFilter::create();
    filter_deck->set_name("deck files");
    filter_deck->add_mime_type("text/deck");
    dialog.add_filter(filter_deck);

    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    dialog.add_filter(filter_text);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

  //


  int result = dialog.run();

  switch (result)
  {
    case(Gtk::RESPONSE_OK):
    {

      d.saveDeck(dialog.get_filename());
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      return;
      break;
    }
    default:
    {
      return;
      break;
    }
  }

}

void save()
{
  if (filename ==NULL)
  {
    save_as();
    return;
  }
  else
  {
    d.saveDeck(filename);
  }
}
#endif

void display_stats(Deck d)
{

  std::ostringstream txtStream;
  txtStream<<"Average CMC = ";
  txtStream<<d.avgCMC();
  txtStream<<"\n";
  txtStream<<"Total Cards: ";
  txtStream<<d.getCount();
  txtStream<<"\nColor Breakdown:";
  Glib::ustring average = txtStream.str();

  statsBuff->set_text(average);
  Gtk::TreeModel::Children children = statsModel->children();
  Glib::ustring color;
  statCols sCols;
  char c;


  for(Gtk::TreeModel::Children::iterator iter = children.begin(); iter != children.end(); ++iter)
  {

    auto row = (*iter);
    color = row[sCols.colA];
    if (color[2] == 'u')
    {
      c = 'U';
    }
    else
    {
      c = color[0];
    }

    row[sCols.colB] = gfloat(d.getPercent(c));
  }

}


void open_and_display()
{
    Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*window);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    /*auto filter_deck = Gtk::FileFilter::create();
    filter_deck->set_name("deck files");
    filter_deck->add_mime_type("text/x-deck");
    dialog.add_filter(filter_deck);*/

    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    dialog.add_filter(filter_text);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);


  int result = dialog.run();

  switch (result)
  {
    case(Gtk::RESPONSE_OK):
    {

      filename = dialog.get_filename();
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      return;
      break;
    }
    default:
    {
      return;
      break;
    }
  }

  d.clear();
  d.addCards(openDeck(filename),data);

  display_deck(d);
  display_stats(d);

}
#if 0
void change_image(Glib::ustring name)
{
  Glib::RefPtr<Gdk::Pixbuf> pix;
  pix = Gdk::Pixbuf::create_from_file("test_image.jpg");
  //Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file
  image_card->set(pix);
}
void card_change()
{
  Gtk::TreeModel::iterator sRow = tSelection->get_selected();
  Gtk::TreeModel::Row row = *sRow;
  Cols myCols;
  Glib::ustring name = row[myCols.colB];

  change_image(name);

}
#endif
int main (int argc, char **argv)
{

  //Opening Database
  data.getData("AllCards.json");

  //GTK MM
  Gtk::Main kit(argc, argv);
  auto refBuilder = Gtk::Builder::create();
    try
    {
      refBuilder->add_from_file("ui_glade.glade");
    }
    catch(const Glib::FileError& ex)
    {
      std::cerr << "FileError: " << ex.what() << std::endl;
      return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
      std::cerr << "MarkupError: " << ex.what() << std::endl;
      return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
      std::cerr << "BuilderError: " << ex.what() << std::endl;
      return 1;
    }
    Gtk::ScrolledWindow* s_window;
    Gtk::TreeView* treeView;
    Gtk::ImageMenuItem* menu_open;
    Gtk::ImageMenuItem* menu_quit;
    //Gtk::ImageMenuItem* menu_save_as;
    //Gtk::ImageMenuItem* menu_save;
    refBuilder->get_widget("window_main",window);

    //Setup Deck View
    refBuilder->get_widget("scrolledwindow",s_window);
    refBuilder->get_widget("treeView",treeView);
    treeModel = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(refBuilder->get_object("deck_store"));

    //tSelection = Glib::RefPtr<Gtk::TreeSelection>::cast_dynamic(refBuilder->get_object("tree_selection_cards"));
    //tSelection->signal_changed().connect(sigc::ptr_fun(&card_change));

    statsModel = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(refBuilder->get_object("stats_store"));
    statsBuff = Glib::RefPtr<Gtk::TextBuffer>::cast_dynamic(refBuilder->get_object("stats_buff"));
    cmcModel = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(refBuilder->get_object("cmc_store"));

    //refBuilder->get_widget("image_card",image_card);

    //Set Dialogs and Menu

    refBuilder->get_widget("menu_quit",menu_quit);
    menu_quit->signal_activate().connect(sigc::ptr_fun(&quit_prog));

    refBuilder->get_widget("menu_open",menu_open);
    menu_open->signal_activate().connect(sigc::ptr_fun(&open_and_display));

    /*refBuilder->get_widget("menu_save_as",menu_save_as);
    menu_open->signal_activate().connect(sigc::ptr_fun(&save_as));

    refBuilder->get_widget("menu_save",menu_save);
    menu_open->signal_activate().connect(sigc::ptr_fun(&save));*/

    //Open Window
    Gtk::Main::run(*window);
  return 0;

}
