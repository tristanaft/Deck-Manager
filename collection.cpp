#include "collection.h"
#include "deck.h"
#include "cardlist.h"

#include <fstream>
#include <iostream>
#include <sstream>

void collection::view(){
    std::cout << "Title: " << title <<std::endl;
    std::cout << "Included Decks: ";
    std::string delim = "";
    for(const auto& d : includedDecklists){
        std::cout << delim <<d;
        delim = ", "; //this is to leave off last delimiter
    }
    std::cout << std::endl;
    // << inCollection <<std::endl;
    cardlist::view(); //print out list of cards
}

std::ofstream& collection::save(std::ofstream& file){
    //I will have to have the save be based on the title
    //as part of a menu option I think
    file << "Collection: " << title <<std::endl;
    file << "Included Decklists: ";
    std::string delim = "";
    for(const auto& d : includedDecklists){
        file << delim <<d;
        delim = ", "; //this is to leave off last delimiter
    }
    file << std::endl;
    cardlist::save(file); //print out list of cards
    return file;
}

//load
//like with deck, there will be headers to manage...

//I should write a function that allows me to
//load a DECK into a COLLECTION from a FILE...
//would that be like an "import" function?

void handleHeaders(std::ifstream& input, collection& c){
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
        if(firstStr == "Collection:"){
            getline(input,line);
            c.title = line;
            hitHeader = true;
            //std::cout << "hit Decklists:" << std::endl;
        }
        else if(firstStr == "Included"){
            //std::cout << "hit Included" << std::endl;
            input >> firstStr; //need to get "Collections:" out of the way
            getline(input,line);
            //now, convert line to string stream and add to collVec
            std::stringstream lss(line);
            while(lss >> secStr){
                c.includedDecklists.push_back(secStr);
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
        c.addCard(entry);
    }
};

void collection::load(std::string& filename){

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







void collection::addDeck(deck& d){
    //add the collection title to the deck
    //and the deck title to the collection
    //BUT have to check to make sure deck not already in collection
    //check if collection in deck
    auto ch1 = std::find(d.collVec.begin(),d.collVec.end(), this->getTitle());
    //check if deck in collection
    auto ch2 = std::find(includedDecklists.begin(),
                        includedDecklists.end(),
                        title);
    if(ch1 != d.collVec.end()){
        std::cout << "Deck labelled as in collection already." << std::endl;
        return;
    }
    if(ch2 != includedDecklists.end()){
        std::cout << "Collection already contains deck." << std::endl;
        return;
    }
    //these two conditions SHOULD MATCH...
    //I will separate them just in case.

    //
    includedDecklists.push_back(d.getTitle());

    d >> *this;


}

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
