#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>
#include <utility>
#include "menu.h"

void menu::display(){
    for(auto p: menuMap){
        std::cout << p.second.name << " -> ";
        std::cout << p.second.text << std::endl;
    }
}

menu::menu(std::initializer_list<menuItem> ilm){
    for(auto m: ilm){
        addItem(m);
    }
    //maybe there is a better way to process this
}

void menu::processInput(std::istream& in){
    std::string response; 
    //get user response
    //while(in >> response){ //gets single word?
    while(std::getline(in,response)){
        auto item = menuMap.find(response);
        if(item != menuMap.end()){
        //found something,
        //call corresponding function, which should put us in some different state
        (*item).second.MenuFunction(); 
        //this REQUIRES menuFunction to have no arguments...
        //now, OK to leave this function
        return;
        }
        else{
            std::cout << "Response not recognized, try again." <<std::endl;
        }
        //NOTE: I don't have any kind of quit functionality...
        //it may be a good idea to just have quit be part of processing input?
    }
    
    //now match response to one of the menu options
    //if we can't, then go back to beginning...
    
}















//maybe rework these into menu items?
std::ostream& prompt(std::ostream& os){
    std::cout << "-EDH Manager-" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1) add deck" << std::endl;
    std::cout << "2) add cards to collection" << std::endl;
    return os;
}

void adddeck(){
    std::cout << "adding deck" << std::endl;
    std::cout << "1) load from file" << std::endl;
    std::cout << "2) manual input" << std::endl;
    std::string rsp;
}
void addToCollection(){
    std::cout << "adding to collection" << std::endl;
}
