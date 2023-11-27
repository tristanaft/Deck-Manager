#ifndef TEXTQUERY_H
#define TEXTQUERY_H

class QueryResult;
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <set>
#include <algorithm>



class TextQuery{
    friend class QueryResult;
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&); //initializer
    QueryResult query(const std::string&); //output query result for given word
    //void printText(); //for debugging
private:
    std::shared_ptr<std::vector<std::string> > entireText; //stored LINE BY LINE
    std::map<std::string, std::shared_ptr<std::set<line_no>> > wordOccurrences;
};


#endif