#ifndef DECK_H
#define DECK_H

#include "cardlist.h"
#include "collection.h"

class deck: public cardlist{
    friend class collection;
    friend void handleHeaders(std::ifstream&, deck&);
private:
    std::string title = "Untitled";
    std::string format = std::string();
    std::string commander = std::string();
    std::vector<std::string> collVec; //contained in THESE collections.
    //bool inCollection = false;

public:

    //initializers:
    //default
    deck() = default;
    //give deckType, just initializes cardlist
    deck(deckType& dt): cardlist(dt) {}
    //init with filename
    deck(std::string& filename) {load(filename);};
    

    //properties
    bool isValid(); //check if the given deck is valid (complicated)
    std::string getCommander() {return commander;}
    void setCommander(std::string); //this is a bit more complicated than format
    std::string getFormat() {return format;};
    void setFormat(std::string f) {this->format = f;}
    std::string getTitle() {return title;}
    void setTitle(std::string t) {this->title = t;}
    void viewCollections(); //print all collections this is in

    //management
    void view();
    void load(std::string&);
    std::ofstream& save(std::ofstream&); //save to decklists folder
    //to simplify, I will try just having collections
    //manage adding decks.
    //void addToCollection(collection&); //add this deck to the collection
    


};
#endif