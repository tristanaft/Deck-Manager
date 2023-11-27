#include<string>
#include<iostream>
#include <fstream>

int main(){

    std::ifstream in("chainerDeck.txt");

    std::string line;
    while(in){
        std::string ct;
        std::string cardname;
        in >> ct;
        std::getline(in, cardname);
        cardname.erase(0,1);
        //there is a space at the beginning of cardname
        //std::getline(in, line);
        //std::cout << line << std::endl;
        //ct = line[];
        std::cout << "count: " << ct << '\n';
        std::cout << "cardname: " << cardname << std::endl;
    }
    

    return 0;
}