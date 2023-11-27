#include "TextQuery.h"
#include "QueryResult.h"

void runQueries(std::ifstream &infile){

    TextQuery tq(infile);
    while(true){
        std::cout << "Enter word to look for, or q to quit: ";
        std::string s;
        if(!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s));
    }

}

int main(){
    std::ifstream in("inputfile.in");
    //std::string s;
    //while(in){
    //    in >> s;
    //    std::cout << s << " ";
    //}
    //I could write more code to request a file name, but I want to be lazy right now...
    runQueries(in);




    

    return 0;
}