#define DEBUG_LEVEL 0
//need to have this here and match the one in main.cpp

#if DEBUG_LEVEL == 1
#define DECK_DEBUG

#include <iostream>
#include <string>
#include <fstream>
#include "deck.h"
#include "collection.h"

int main(){
    /*
    bool okToProceed = false;
    std::string rsp1;

    while(!okToProceed){
        prompt(std::cout);
        std::cin >> rsp1;
        if(rsp1 == "1" || rsp1 == "2")
            okToProceed = true;
        else{
            std::cout << "input 1 or 2" << std::endl;
        }
    }
    if(rsp1 == "1")
        adddeck();

    if(rsp1 == "2")
        addToCollection();

    */
   std::cout << "Testing deck functionality." << std::endl;

    //test out initializing
    deck decktest1;
    std::cout << "Adding individual cards" << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;
    deck::entryType testEntry = {"cardname", 1};
    deck::entryType testEntr2 = {"cardname2", 1};
    decktest1.addCard(testEntry);
    //decktest1.view();
    std::cout << std::endl;
    decktest1.addCard(testEntry);
    //decktest1.view();
    std::cout << std::endl;
    decktest1.addCard(testEntr2);
    //decktest1.view();
    std::cout << std::endl;


    std::cout << "Loading Decks..." << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;
    std::string fileName = "monoBlackBurn.txt";
    //deck decktest2(fileName);
    std::cout << "manual load" << std::endl;
    deck decktest2;
    decktest2.load(fileName);
    //decktest2.view(); //view method works,
    //commenting out views to save on space in cmd
    std::cout << "load by init" << std::endl;
    deck decktest3(fileName);
    //decktest3.view(); //view method works,
    //commenting out views to save on space in cmd
    std::cout << std::endl;

    std::cout << "Duplicate Checking..." << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;
    std::string filename2 = "invalidDecklist.txt";
    deck decktest4(filename2);
    decktest4.view();
    auto dt4dupes = decktest4.findDupes(4);
    std::cout << std::endl;
    std::cout << "Card list of duplicate cards:" << std::endl;
    for(auto e : dt4dupes){
        std::cout << e.second << " " << e.first << std::endl;
    }
    std::cout << std::endl;
    //ok, that works.

    std::cout << "Check get and set methods..." << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;
    std::cout << "getFormat() = " << decktest4.getFormat() << std::endl;
    std::cout << "now, setFormat = test and try again" << std::endl;
    decktest4.setFormat("test");
    std::cout << "getFormat() = " << decktest4.getFormat() << std::endl;
    std::cout << std::endl;

    std::cout << "Check operator >>" << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;
    deck decktest5, decktest6;
    deck::entryType te1 = {"cardname1", 1};
    deck::entryType te2 = {"cardname2", 1};
    deck::entryType te3 = {"cardname3", 1};
    //I should put in a function for entering a bunch of entries...
    //as it is now, it is one at a time.
    decktest5.addCard(te1);
    decktest5.addCard(te2);

    decktest6.addCard(te1);
    decktest6.addCard(te2);
    decktest6.addCard(te2);
    decktest6.addCard(te3);

    std::cout << "deck1:" << std::endl;
    decktest5.view();
    std::cout << "deck2:" << std::endl;
    decktest6.view();
    std::cout << "deck1 >> deck2 " << std::endl;
    decktest5 >> decktest6;
    std::cout << "deck2:" << std::endl;
    decktest6.view();
    std::cout << std::endl;






    //commander set method is more complicated than formats
    //std::cout << std::endl;
    //auto tc = decktest4.getCommander();
    /*
    std::cout << "getCommander() = " << decktest4.getCommander() << std::endl;
    std::cout << "now, setCommander = test and try again" << std::endl;
    decktest4.setCommander("test");
    std::cout << "getCommander() = " << decktest4.getCommander() << std::endl;
    std::cout << std::endl;
    */


   //I can verify formats when I get code working
   //that gets card data from cardData.json...
    /*
    std::cout << "Verifying Formats..." << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;
    std::cout << "I can check for standard now, but EDH is limited..." << std::endl;
    //std::cout << "test format is: " << decktest3.getFormat() << std::endl;
    //decktest3.isValid();
    //std::string filename2 = "invaliddeck.txt";
    deck decktest5(filename2);
    std::cout << "test format is: " << decktest5.getFormat() << std::endl;
    decktest5.isValid();
    std::cout << std::endl;
    */

    std::cout << "Testing save functions" << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;

    //std::ofstream file("test.txt");
    //file << "some text" << std::endl;
    //file.close();
    std::ofstream file1("testDeck.txt");
    decktest6.save(file1);
    decktest6.view();
    file1.close();

    std::cout << "Testing load function with headers" << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;
    std::string fn1 = "testDeck.txt";
    deck decktest7(fn1);
    std::cout << "Loaded Deck:" << std::endl;
    decktest7.view();
    std::cout << "Original Deck:" << std::endl;
    decktest6.view();

    return 0;
}

#endif


#if DEBUG_LEVEL == 2
#define COLLECTION_DEBUG

#include <iostream>
#include <string>
#include <fstream>
#include "deck.h"
#include "collection.h"

int main(){

    //std::cout << "Testing Collection Functionality" << std::endl;
    //std::cout << "------------------------" << std::endl;

    std::cout << "Load collection without headers from file" << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;

    std::string filename1 = "collectionTest.txt";
    collection coll1(filename1); //I dont think I implemented from string init?
    coll1.view();
    std::cout << std::endl;

    std::cout << "Ok, lets try adding a title, saving and reloading it?" << std::endl;
    std::cout << "As it is now, the file can be named anything," << std::endl;
    std::cout << "When I save something, the title of the deck/collection doesn't matter..." << std::endl;

    coll1.setTitle("Interesting Title");

    std::string filename2 = "collSaveTest1.txt";
    std::ofstream out2(filename2); //naming out2 to match filename 2, there is no out1
    coll1.save(out2);
    out2.close();
    collection coll2(filename2);
    std::cout << std::endl;
    coll2.view();
    std::cout << "Ok, the title works... there is a weird blank line in the .txt file..." << std::endl;
    std::cout << "Just to make sure it is fine... lets check this newly saved file..." << std::endl;
    collection coll3(filename2);
    coll3.view();
    std::cout << "Ok, it reads just fine..." << std::endl;
    std::cout << std::endl;

    std::cout << "Add decklists to build collection..." << std::endl;
    std::cout << "++++++++++++++++++++++++" << std::endl;
    std::cout << "Oh, I have to make sure I title the decks too" <<std::endl;
    std::string deckfilename1 = "monoBlackBurn.txt";
    //std::string deckfilename2 = "chainerDeck.txt";
    std::string deckfilename3 = "hammertime.txt";
    deck mbb(deckfilename1);
    //deck chd(deckfilename2);
    deck ham(deckfilename3);
    mbb.setTitle("Mono Black Burn");
    ham.setTitle("Hammertime");

    std::cout << "I will try adding to just a blank collection" <<std::endl;
    collection coll4;
    coll4.addDeck(mbb);
    //coll4.addDeck(chd);
    coll4.addDeck(ham);
    coll4.view();
    //ok that is fixed...
    std::cout << "Ok, now let's try saving this..." <<std::endl;
    std::string filename3 = "collSaveTest2.txt";
    std::ofstream out3(filename3); //naming out2 to match filename 2, there is no out1
    coll4.save(out3);


    

    return 0;
}

#endif

#if DEBUG_LEVEL == 3
#define MENU_DEBUG

#include <iostream>
#include <string>
#include <fstream>
#include "deck.h"
#include "collection.h"
#include "menu.h"

menu mainMenu;

void runMenu(menu m){
    m.display();
    m.processInput(std::cin);
}

//what are mainMenu options?
menuItem goToPropDeckMenu;
menuItem goToSavedDeckMenu;
menuItem goToCollectionMenu;


menu proposedDeckMenu, savedDeckMenu, collectionMenu;

//what are the proposedDeckMenu options?
//menuItem loadProposedDeck; //should have to load a deck to get to the deck menu
menuItem viewDeck;
menuItem saveProposedDeck;
menuItem addCardToDeck;
menuItem removeCardDeck;

//what are the savedDeckMenu options?
//menuItem viewDeck;
menuItem saveSavedDeck;
//menuItem addCardToDeck;
//menuItem removeCard;

//what are the collectionMenu options?
menuItem addCardToCollection;
menuItem addSavedDeck;
menuItem viewCollection;
menuItem removeCardCollection;

//menu testMenu;
menuItem optA, optB, optC;

void optAfunc(){
        std::cout << "process A" <<std::endl;
    }
void optBfunc(){
        std::cout << "process B" <<std::endl;
    }
void optCfunc(){
        std::cout << "process C" <<std::endl;
    }
void goToMenuA(){
    std::cout << "Running Menu A" << std::endl;

}


int main(){
    /*
    //testing out my menu class stuff...
    optA.name = "Option A";
    optB.name = "Option B";
    optC.name = "Option C";

    optA.text = "Some text for opt A";
    optB.text = "Some text for opt B";
    optC.text = "Some text for opt C";

    //set MenuFunctions
    optA.MenuFunction = &optAfunc;
    optB.MenuFunction = &optBfunc;
    optC.MenuFunction = &optCfunc;

    //Ok, here we actually get to work with the menu...


    menu testmenu({optA, optB, optC}); //nice this works for init
    std::cout << "This is a test menu" << std::endl;
    std::cout << "+++++++++++++++++++" << std::endl;
    std::cout << "Enter one of the following:" << std::endl;


    menuItem goToSubMenuA;
    goToSubMenuA.name = "Submenu A";
    goToSubMenuA.text = "Go To Submenu A";
    goToSubMenuA.MenuFunction = &goToMenuA;


    testmenu.display();
    testmenu.processInput(std::cin);
    //maybe should have default options, like view() to show menu again
    //and quit() to quit the menu...

    menu nestedMenu({goToSubMenuA, optB, optC});
    */



    
    










    return 0;
}


#endif

#if DEBUG_LEVEL == 4
//here, I am going to test out objMenu

#include <iostream>
#include <string>
#include <fstream>
#include "deck.h"
#include "collection.h"
#include "menu.h"
#include "objMenu.h"

void inc(int& i){
    ++i;
}
void (*f1)(int&) = &inc;


int main(){

   //Ok... I don't really understand why, but I have to build the 
    //menu items INSIDE OF MAIN
    /*
    struct objProcItem{
        std::string name;
        void (*objProcFunc)(T&);
        std::string text;
        };
    */

    /*
    objProcItem<int> opi1;
    opi1.objProcFunc = f1;
    opi1.name = "op1";
    opi1.text = "increment the saved int";
    */
   objProcItem<int> opi1 = {"op1", f1, "increment the saved int"};
    

    //for opi to be usable, needs:
        //a function
        //a name
    objMenu<int> test({opi1});
    int i = 5;
    test.setObj(i);
    test.setTitle("Int Menu");
    test.display();
    test.processInput(std::cin);
    std::cout << i << std::endl;



    

    return 0;
}


#endif