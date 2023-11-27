#ifndef COLLECTION_H
#define COLLECTION_H

#include "cardlist.h"
#include "deck.h"
#include <string>

//not sure why we have to declare deck when we included it...
class deck;


class collection: public cardlist {
    friend class deck;
    friend void handleHeaders(std::ifstream&, collection&);
private:
    std::string title = "Untitled";
    std::vector<std::string> includedDecklists;

public:

    //initializers:
    //default
    collection() = default;
    //give collection, just initializes cardlist
    collection(collection& col): cardlist(col) {}
    //init with filename
    collection(std::string& filename) {load(filename);};

    std::string getTitle() {return title;}
    void setTitle(std::string t) {this->title = t;}

    void view();
    void load(std::string&);
    std::ofstream& save(std::ofstream&);
    void addDeck(deck&);

};

#endif