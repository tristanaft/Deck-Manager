#ifndef QUERYRESULT_H
#define QUERYRESULT_H


#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <set>
#include <iostream>

class QueryResult{
using line_no = std::vector<std::string>::size_type;
public:
    friend std::ostream& print(std::ostream&, const QueryResult&);
    QueryResult() = default; //get this IF QUERY INVALID
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>>p,
                std::shared_ptr<std::vector<std::string>> f) : 
                target(s), lines(p), text(f) {}
    std::set<line_no>::iterator begin() {return lines->begin();};
    std::set<line_no>::iterator end() {return lines->end();};
    std::shared_ptr<std::vector<std::string>> get_file() {return text;};
private:
    std::string target;
    std::shared_ptr<std::set<line_no>> lines; //lines that the target is on
    std::shared_ptr<std::vector<std::string>> text; //entire text
};


#endif