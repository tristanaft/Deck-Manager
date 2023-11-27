#include "decklist.h"

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <set>
#include <fstream>

//properties
bool decklist::isValid(){//check if the given deck is valid
    bool isv = true;
    if(format == "Standard" || format == "Commander"){
        if(format == "Standard"){
            //needs greater than 60 cards
            if(this->size() < 60){
                std::cout << "Too few cards for standard deck." << std::endl;
                isv = false;
            }
            //needs no more than 4 cards of each name,
            //except for basic land cards...
            auto dupesList = this->findDupes(4);
            if(dupesList.size() > 0){
                std::cout << "Contains >4 of: " << std::endl;

                for(auto entry : dupesList){
                    std::cout <<"   "<< entry.first << std::endl;
                }
                isv = false;
            }
        }
        if(format == "Commander"){
            //needs greater than 100 cards
            if(this->size() < 100){
                std::cout << "Too few cards for commander deck." << std::endl;
                isv = false;
            }
            //needs no more than 1 cards of each name,
            //except for basic land cards...
            auto dupesList = this->findDupes(2);
            if(dupesList.size() > 0){
                std::cout << "Contains >1 of: " << std::endl;

                for(auto entry : dupesList){
                    std::cout <<"   "<< entry.first << std::endl;
                }
                isv = false;
            }
        }
    }else{
        std::cout << "Unrecognized format." << std::endl;
        isv = false;
    }
    return isv;
}

bool isDupe(decklist::entryType entry, int maxCount){
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
//returns a sub decklist of just the cards with X copies or more
//basics excluded
decklist::deckType decklist::findDupes(int maxCount){
    //using namespace std::placeholders;
    deckType dupesList; //not a list, but a decklist of dupes
    auto beg = deckText->begin();
    auto end = deckText->end();
    auto crit = std::bind(isDupe, std::placeholders::_1, maxCount);
    //auto crit = [&](decklist::entryType e){return isDupe(e,maxCount);};
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


int  decklist::size(){ //how many cards in the deck
    int sz = 0;
    for(auto p : *deckText){
        sz += p.second;
    }
    return sz;
}

void decklist::addCard(entryType entry){
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

void decklist::load(std::string& filename){
    std::ifstream in(filename);
    std::string line;
    std::string ct;
    std::string cardname;
    while(in >> ct){
        std::getline(in, cardname);
        cardname.erase(0,1);
        entryType entry = std::make_pair(cardname, std::stoi(ct));
        //std::cout << ct << " " << cardname << "\n";
        addCard(entry);
    }
    in.close();
    
}

void decklist::view(){
    for(auto e : *deckText){
        std::cout << e.second << " " << e.first << "\n";
    }
}

void decklist::setCommander(std::string cmdName){
    //check if the card is currently in the decklist
    //if not, say there is an error and get out.

    if(format != "Commander"){
        std::cerr << "Can only set commander if format is commander." << std::endl;
        return;
    }
    auto check = deckText->find(cmdName);
    if(check != deckText->end()){
        std::cerr << "Card: " << cmdName << " was not found in the decklist" 
        << std::endl;
        return;
    }
    else{
        //need to check whether card is legendary, but need card data
        //for that...
        commander = cmdName;
    }


}

//to implement later...
//I could define operator>> and << for input and output...
//that would probably be convenient?


//management
//void decklist::addToCollection(); //add this deck to the collection
//void decklist::save(); //save to decklists folder