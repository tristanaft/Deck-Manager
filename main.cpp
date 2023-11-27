#define DEBUG_LEVEL 0
#if DEBUG_LEVEL == 0
#define MAIN

#include <iostream>
#include <string>
#include <fstream>
#include "deck.h"
#include "collection.h"
#include "menu.h"
#include "objMenu.h"

//filesystem iterators to show contents of folders would be helpful.
//its a C++17 feature though...
//#include <filesystem>
//namespace fs = std::filesystem;
//need to change the C++ standard...

//void listFolderContents(const std::string& folderPath){}

//have to build the main menu...
//what is the structure?

//Main Menu: -> just to get to the other menus...
//propose a new decklist
//load a saved decklist
//load a collection

//hit propose -> prompt user for filename for .txt file
//OR (may not include) manually enter (may be too big of a pain for large decks...)
//either way, we need to get a deck object
//Propose Menu:
//view deck -> can have a generic one that acts on cardObjects
//add cards -> same as above, and then reuse below
//remove cards (need to add)
//save to collection -> prompt user for collection file name
    //make new collection from deck?

//Saved Deck Menu
//view deck
//add cards
//remove cards
//add to collection

//Collection Menu
//view collection
//add cards
//remove cards
//add deck to this collection

//the other thing I want to implement is some method of upgrading decks...
//but not sure how to do that ATM...





//I should be able to turn this into a template maybe?
template<class T> //this should be for deck or collection
void goToSubMenu(const std::string& fileFolder, objMenu<T> subMenu){
    std::cout << "Opening folder " << fileFolder  << "."<< std::endl;
    //list out everything in the folder?
    std::cout << "Input filename to load: " << std::endl;
    std::string filename, fullFilename;
    //std::getline(std::cin, filename);
    std::cin >> filename;
    T deckOrCollection; //either a deck or collection
    fullFilename = fileFolder + "/" + filename;
    //I should change the load function...
    //so I could do an ifstream and then if(in){stuff} else{error}
    deckOrCollection.load(fullFilename);
    std::cout << "Load successful." << std::endl;
    subMenu.setObj(deckOrCollection);

    //run the submenu
    bool done = false;
    //need to replace this section with the function below?
    while(!done){
        subMenu.display();
        std::cin.ignore(10000, '\n');
        subMenu.processInput(std::cin);
        std::cout << "enter q to quit, otherwise input any other key" << std::endl;
        std::string qstr;
        std::cin >> qstr;
        if(qstr == "q") done = true;
        std::cout << std::endl;
        //std::cin.ignore(10000, '\n'); //clear line for new input
    }

    //here is where you must prompt RETURN TO MAIN MENU and QUIT

    
}

void removeCard(cardlist& cl){
    cl.view(); //show all the cards first
    std::cout << "Enter card to remove: ";
    std::string name;
    std::getline(std::cin, name);
    cl.removeCard(name);
    //I think that is all we need, now just specialize for menu func.
    //we can just act on the cardlist directly
    //I could have been doing this for other functions probably...
}

void removeCardDeck(deck& d){ removeCard(d);}
void removeCardCollection(collection& coll){removeCard(coll);}

void viewDeck(deck& d){d.view();}
void viewCollection(collection& c){c.view();}

void addCardDeck(deck& d){
    std::cout << "Enter a card to add: ";
    std::string cn;
    std::getline(std::cin,cn);
    d.addCard({cn,1});
}

void addCardCollection(collection& c){
    std::cout << "Enter a card to add: ";
    std::string cn;
    std::getline(std::cin,cn);
    c.addCard({cn,1});
}

void saveDeck(const std::string foldername, deck& d){
    std::cout << "Save as: " << std::endl;
    std::string deckname;
    std::cin >> deckname;
    std::string fullname = foldername + deckname + ".txt";
    std::ofstream ofs(fullname);
    d.save(ofs);
}

void saveCollection(collection& c){
    std::cout << "Save as: " << std::endl;
    std::string collname;
    std::cin >> collname;
    std::string fullname = "collections/" + collname + ".txt";
    std::ofstream ofs(fullname);
    c.save(ofs);
}

//void (*addCardDeckPtr)(deck&) = &addCardDeck;
//ugh, surely there must be a better way to do this...
//what I want to be able to do, is have one function template
//and then define specializations of that template?
//I GUESS this works...
//idk what to do instead though
//is this a forwarding issue?

//ughhh i cant do it like this...
//i need to load a collection and add the proposed deck to it...
void saveToSaved(deck&d){saveDeck("savedDecklists",d);}
void saveToProposed(deck&d){saveDeck("proposedDecklists",d);}
void publishDeck(deck& d) {
    //this should take a deck from proposedDecklists
    //add it to a collection
    //then save it to savedDecklists

    //Stuff to implement later:
    //CHECK THAT DECKLIST IS VALID BEFORE YOU CAN SAVE AND PUSH TO COLLECTION

    std::cout << "Enter the name of the collection you want to open: " <<std::endl;
    std::string filename, fullFilename;
    //std::getline(std::cin, filename);
    std::cin >> filename;
    fullFilename = "collections/filename.txt"; //maybe leave off .txt...
    collection temp(fullFilename); //this loads the collection from the filename....
    temp.addDeck(d); //add deck to this collection
    std::ofstream ofs1(fullFilename);
    temp.save(ofs1); //save changes to collection
    ofs1.close();
    std::cout << "Deck saved to collection successfully." <<std::endl;
    //ok, now you can save the deck to savedDecklists
    saveDeck("savedDecklists",d);
}

//have to turn the run function for objmenu into a template
template<class T>
void runObjMenu(objMenu<T>& om){
    bool done = false;
    while(!done){
        om.display();
        om.processInput(std::cin);
        std::cout << "enter q to quit, otherwise input any other key" << std::endl;
        std::string qstr;
        std::cin >> qstr;
        if(qstr == "q") done = true;
        std::cout << std::endl;
        std::cin.ignore(10000, '\n'); //clear line for new input
    }
}

//ok, so the option for the main menu should do what exactly?



//have to set up sub-menus before main menu
//first, menu options...
objProcItem<deck> viewOptionDeck = {"View", "view" ,&viewDeck, "view cards in deck"};
objProcItem<deck> addOptionDeck = {"Add", "add" ,&addCardDeck, "add card to deck"};
objProcItem<deck> removeOptionDeck = {"Remove", "remove" ,&removeCardDeck, "remove a card from the deck"};

objProcItem<deck> saveOptionSaved = {"Save", "save", &saveToSaved, "save deck (doesn't yet affect the collection file...)"};
objProcItem<deck> saveOptionProp = {"Save", "save", &saveToProposed, "save changes but don't add to collection"};
objProcItem<deck> publishOption = {"Publish", "publish", &publishDeck, "saves deck to saved deck folder and add to existing collection"};


objProcItem<collection> viewOptionCollection = {"View", "view" , &viewCollection, "view cards in collection"};
objProcItem<collection> addOptionCollection = {"Add", "add" ,&addCardCollection, "add card to collection"};
objProcItem<collection> removeOptionCollection = {"Remove", "remove", &removeCardCollection, "remove a card from the collection"};
objProcItem<collection> saveOptionCollection = {"Save", "save", &saveCollection, "save collection"};

//now, set up sub-menus
objMenu<deck> savedDeckMenu{viewOptionDeck, addOptionDeck, removeOptionDeck,saveOptionSaved};
objMenu<deck> proposedDeckMenu{viewOptionDeck, addOptionDeck, removeOptionDeck ,saveOptionProp, publishOption};
objMenu<collection> collectionMenu{viewOptionCollection,addOptionCollection, removeOptionCollection ,saveOptionCollection};



//now, build main menu to run
//menu mainMenu;
//menuItem savedDeck = {};
//menuItem proposedDeck = {};
//menuItem collection = {};
//menuItem quit = {};

//need specializations of goToSubMenu for each of our submenus
//there must be a better way to do this right?
void goToSaved() {goToSubMenu<deck>("savedDecklists", savedDeckMenu);}
void goToProposed() {goToSubMenu<deck>("proposedDecklists", proposedDeckMenu);}
void goToCollections() {goToSubMenu<collection>("collections",collectionMenu);}
//now, these I should be able to call in menu set up in main?
//menuItem savedDeck = {"View", "view" , , "view cards in deck"};
menuItem savedDeck = {"Saved Decks", "saved", &goToSaved, "Open a saved deck."};
menuItem proposedDeck = {"Proposed Decks", "proposed", &goToProposed, "Open or create new proposed deck."};
menuItem collections = {"Collections", "collections", &goToCollections, "Open or create new collection."};

//menu mainMenu{savedDeck, proposedDeck, collections};
//for some reason, collections is not displaying?
//the initializer list not working?
//mainMenu.setTitle("My Deck Collection Database");



int main(){
    //std::string deckfilename1 = "proposedDecklists/monoBlackBurn.txt";
    menu mainMenu{savedDeck, proposedDeck, collections};


    bool isDone = false;
    while(!isDone){
        mainMenu.display();
        //std::cout << std::endl;
        mainMenu.processInput(std::cin);

        isDone = true;
    }

    





    return 0;
}















#endif