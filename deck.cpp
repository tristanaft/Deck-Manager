#include "deck.h"

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>

//properties
//isValid is currently (4/19) incomplete
//I have yet to implement anything that can access the data
//in cardData.json which is required for verifying EDH validity
bool deck::isValid(){//check if the given deck is valid
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

void handleHeaders(std::ifstream& input, deck& d){
    //headers of the form:
    //Decklist: some title
    //Format: standard/commander/other?
    //Commander: some cardname... (this may or not be here)
    //In Collections: this will have multiple options...

    std::string firstStr;
    std::string secStr;
    std::string line;
    bool hitHeader = true; //just to start while loop
    while(hitHeader){
        if(input.eof()){
            //std::cout << "HIT EOF" << std::endl;
            break;}
        //std::cout << "at start of loop" << std::endl;
        hitHeader = false;
        input >> firstStr; //if input is valid
        //check all possible headers
        //if we hit one, 
        if(firstStr == "Decklist:"){
            getline(input,line);
            d.title = line;
            hitHeader = true;
            //std::cout << "hit Decklists:" << std::endl;
        }
        else if(firstStr == "Format:"){
            getline(input,line);
            d.format = line;
            hitHeader = true;
            //std::cout << "hit Format:" << std::endl;
        }
        else if(firstStr == "Commander:"){
            getline(input,line);
            d.commander = line;
            hitHeader = true;
            //std::cout << "hit Commander:" << std::endl;
        }
        else if(firstStr == "In"){
            //std::cout << "hit In" << std::endl;
            input >> firstStr; //need to get "Collections:" out of the way
            getline(input,line);
            //now, convert line to string stream and add to collVec
            std::stringstream lss(line);
            while(lss >> secStr){
                d.collVec.push_back(secStr);
            }
            hitHeader = true;
            //input >> firstStr;
        }
    }
    //input >> firstStr;
    //ok, if we are out here, then we should be in the actual cardlist,
    //so firstStr has the count of the first card.
    if(!input.eof()){
        std::getline(input, line);
        line.erase(0,1);
        //std::cout << "line = " << line << " " << "firstStr = " <<firstStr << std::endl;
        deck::entryType entry = std::make_pair(line, std::stoi(firstStr));
        //I get errors specifically here ^^^ with stoi if firstStr is not
        //reading from a card list...
        //I could probably do a try/catch statement, and if firstStr
        //cant be converted to int, there may be an incorrect header
        //or the text file was written incorrectly?
        d.addCard(entry);
    }
};


void deck::load(std::string& filename){

    std::ifstream in(filename);

    //I am putting the functionality for handling the headers
    //in the decklist .txt files in here
    handleHeaders(in, *this);


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

void deck::view(){
    std::cout << "Title: " << title <<std::endl;
    std::cout << "Format: " << format <<std::endl;
    if(format == "Commander"){
        std::cout << "Commander: " << commander <<std::endl;
    }
    std::cout << "In Collections: ";
    std::string delim = "";
    for(auto coll : collVec){
        std::cout << delim <<coll;
        delim = ", "; //this is to leave off last delimiter
    }

    std::cout << std::endl;
    // << inCollection <<std::endl;
    cardlist::view(); //print out list of cards
}

std::ofstream& deck::save(std::ofstream& file){
    //I will have to have the save be based on the title
    //as part of a menu option I think
    file << "Decklist: " << title <<std::endl;
    file << "Format: " << format <<std::endl;
    if(format == "Commander"){
        file << "Commander: " << commander <<std::endl;
    }
    file << "In Collections: ";
    std::string delim = "";
    for(auto coll : collVec){
        file << delim <<coll;
        delim = ", "; //this is to leave off last delimiter
    }
    file << std::endl;
    // << inCollection <<std::endl;
    cardlist::save(file); //print out list of cards
    //SHOULD I CLOSE FILE HERE???
    //file.close();
    return file;
}

void deck::setCommander(std::string cmdName){
    //check if the card is currently in the deck
    //if not, say there is an error and get out.

    if(format != "Commander"){
        std::cerr << "Can only set commander if format is commander." << std::endl;
        return;
    }
    //need a method in cardlist to find a given card...
    //and a method to get the end of the card list...
    auto check = cardlist::findCard(cmdName);
    if(check != cardlist::getEnd()){
        std::cerr << "Card: " << cmdName << " was not found in the deck" 
        << std::endl;
        return;
    }
    else{
        //need to check whether card is legendary, but need card data
        //for that...
        commander = cmdName;
    }


}

void deck::viewCollections(){
    for(auto c : collVec){
        std::cout << c << " ";
    }
}

//I want a function that takes 2 decklists and compares them...


//management
//add this deck to the collection
/*
//After thinking a bit more, I will have collection solely manage
//the process of adding a deck to the collection.
void deck::addToCollection(collection& coll){
    //add the collection title to the deck
    //and the deck title to the collection
    //BUT have to check to make sure deck not already in collection
    //check if collection in deck
    auto ch1 = std::find(collVec.begin(),collVec.end(),coll.getTitle());
    //check if deck in collection
    auto ch2 = std::find(coll.includedDecklists.begin(),
                        coll.includedDecklists.end(),
                        title);
    if(ch1 != collVec.end()){
        std::cout << "Deck labelled as in collection already." << std::endl;
        return;
    }
    if(ch2 != coll.includedDecklists.end()){
        std::cout << "Collection already contains deck." << std::endl;
        return;
    }
    //these two things SHOULD MATCH...
    //I will separate them just in case.

    *this >> coll; 
    //this operator should add all cards from this deck to collection
} 
*/
