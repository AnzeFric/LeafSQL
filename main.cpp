#include <iostream>
#include "QueryParser/QueryParser.h"

int main() {
    const std::string selectQuery = "SELECT * FROM table;";
    const std::string createDBQuery = "CREATE DATABASE LeafDB;";
    const std::string createTableQuery = "CREATE TABLE LeafTable";

    QueryParser queryParser = QueryParser(createDBQuery);
    queryParser.parseQuery();
    queryParser.print();

    return 0;
}
