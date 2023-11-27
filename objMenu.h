#ifndef OBJMENU_H
#define OBJMENU_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>
#include <utility>
//#include "menu.h"
//#include "deck.h"
//#include "collection.h"

//At this point, it would literally be easier if I hard-coded
//menus for decks and collections by hand...?

template<class T>
struct objProcItem{
    std::string name;
    std::string mapLabel;
    void (*objProcFunc)(T&);
    std::string text;

    //typedef void (*Object_Processing_Function_Ptr)(T);
    //unsigned int number; //why is this necessary
    //void processInput(std::istream&);
    //Object_Processing_Function_Ptr objProcFunc;
    
};

//after trying to code, I realized I need a version of menu that
//can have a saved object that it can manipulate.
//menu for a given object of type T
template<class T>
class objMenu{ //I can't have objMenu inherit from menu... I have to redo stuff
public:
    T* myObj; // the object in this menu that is acted upon...
    //I think this has to be public so the functions in menuMap can access it
    //initialize
    objMenu() = delete; 
    //process input won't work with menuMap empty so cant blank init
    objMenu(std::initializer_list<objProcItem<T>>);

    void display(); //display the menu
    void addItem(objProcItem<T> mi) 
        {menuMap.insert({mi.mapLabel, mi});}
    void setTitle(const std::string title) {menuTitle = title;}
    void processInput(std::istream&);
    void setObj(T& obj) {myObj = &obj;} //pointer should now point to obj
private:
    //I have to call this menuMap to override the one in menu
    std::map<std::string, objProcItem<T>> menuMap;
    std::string menuTitle;
    
};

//ughhhh I forgot that you can't have a separate file for implementation...
template<class T>
objMenu<T>::objMenu(std::initializer_list<objProcItem<T>> ilm){
    for(auto m: ilm){
        addItem(m);
    }
    //maybe there is a better way to process this
}
template<class T>
void objMenu<T>::display(){
    if(menuTitle != ""){
        std::cout << menuTitle << std::endl;
    }

    for(auto p: menuMap){
        std::cout << p.second.name << " -> ";
        std::cout << p.second.text << std::endl;
    }
}


template<typename T>
void objMenu<T>::processInput(std::istream& in){
    std::string response; 
    //get user response
    //while(in >> response){ //gets single word?
    while(std::getline(in,response)){
        auto item = menuMap.find(response);
        if(item != menuMap.end()){
            //found something,
            //call corresponding function, which should put us in some different state
            (*item).second.objProcFunc(*myObj); 
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














#endif