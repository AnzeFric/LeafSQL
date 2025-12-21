#include <iostream>
#include "QueryParser/QueryParser.h"

int main() {
    const std::string query = "SELECT * FROM table;";

    QueryParser queryParser = QueryParser(query);
    queryParser.parseQuery();
    queryParser.print();

    return 0;
}
