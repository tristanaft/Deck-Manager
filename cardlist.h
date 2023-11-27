#ifndef CARDLIST_H
#define CARDLIST_H

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <map>

class cardlist{
public:
    friend void operator>>(cardlist&, cardlist&);
    using deckType = std::map<std::string, int>;
    using entryType = std::pair<std::string, int>;

    //initialize this object either as empty, or with a deckType
    cardlist(): deckText(new deckType) {}
    cardlist(deckType deck):
        deckText(std::make_shared<deckType>(deck)) {}

    //add single card
    void addCard(entryType); 
    void removeCard(const std::string&);
    //how many cards in the list
    int size(); 
    //returns deckType of entries with >= specified value
    deckType findDupes(int); 
    //list out cards in this list
    void view();

    deckType::iterator findCard(std::string&);
    deckType::iterator getEnd(); //get end iterator of deckText
    deckType::iterator getBeg(); //get begin iterator of deckText

    
    std::ofstream& save(std::ofstream&);

private:
    std::shared_ptr<deckType> deckText;
};

#endif