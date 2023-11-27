#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <map>

class decklist{
public:
    //using deckType = std::vector<std::pair<int,std::string>>;
    using deckType = std::map<std::string, int>;
    using entryType = std::pair<std::string, int>;
    //entries in the form of "Fury Sliver", 1


    //initializers
    //default initializer
    decklist(): format("Standard"), inCollection(false),
        deckText(new deckType) {}
    //can pass deck to convert to decklist type
    decklist(deckType& deck): format("Standard"), inCollection(false),
    deckText(std::make_shared<deckType>(deck)) {}
    decklist(deckType& deck, std::string frm, bool inColl):
    format(frm), inCollection(inColl), deckText(std::make_shared<deckType>(deck)) {}
    decklist(std::string& filename): format("Standard"), inCollection(false),
        deckText(new deckType) {load(filename);} //this is to load from file.

    //properties
    deckType findDupes(int);
    bool isValid(); //check if the given deck is valid
    int size(); //how many cards in the deck
    std::string getCommander() {return commander;}
    void setCommander(std::string); //this is a bit more complicated than format
    std::string getFormat() {return format;};
    void setFormat(std::string f) {this->format = f;}
    

    //management
    void view();
    void addCard(entryType); //add single card
    void load(std::string&);
    void addToCollection(); //add this deck to the collection
    void save(); //save to decklists folder
    


private:
    std::shared_ptr<deckType> deckText;
    std::string format;
    std::string commander;
    bool inCollection;
    


};