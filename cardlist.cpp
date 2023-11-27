#include "cardlist.h"
#include <set>
#include <string>
#include <iostream>
#include <fstream>


bool isDupe(cardlist::entryType entry, int maxCount){
    //int count = entry.second;
    //std::string cardname = entry.first;
    std::set<std::string> basicTypes = 
    {"Plains", "Island", "Swamp", "Mountain", "Forest"};
    //you can have as many basic lands as you want.
    //std::cout << cardname << " " << basicTypes.count(cardname) << std::endl;
    
    if(entry.second >= maxCount){
        if(basicTypes.count(entry.first) >= 1){
        //std::cout << "FOUND A BASIC!!!!!" << std::endl;
        //if you are a basic land, this doesn't count as a dupe
        return false;
        }else{
            return true;
        }

    }else{
        return false;
    }
    
    
}

//dupes for duplicates, but it also means some arbitrary number of copies
//returns a sub deck of just the cards with X copies or more
//basics excluded
cardlist::deckType cardlist::findDupes(int maxCount){
    //using namespace std::placeholders;
    deckType dupesList; //not a list, but a deck of dupes
    auto beg = deckText->begin();
    auto end = deckText->end();
    auto crit = std::bind(isDupe, std::placeholders::_1, maxCount);
    //auto crit = [&](cardlist::entryType e){return isDupe(e,maxCount);};
    //iterate through the pairs in deckText,
    //see if we find any entries
    auto dupes = beg;
    while((dupes=std::find_if(dupes, end, crit)) != deckText->end()){
        dupesList.insert(*dupes);
        //std::cout << dupes->first << std::endl;
        ++dupes;
        
    }
    
    //if dupes is not the end, then we have hit one

    return dupesList;
}


int  cardlist::size(){ //how many cards in the deck
    int sz = 0;
    for(auto p : *deckText){
        sz += p.second;
    }
    return sz;
}

void cardlist::addCard(entryType entry){
    //std::cout << "adding card..." << "\n";
    std::string cardName = entry.first;
    auto deckEntry = deckText->find(cardName);
    //std::cout << "setting up iterator..." << "\n";
    if(deckEntry != deckText->end()){
        //this card is in the deck text already
        //std::cout << "entry exists" << "\n";
        deckEntry->second += entry.second;
        //std::cout << "entry incremented" << "\n";
    }else{
        //std::cout << "inserting entry" << "\n";
        deckText->insert(entry);
        //std::cout << "entry inserted" << "\n";
    }
    //if(deckText->find())
}

void cardlist::removeCard(const std::string& cardName){
    auto deckEntry = deckText->find(cardName);
    if(deckEntry != deckText->end()){
        if(deckEntry->second == 1){
            deckText->erase(deckEntry);
        }
        else{ //have more than just one card there, so decrement
            deckEntry->second--;
        }
    }else{
        std::cout << cardName << " not found." << std::endl;
        //std::cout << "inserting entry" << "\n";
        //deckText->insert(entry);
        //std::cout << "entry inserted" << "\n";
    }
    //if(deckText->find())

    //try to find the corresponding card in the map.
}

void cardlist::view(){
    for(auto e : *deckText){
        std::cout << e.second << " " << e.first << "\n";
    }
    //std::cout << std::endl;
}

std::ofstream& cardlist::save(std::ofstream& file){
    for(auto e : *deckText){
        file << e.second << " " << e.first << "\n";
    }
    //std::cout << std::endl;
    return file;
}

cardlist::deckType::iterator cardlist::findCard(std::string& cardname){
    return (deckText->find(cardname));
}

cardlist::deckType::iterator cardlist::getBeg() {
    return (deckText->begin());
}

cardlist::deckType::iterator cardlist::getEnd() {
    return (deckText->end());
}

//copy all cards in list from lhs to rhs
void operator>>(cardlist& lhs, cardlist& rhs){
    auto beg = lhs.getBeg();
    auto end = lhs.getEnd();
    for(;beg != end; ++beg){
        rhs.addCard(*beg);
    }
}
