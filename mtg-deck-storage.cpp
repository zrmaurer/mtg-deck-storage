#include <iostream>
#include <fstream>
#include <gtk/gtk.h>
#include <vector>
#include "json/json.h"

#include "database.h"
#include "deck.h"

/*static void activate (GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "MTG Deck Storage");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 800);
  //Show ALL
  gtk_widget_show_all (window);

}
*/
int main (int argc, char **argv)
{

  //Opening Database
  //Database data = Database("testCards.json");
  Database data = Database("AllCards.json");

  //Test Deck building
  std::vector<std::string> deck_string =
  {
    "Treasure Hunt",
    "Treasure Hunt",
    "Treasure Hunt",
    "Treasure Hunt",
    "Zombie Infestation",
    "Zombie Infestation",
    "Dismal Backwater",
    "Dismal Backwater",
    "Dismal Backwater",
    "Faerie Conclave",
    "Faerie Conclave",
    "Faerie Conclave",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Island",
    "Reliquary Tower",
    "Reliquary Tower",
    "Reliquary Tower",
    "Reliquary Tower",


  };

  Deck deck = Deck("Zombie Hunt");
  deck.addCards(deck_string,data);
  deck.printCards();
  std::cout<<"Average CMC: "<<deck.avgCMC()<<"\n";
  /*GtkApplication *app;
  int status;

  app = gtk_application_new ("com.github.zrmaurer.mtgdeckstorage", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;*/


  //Text Based




  return 0;
}
