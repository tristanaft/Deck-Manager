#include "QueryResult.h"

std::string make_plural(int cnt, const std::string &s,
                        const std::string &postfix = "s") {
  return cnt > 1 ? s + postfix : s;
}

std::ostream &print(std::ostream &os, const QueryResult &qr){
    os << qr.target << " occurrs " << qr.lines -> size() << " " << 
    make_plural(qr.lines -> size() , "time","s") << std::endl;
    for (auto num : *qr.lines){
        os << "\t (line " << num+1 <<"): " << *(qr.text->begin() + num) << std::endl;
    }
    return os;
}

