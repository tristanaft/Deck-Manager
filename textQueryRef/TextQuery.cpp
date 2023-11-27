#include "TextQuery.h"
#include "QueryResult.h"

/*
void TextQuery::printText(){
    for(auto l : entireText) 
    std::cout << l << std::endl;
}
*/

TextQuery::TextQuery(std::ifstream& in): entireText(new std::vector<std::string>){
    std::string line;
    while(getline(in, line)){
        entireText -> push_back(line);
        int n = entireText -> size() - 1; //current line number
        std::istringstream iss(line);
        std::string word;
        while(iss >> word){
            auto &lines = wordOccurrences[word]; //this adds new entry if it doesnt exist
            if(!lines) //if this is the first occurrence, the pointer is null
                lines.reset(new std::set<line_no>); //allocate new set
                //this is giving me red squiggles on VScode, not sure why it runs fine?
                //vscode is saying this is <error-type> but it is fine?
            lines->insert(n); //insert line number
        }
    }
}

QueryResult TextQuery::query(const std::string &target){
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>); //if no data found    
    auto loc = wordOccurrences.find(target);
    if(loc == wordOccurrences.end()){
        return QueryResult(target, nodata, entireText);
    }else{
        return QueryResult(target, loc -> second, entireText);
    }
}

