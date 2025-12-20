#include <iostream>
#include "QueryParser/QueryParser.h"

int main() {
    const std::string query = "SELECT * FROM table;";

    QueryParser queryParser = QueryParser(query);
    std::cout << "Parsing:" << std::endl;
    queryParser.parseQuery();
    std::cout << "Printing:" << std::endl;
    queryParser.print();

    return 0;
}
