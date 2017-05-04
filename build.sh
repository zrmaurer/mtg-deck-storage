g++ -Wall -std=c++11 -g `pkg-config --cflags gtk+-3.0` jsoncpp.cpp mtg-deck-storage.cpp database.cpp deck.cpp -o mtg-deck-storage `pkg-config --libs gtk+-3.0` `pkg-config gtkmm-3.0 --cflags --libs`
