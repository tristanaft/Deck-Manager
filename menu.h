#ifndef MENU_H
#define MENU_H

typedef void (*Menu_Processing_Function_Ptr)();

struct menuItem{
    //unsigned int number; //why is this necessary
    std::string name;
    std::string mapLabel;
    Menu_Processing_Function_Ptr MenuFunction;
    std::string text;
    
};

class menu{
public:
    //initialize
    menu() = default;
    menu(std::initializer_list<menuItem>);

    void display(); //display the menu
    void addItem(menuItem mi) 
        {menuMap.insert({mi.mapLabel, mi});}
    void processInput(std::istream&); //get input and then run a specific menu item
    void setTitle(const std::string title) {menuTitle = title;}

private:
    std::string menuTitle; //is this necessary?
    std::map<std::string, menuItem> menuMap;
};

#endif